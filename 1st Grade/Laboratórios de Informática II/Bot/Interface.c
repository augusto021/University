#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "Dados.h"
#include "Listas.h"
#include "Logicadoprograma.h"
#define BUF_SIZE 1024

/**=============================================CAMADA DA INTERFACE===================================================*/

                                    //----Funções relativas a impressão do tabuleiro----//

/** Função que imprime uma casa do tabuleiro.*/
void imprime_casa(FILE *fp, ESTADO *e, int lin, int col){
    COORDENADA c = {lin,col};
    CASA home = obter_estado_casa(e, c);

    switch (home)
    {
        case DOIS:
            fputc('2', fp); break;
        case BRANCA:
            fputc('*', fp); break;
        case PRETA:
            fputc('#', fp); break;
        case UM:
            fputc('1', fp); break;
        default:
            fputc('.', fp);
    }
}


/** Função que imprime o tabuleiro e o prompt.*/
void mostrar_tabuleiro(FILE *fp, ESTADO *e) {
    int i, j;
    for (i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
            imprime_casa(fp, e, i, j);
        fputc('\n', fp);
    }
    fputc('\n', fp);

}

                    //----Funções print que servem para imprimir ERROS e os Movimentos----//

/** Função que imprime os erros para o jogador.*/
int print_erro(ERROS erro){
    if (erro == OK)
        return 1;
    if (erro == COORDENADA_INVALIDA)
        printf("Digitou uma coordenada inválida!\n");
    if (erro == JOGADA_INVALIDA)
        printf("A jogada é inválida!\n");
    if (erro == ERRO_LER_TAB)
        printf("Erro ao tentar ler o tabuleiro!");
    if (erro==ERRO_ABRIR_FICHEIRO)
        printf("Erro ao tentar abrir o ficheiro");
    return 0;
}

/** Função que imprime o movimento do jogador 1.*/
void print_mov(FILE *fp, COORDENADA c, int jogada){
    char j[3];

    strcpy(j, coord_to_str(c));

    fprintf(fp, "%02d: %s\n", jogada, j);
}

/** Função que recebe um ESTADO e um nº que corresponde ao nº de jogadas e imprime essa linha.*/
void print_jogadas_completas(ESTADO *e, FILE *fp, int jogada){

    COORDENADA c1 = obter_coord_jogadaX(e, jogada, 1);
    COORDENADA c2 = obter_coord_jogadaX(e, jogada, 2);
    char j1[3], j2[3];
    strcpy(j1, coord_to_str(c1));
    strcpy(j2, coord_to_str(c2));

    fprintf(fp, "%02d: %s %s\n", jogada, j1, j2);

}

                    /**----Função principal responsável pelo comando 'movs----*/

/** Função que imprime os movimentos num File, usada para imprimir os movs logo a seguir ao tabuleiro.*/
int movimentos(ESTADO *e, FILE *fp){
    int n = obter_numero_de_jogadas(e), num =1;
    int plr = obter_jogador_atual(e);


    if (n==0)
        fprintf(fp, "Erro! Não foram efetuadas jogadas!\n");
    else {
        if (n==1 && plr==2){
            print_mov(fp,obter_ultimajogada(e),n);
        }
        else
            if (plr==2) {
                while (num < n){
                    print_jogadas_completas(e,fp,num);
                    num++;
                }
                print_mov(fp,obter_ultimajogada(e),n);
            } else{
            while (num<n){
                print_jogadas_completas(e,fp,num);
                num++;
            }
        }
    }
    return 1;
}

                            /**----Função principal responsável pelo comando 'gr'----*/

/** Função que grava o Estado do jogo num ficheiro.*/
int gravar(ESTADO *e, char c[]){
    FILE * fp;
    fp = fopen(c, "w");

    mostrar_tabuleiro(fp, e);
    movimentos(e,fp);

    fclose(fp);
    return 1;
}

                            /**----Função principal responsável pelo comando 'ler'----*/

/** Função que lê os dados de um ficheiro e modifica o Estado.*/
int ler(ESTADO *e, char c[]){
    ERROS erro;
    FILE * fp;
    fp = fopen(c, "r");
    if (fp == NULL) {
        erro = ERRO_LER_TAB;
        print_erro(erro);
        return 1;
    }
    else {
        char buffer[BUF_SIZE];
        int num_jog;
        char jog1[BUF_SIZE];
        char jog2[BUF_SIZE];
        int l = 0, col;
        while(fgets(buffer, BUF_SIZE, fp) != NULL) {
            if (l<8) {
                for (col = 0; col < 8; col++)
                    set_casa(e, (COORDENADA) {l, col}, buffer[col]);
            }
            else {
                int num_tokens = sscanf(buffer, "%02d: %s %s", &num_jog, jog1, jog2);
                if (num_tokens == 3) {
                    COORDENADA c1 = str_to_coord(jog1);
                    COORDENADA c2 = str_to_coord(jog2);
                    armazenar_jogada(e, (JOGADA) {c1, c2}, num_jog);
                    atualiza_num_jogada(e,num_jog+1);
                    atualiza_ultima_jog_e_jogador(e, (JOGADA) {c1,c2});
                } else if (num_tokens == 2){
                    COORDENADA c1 = str_to_coord(jog1);
                    COORDENADA c2 = {-1, -1};
                    armazenar_jogada(e, (JOGADA) {c1, c2}, num_jog);
                    atualiza_num_jogada(e,num_jog);
                    atualiza_ultima_jog_e_jogador(e, (JOGADA) {c1,c2});
                } else{
                    if (num_tokens==0) {
                        ESTADO *tmp = inicializar_estado();
                        *e=*tmp;
                        free(tmp);
                    }
                }
            }
            l++;
        }
    }
        fclose(fp);
        return 1;
}

                        /**----Funções principais responsáveis pelo comando 'pos'----*/

