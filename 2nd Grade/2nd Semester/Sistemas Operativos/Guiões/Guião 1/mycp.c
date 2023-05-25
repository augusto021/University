#include "files.h"


int main(int argc,char *argv[]){
    int fd_origem = open(argv[1],O_RDONLY,0600);
    int fd_destino = open(argv[2],O_CREAT | O_TRUNC | O_WRONLY, 0600);

    if(fd_origem == -1){
        perror("Open Ficheiro Origem");
        exit(-1);    
    }

    char buffer[BUFF_SIZE];
    int bytes_read;

    while((bytes_read = read(fd_origem,buffer,BUFF_SIZE)) > 0){
        write(fd_destino,buffer,bytes_read);
    }

    close(fd_origem);
    close(fd_destino);
    exit(0);
}