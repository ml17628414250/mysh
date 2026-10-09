#include "mysh.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
int execute_cmd(char *argv[],int background)
{
    sigset_t mask,oldmask;

    /* 1. 构造只含 SIGCHLD 的信号集 */
    sigemptyset(&mask);
    sigaddset(&mask,SIGCHLD);

    sigprocmask(SIG_BLOCK,&mask,&oldmask);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        sigprocmask(SIG_SETMASK,&oldmask,NULL);
        return -1;
    }

    if (pid == 0) {
        /* 子进程：恢复原掩码 */
        sigprocmask(SIG_SETMASK, &oldmask,NULL);
        /* 子进程：执行命令 */
        execvp(argv[0], argv);
        /* 只有 execvp 失败才会走到这里 */
        perror("execvp");
        _exit(127);
    }

    /* 父进程：等子进程结束 */
    if(background == 0){
        int status = 0;
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid");
            sigprocmask(SIG_SETMASK,&oldmask,NULL);
            return -1;
        }
        sigprocmask(SIG_SETMASK, &oldmask, NULL);
        return status;
    }
    else{
        sigprocmask(SIG_SETMASK, &oldmask, NULL);
        return -1;
    }
}