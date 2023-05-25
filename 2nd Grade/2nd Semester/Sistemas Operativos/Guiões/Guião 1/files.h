#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 100

typedef struct pessoa{
    char nome[BUFF_SIZE];
    int idade;
} Pessoa;
