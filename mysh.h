#ifndef MYSH_H
#define MYSH_H

#include <stddef.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

/* 把一行拆成 argv，返回 argc，argv[argc] 置为 NULL */
int parse_line(char *line, char *argv[], int max_args);

/* 执行 argv 表示的命令，返回退出状态 */
int execute_cmd(char *argv[],int background);

#endif
