#include "builtins.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int is_builtin(char *argv[]){
    if(argv[0]==NULL)
        return 0;
    else if((strcmp(argv[0],"cd") == 0)||(strcmp(argv[0],"exit") == 0))
        return 1;
    else
        return 0;
}
int run_builtin(char *argv[]){
    if(strcmp(argv[0],"exit") == 0){
        exit(0);
    }
    
    else if(strcmp(argv[0],"cd") == 0){
        const char *path;
        path = getenv("HOME");
        if(argv[1] == NULL){
            path = getenv("HOME");
            if(path == NULL){
                fprintf(stderr,"cd: HOME not set\n");
                return 1;
            }
        }
        else{
            path = argv[1];
        }

        if(chdir(path)!=0){
            perror("cd");
        }
        return 1;
    }

    return 0;
}