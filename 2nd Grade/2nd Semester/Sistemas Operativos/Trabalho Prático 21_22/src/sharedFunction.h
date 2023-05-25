#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>

#ifndef __SHARED_F__
#define __SHARED_F__


#define STATUS 1
#define PROC_FILE 2

typedef struct pedido{
    int elems;
    int priority;
    char args[22][222];//max de 22 palavras de de 222 de lenght de cada palavra
}*Pedido;


#define ERROR -1
#define OK 1

#define MAX_STORE 777

#define TRANS_NR 7

#define ALARM_TIME 11

#define STARVATION_COUNT 11

#define SERVICE_PENDENT "Request status: PENDENT\n"
#define SERVICE_RUNNING "Request status: RUNNING\n"
#define SERVICE_FINISHED "Request status: CONCLUDED\n"
#define SERVICE_ABORTED "Request status: ABORTED\n"

#define READ_NAME "../tmp/fifoRead"
#define WRITE_NAME "../tmp/fifoWrite"

char* concatStrings(char *s1, char *s2);

int redirecionar(char *inputPath, char *outputPath);

void copyStruct(Pedido src, Pedido dst);

off_t calculaTamanho(char* path);

#endif