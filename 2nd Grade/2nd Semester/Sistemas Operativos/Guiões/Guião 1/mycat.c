#include "files.h"


int main(int argc,char *argv[]){

    void *buffer = malloc(BUFF_SIZE);
    int bytes_read;

    while((bytes_read = read(0,buffer,BUFF_SIZE)) > 0){
        write(1,buffer,bytes_read);
    } 
}