#include "files.h"

/* Implemente um programa que execute concorrentemente uma lista de executáveis especificados como
argumentos da linha de comando. Considere os executáveis sem quaisquer argumentos próprios. O
programa deverá esperar pelo fim da execução de todos processos por si criados. */

int main(int argc,const char* argv[]){
    int status;
    char* exec_args = NULL; 

    for(int i = 1;i < argc; i++){
        if(fork() == 0){
            execvp(argv[i],exec_args);
            _exit(i);
        }
    }

    for(int i = 1; i < argc;i++){
        waitpid(-1,&status,0);
    }

    return 0;
}