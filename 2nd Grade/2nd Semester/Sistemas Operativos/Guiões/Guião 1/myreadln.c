#include "files.h"


/* 3. Implemente a leitura de uma linha (i.e. sequência terminada por \n) numa função readln:
        ssize_t readln(int fd, char *line, size_t size); */

ssize_t myreadln(int fd,char *line,size_t size){

    ssize_t i;
    
    for(i = 0;i < size - 1;i++){
        ssize_t bytes = read(fd,&line[i],1);
        if(bytes < 1) break;
        if(line[i] == '\n') break;
    }
    i++;
    line[i] = 0;
    return i;
}

/* 4. Implemente, utilizando a função readln, um programa com funcionalidade similar ao comando nl,
que numera as linhas recebidas no seu standard input. */

int main(int argc,char *argv[]){

    char *line_buffer = (char *) malloc(BUFF_SIZE * sizeof (char));
    ssize_t bytes_read;
    int i = 1;

    while((bytes_read = myreadln(0,line_buffer,BUFF_SIZE)) > 0){
        char line_number[BUFF_SIZE];
        sprintf(line_number,"%*d ",5,i++);
        write(1,line_number,strlen(line_number));
        
        write(1,line_buffer,bytes_read);
    }
}