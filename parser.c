#include "mysh.h"

int parse_line(char *line, char *argv[], int max_args)
{
    int argc = 0;
    char *p = line;
    int in_token = 0;

    while (*p != '\0') {
        if (*p == ' ' || *p == '\t') {
            *p = '\0';
            in_token = 0;
        } else {
            if (!in_token) {
                if (argc >= max_args - 1) {
                    break;
                }
                argv[argc++] = p;
                in_token = 1;
            }
        }
        p++;
    }

    argv[argc] = NULL;
    return argc;
}