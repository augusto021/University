#include "files.h"


/* 5. Considere uma estrutura (struct) com dados de uma pessoa (nome, idade, ...) e um ficheiro binário que
contém registos organizados segundo esta estrutura. Não assuma que o ficheiro cabe todo em memória.
Escreva um programa que, consoante a opção, permita:
    -i - Acrescentar pessoas a um ficheiro de dados binário.
    -u - Atualizar a idade de uma determinada pessoa no ficheiro de dados.
    Exemplos:
    $ pessoas i "José Mourinho" 59
    $ pessoas u "José Mourinho" 60

Meça o tempo que demora a inserir 1.000.000 de pessoas (nomes e idades gerados por si). Observa
alguma degradação de desempenho à medida que o ficheiro cresce? */

int acrescentarPessoa(int fd,const char *name,int idade){
    if(fd == -1) perror("Não foi possível abrir ficheiro!\n");

    Pessoa p;
    strcpy(p.nome,name);
    p.idade = idade;

    lseek (fd, 0, SEEK_END);
    write(fd,&p,sizeof(struct pessoa));

    printf("Inserção concluída com sucesso!\n");
    return 0;
}

int atualizarPessoa(int fd,const char* name,int novaIdade){
    if(fd == -1) perror("Não foi possível abrir ficheiro!\n");

    Pessoa p;
    lseek(fd,0,SEEK_SET);
    int bytes_read;

    while((bytes_read = read(fd,&p,sizeof(struct pessoa))) > 0){
        if(strcmp(p.nome,name) == 0){
            p.idade = novaIdade;
            lseek(fd,-sizeof(struct pessoa),SEEK_CUR);
            write(fd,&p,sizeof(struct pessoa));
        }
    }

    return 0;
}

void verFicheiro(int fd, const char *nome, int idade){
    Pessoa p1; //Cria pessoa
    lseek(fd,0,SEEK_SET);
    int byte_read;
    while((byte_read = read(fd,&p1,sizeof(struct pessoa))) > 0){
        printf("\t--------------------\n");
        printf("\tidade: %d\n\tnome: %s\n",p1.idade,p1.nome);
        printf("\t--------------------\n");
    }
}


int main(int argc, char *argv[]){
    if(argc != 4) perror("Input errado!\n");
    
    int fd = open("registo", O_CREAT | O_RDWR , 0640);
    const char *name = argv[2];
    int idade = atoi(argv[3]);

    switch(*argv[1]){
        case 'i':
            acrescentarPessoa(fd,name,idade);
            break;
        case 'u':
            atualizarPessoa(fd,name,idade);
            break;
        default:
            puts("Erro: modo inválido");
            break;

    }

    verFicheiro(fd,name,idade);
    close(fd);
    return 0;
}