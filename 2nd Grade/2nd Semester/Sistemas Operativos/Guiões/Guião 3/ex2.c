#include "files.h"

/* Implemente um programa semelhante ao anterior que execute o mesmo comando mas agora no contexto
de um processo filho */

int main(int argc,const char* argv[]){
    pid_t pid;

    if((pid = fork()) == 0){
        execlp("ls","ls","-l",NULL);
    }

    return 0;
}