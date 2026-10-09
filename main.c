#include "mysh.h"
#include "builtins.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

void sigchld_handler(int sig);

int main(void)
{
    signal(SIGCHLD,sigchld_handler);

    char line[MAX_LINE];
    char *argv[MAX_ARGS];

    while (1) {
        printf("mysh> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            continue;
        }

        int argc = parse_line(line, argv, MAX_ARGS);
        if (argc == 0) {
            continue;
        }

        int background = 0;

        if(argc > 0 && strcmp(argv[argc - 1],"&") == 0){
            background = 1;
            argv[argc-1] = NULL;
            argc--;
        }

        if(argc == 0){
            continue;
        }

        if(is_builtin(argv)){
            run_builtin(argv);
            continue;
        }

        execute_cmd(argv,background);
    }

    return 0;
}

void sigchld_handler(int sig){
    while(waitpid(-1,NULL,WNOHANG)>0){
        (void)sig;
        continue;
    }
}