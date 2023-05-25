#ifndef SHAFA_D_H
#define SHAFA_D_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "dados.h"

// Lista ligada de array com código e o caractér em código ASCII associado ao respetivo código.
typedef struct lista
{
    char code[8];
    char c;
    struct lista *prox;
} *Lista;

// Árvore em que cada nodo corresponde a um caractér
typedef struct btree
{
    char nodo;
    struct btree *right;
    struct btree *left;
} *Btree;

//---------------------------------------------COD------------------------------------------

// Função que coloca o conteúdo do ficheiro cod num buffer.
char* readcod(FILE *fp);

// Função que calcula o comprimento de um array de char
int length (char a[]);

//Função que filtra o buffer do ficheiro cod, devolvendo o índice que indica onde começa o conteúdo do cod
int bufcod(char buf[]);

// Função que divide o buffer resultante do ficheiro cod, transformando o mesmo numa matriz em que cada linha corresponde a um bloco.
void divide_bufcod (char *buf, int n_blocos, char** matriz);

// Função que insere na cabeça da lista um código e o respetivo caratér.
Lista insere_cabeca ( char* code, char c , Lista l);

// Função que, dado o buffer, transforma o seu conteúdo numa lista ligada.
Lista buf_to_list(char* buffer, Lista lista);

//Função que, dado um array, retorna esse array sem o primeiro elemento.
char* tail ( char a[]);

// Função que, dado uma árvore, cria um nodo adicional na árvore.
Btree altera_nodo (char i, Btree t);

//Função que dado um array a e um inteiro i, devolve o array a com i elementos
char* take(char a[], int i);

//Função que procura o sítio onde deve colocar o elemento e o coloca o har c nesse local da árvore t (Funcionando quase como árvore de procura)
Btree bseek(char a[], Btree t,char c);

//Função que constrói a árvore t dado um array e um caractér c
Btree constroi_arvore(char a[], Btree t, char c);

// Função que, dada uma lista, usa o seu conteúdo para transformar numa árvore.
Btree list_tree (Lista l);

// Função que recebe o ficheiro e faz a descodificação do ficheiro cod
Btree decode_block(char* a);

// Função usada para ler o ficheiro cod e implementar a descodificação feita com as funções anteriores.
char** decode_cod(char *fp_cod, int num_blocos,int *len_cod);

//---------------------------------------------SHAF------------------------------------------

//Função que coloca o conteúdo do ficheiro shaf num buffer.
unsigned char* readshaf(FILE *fp);

//Função que retorna o índice onde começa o conteúdo do shaf.
int bufshaf(unsigned char buf[]);

// Função que divide o buffer resultante do ficheiro shaf, transformando o mesmo numa matriz em que as linhas correspondem aos blocos.
void divide_bufshaf (unsigned char *buf, int n_blocos, unsigned char** matriz, int *len);

//Função que dado um buffer, transforma o seu conteúdo em binário.
unsigned char* shaf_to_bin(unsigned char* buffer, int len);

//Função que verifica se um dado nodo numa árvore é nodo final ou não
int verifica_folha(Btree t);

//Função que limpa um ficheiro com nome fn
FILE* limpaficheiro( char* fn);

//Função que escreve no ficheiro a descodificação dos blocos shaf
void descodificacao(FILE *fp, unsigned char* block,int len_block, Btree topo,int len_txt);

//Função que devolve um array com o tamanho dos blocos txt.
int * len_block_txt(char *buf,int num_blocos,int*len_txt);

//Função que devolve um array com o tamanho dos blocos shaf.
int *len_block_shaf(FILE* shaf,int num_blocos, int* len_shaf);

//Função que devolve um array com o tamanho dos blocos cod.
int *len_block_cod(char* buf,int num_blocos, int* len_cod);

//Função que, recebe os nomes dos ficheiros cod e shaf e descodifica, escrevendo num ficheiro com nome filename.
void decode_shaf(char* fp_shaf,char *fp_cod, char* filename);

//---------------------------------------------RLE---------------------------------------------

//Função que divide o buffer resultante do ficheiro RLE, transformando o mesmo numa matriz em que as linhas correspondem aos blocos.
char **divide_rle(char* buffer,int num_blocos, char**matriz_rle,int*len_block);

//Função designada para imprimir caractéres repetidos no ficheiro fp.
void imprime_repetidos(FILE* fp, char* buffer, int i);

//Função que descodifica um bloco escrevendo o mesmo no ficheiro fp.
void decode_block_rle(char* buffer,int len_block, FILE* fp);

//Função que, dado um ficheiro rle e o ficheiro rle.cod, escreve a descodificação no ficheiro filename.
void decode_rle(char* fp_rle,char* fp_freq, char* filename);

//---------------------------------------------OUTPUT------------------------------------------

//Função que imprime o output
void output(FILE*cod,FILE*shaf,double tempo,char*nomefinal);

//---------------------------------------------MAIN--------------------------------------------

//Função usada para alterar a extensão dos ficheiros
char* nome_rle_txt(char*filename);

//Função que executa o módulo D
SINAL moduloD(char* filename, int descm_RLE, int descm_SF);

#endif //SHAFA_D_H