/** Função que mostra o Estado anterior sem alterar o atual.*/
void pos_nao_atualiza(ESTADO *e, int n_jogada){
    ESTADO *novo = inicializar_estado();

    for (int i=1; i<=n_jogada; i++)
        armazenar_jogada(novo, obter_jogada(e, i), i);

    for (int j=1; j<=n_jogada; j++)
        executa_jogada(novo, obter_jogada(novo, j));

    mostrar_tabuleiro(stdout, novo);

    free(novo);
}

/** Função que altera o Estado atual por um anterior.*/
void pos_atualiza(ESTADO *e, int n_jogada){
    ESTADO *novo = inicializar_estado();

    for (int i=1; i<=n_jogada; i++)
        armazenar_jogada(novo, obter_jogada(e, i), i);

    for (int j=1; j<=n_jogada; j++)
        executa_jogada(novo, obter_jogada(novo, j));

    atualiza_num_jogada(novo, n_jogada+1);

    copia_num_comandos(novo, e);

    *e =*novo;
    free(novo);
}

                    /**----Funções principais responsáveis pelos comandos 'jog' e 'jog2'----*/

/** Função que joga automaticamente de acordo com a Herística Euclidiana.*/
int jogada_automatica(ESTADO *e){
    if (obter_jogador_atual(e)==1){
        COORDENADA branc = obter_ultimajogada(e);
        LISTA l1 = armazena_branca(e,branc);
        COORDENADA melhor = jogadaEclidiana(e, l1, 1);
        atualiza_estado(e,melhor);
    } else{
        COORDENADA branc = obter_ultimajogada(e);
        LISTA l1 = armazena_branca(e,branc);
        COORDENADA melhor = jogadaEclidiana(e, l1, 2);
        atualiza_estado(e,melhor);
    }
    return 1;
}

/** Função que gera uma jogada automática mas aleatória.*/
COORDENADA jog(ESTADO *e){
    COORDENADA c = obter_ultimajogada(e);
    LISTA L = armazena_branca(e,c);
    srand((unsigned)time(NULL));
    int a = (rand() %length_lista(L));
    for(;L && L->prox && a>0;a--)
        L = remove_cabeca(L);
    COORDENADA c1 = (*(COORDENADA*) devolve_cabeca(L));
    return c1;
}

                        /**----Função responsável por imprimir o prompt do jogo----*/

/** Função que corresponde ao prompt do jogo.*/
void prompt(ESTADO*e){
    int num = obter_numero_de_jogadas(e), n;
    if (num == 0)
        n = 1;
    else n = num;
    printf("# %02d Jogador: %d {%d}->>>  ", obter_numero_comando(e), obter_jogador_atual(e), n);
}

                /**----Funções responsáveis por intrepertar as jogadas e os comandos do jogo----*/

/** Função que interpreta só os comandos do joga.*/
int comandos(ESTADO *e, char *linha){
    char comando[BUF_SIZE];
    char arg[1024];
    int num;
    ERROS erro;

    sscanf(linha, "%s %s", comando, arg);

    if (strcmp(comando, "Q")==0)
        return 0;
    else if (strcmp(comando, "gr")==0 && strcmp(arg, "Estado.txt")==0){
        atualiza_comando(e,comando, -1);
        return gravar(e, arg);
    }
    else if(strcmp(comando, "ler")==0 && strcmp(arg, "Estado.txt")==0) {
        atualiza_comando(e,comando, -1);
        return ler(e,arg);
    }
    else if (strcmp(comando, "pos")==0){
        num = atoi(arg);
        if (pos_valido(e, num)==1) {
            atualiza_comando(e, comando, num);
            pos_nao_atualiza(e, num);
            return 1;
        }
    }
    else if (strcmp(comando, "movs")==0){
        atualiza_comando(e,comando, -1);
        return movimentos(e, stdout);
    }
    else if(strcmp(comando, "jog2")==0) {
        atualiza_comando(e,comando, -1);
        return jogada_automatica(e);
    }
    else if(strcmp(comando,"jog")==0){
        atualiza_comando(e,comando, -1);
        COORDENADA c = jog(e);
        atualiza_estado(e,c);
        return 1;
    }
    else if (strcmp(comando, "tab")==0){
        atualiza_comando(e,comando,-1);
        mostrar_tabuleiro(stdout,e);
        return 1;
    }
    else{
        erro = JOGADA_INVALIDA;
        print_erro(erro);
        return 1;
    }
    return 1;
}

/** Função que representa o interpretador do jogo.*/
int interpretador(ESTADO *e) {
    char comando[BUF_SIZE];
    char col[2], lin[2];

    if (comand_pos(e)==0 && obter_ultimo_comand(e)!=2 && obter_ultimo_comand(e)!=9)
        mostrar_tabuleiro(stdout, e);
    prompt(e);

    if (fgets(comando, BUF_SIZE, stdin) == NULL)
        return 0;

    else if (strlen(comando) == 3 && sscanf(comando, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {'8' - *lin, *col - 'a'};
        ERROS erro;
            if (comand_pos(e) == 1) {
                pos_atualiza(e, obter_jog_pos(e));
                if ((erro = jogar(e, coord)) == OK) {
                    atualiza_estado(e, coord);
                    atualiza_comando(e,"jogada", -1);
                } else
                    print_erro(erro);
            } else {
                if ((erro = jogar(e, coord)) == OK) {
                    atualiza_estado(e, coord);
                    atualiza_comando(e, "jogada", -1);
                } else
                    print_erro(erro);
            }
            return 1;

        }else
            return comandos(e,comando);

}

/**===================================================================================================================*/
