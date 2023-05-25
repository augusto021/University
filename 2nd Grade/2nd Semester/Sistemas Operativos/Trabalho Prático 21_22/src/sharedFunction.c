#include "sharedFunction.h"


char* concatStrings(char *s1, char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int redirecionar(char *inputPath, char *outputPath){
    int input,output;

    input = open(inputPath, O_RDONLY);
    if(input == ERROR){
        perror("error redirecting input");
        return ERROR;
    }
    dup2(input,STDIN_FILENO);
    close(input);
  
    output = open(outputPath, O_TRUNC | O_WRONLY | O_CREAT, 0666);
    if( output == ERROR){
        perror("error redirecting output");
        return ERROR;
    }
    dup2(output,STDOUT_FILENO);
    close(output);

    return OK;
}

void copyStruct(Pedido src, Pedido dst){
    dst->elems = src->elems;
    dst->priority = src->priority;
    for (int i = 0; i < src->elems; i++){
        sprintf(dst->args[i], "%s", src->args[i]);
    }
}

off_t calculaTamanho(char* path){
    int fd = open(path, O_RDONLY);
    off_t size = lseek(fd, 0, SEEK_END);
    close(fd);
    return size;
}