/**
@file Logica do programa.c
Definição das funções da camada da lógica
*/
#include "Dados.h"
#include "Listas.h"
#include <stdlib.h>
#include <string.h>


/**===============================================CAMADA DA LOGICA====================================================*/

/** Função que verifica se o nº inserido no comando "pos" é válido.*/
int pos_valido(ESTADO *e, int num){
    int n = obter_numero_de_jogadas(e);
    if (num >= 0 && num <= n)
        return 1;
    else return 0;
}

/** Função booleana que verifica se o último comando executado foi o pos.*/
int comand_pos(ESTADO *e){
    int cmd = obter_ultimo_comand(e);
    if (cmd == 5)
        return 1;
    else return 0;
}

/** Função que atribui um número as posições a volta da peça branca.*/
int posicao_em_relacao_branca(COORDENADA c, COORDENADA brc){
    int x1, x2, y1, y2, r=0;
    x1 = brc.linha;
    y1 = brc.coluna;
    x2 = c.linha;
    y2 = c.coluna;

    if (x1-x2==1 && y1-y2==1){
        r = 1;                           /** Posição superior esquerda == 1.*/
    }else if(x1-x2==1 && y1-y2==0){
        r = 2;                           /** Posição a cima == 2.*/
    }else if (x1-x2==1 && y2-y1==1){
        r= 3;                            /** Posição superior direita == 3.*/
    }else if (x1-x2==0 && y1-y2==1){
        r=8;                             /** Posição a direita == 4.*/
    }else if (x1-x2==0 && y2-y1==1){
        r = 4;                           /** Posição inferior direita == 5.*/
    }else if (x2-x1==1 && y1-y2==1){
        r = 7;                           /** Posição a baixo == 6.*/
        r = 6;                           /** Posição inferior esquerda == 7.*/
    }else if (x2-x1==1 && y2-y1==1){
        r = 5;                           /** Posição a esquerda == 8.*/
    }
    return  r;
}


/** Função que verifica se uma jogada é completa.*/
int jogada_completa(JOGADA play){
    COORDENADA pl1 = play.jogador1;
    COORDENADA pl2 = play.jogador2;

    if ((pl1.linha!=-1 && pl1.coluna!=-1) && (pl2.linha!=-1 && pl2.coluna!=-1))
        return 1;
    else return 0;
}

/** Função que converte uma COORDENADA para uma string.*/
char* coord_to_str(COORDENADA coord){
    int lin = coord.linha,
        col = coord.coluna;
    char l,c;
    char *crd;
    crd = (char*)malloc(3*sizeof(char));
    c = col + 'a';
    l = '8' - lin;
    crd[0] =  c;
    crd[1] =  l;
    crd[2] = '\0';

    return crd;
}

/** Função que transforma uma string numa jogada.*/
COORDENADA str_to_coord(char str[]){
    int lin, col;
    col = str[0] - 'a';
    lin = '8' -  str[1];
    COORDENADA c = {lin, col};
    return c;
}

/** Função que uma casa está livre, isto é, se é vazia e pertence ao tabuleiro.*/
int casa_livre(ESTADO *e, COORDENADA c){
    int x = c.linha; int y = c.coluna;
    if (x>=0 && y>=0 && x<=7 && y<=7) {
        if (obter_estado_casa(e, c) == UM || obter_estado_casa(e, c) == DOIS || obter_estado_casa(e, c) == VAZIO)
            return 1;
    }
    return 0;

}

/** Função booleana que verifica se a distância da próxima jogada é válida.*/
    int dist_valida(ESTADO *e, COORDENADA c) {
        int x1, x2, y1, y2, r, dif_X, dif_Y;
        COORDENADA branc = obter_ultimajogada(e);
        x1 = branc.linha;
        y1 = branc.coluna;
        x2 = c.linha;
        y2 = c.coluna;
        dif_X = x1 - x2;
        dif_Y = y1 - y2;
        if ((x1 == x2 && abs(dif_Y) == 1) || (y1 == y2 && abs(dif_X) == 1) || (abs(dif_X) == 1 && abs(dif_Y) == 1))
            r = 1;
        else r = 0;
        return r;
    }

/** Função booleana que verifica se a próxima jogada é válida.*/
    int jogada_valida(ESTADO *e, COORDENADA c) {
        int r;
        if (dist_valida(e, c) == 1 && casa_livre(e, c) == 1)
            r = 1;
        else r = 0;
        return r;
    }

/** Função que retorna o erro OK se a jogada é valida se não retorna o respetivo erro.*/
    ERROS jogar(ESTADO *e, COORDENADA c) {
        ERROS r;
        if (jogada_valida(e, c) == 1) {
            r = OK;
        } else r = JOGADA_INVALIDA;
        return r;
    }

/** Função que atribui um prioridade as casas dependendo do jogador:
 * Para o jogador 1, a prioridade vai aumentando na diagonal, do canto superior direito para o canto inferior esquerdo;
 * Para o jogador 2, a prioridade vai aumentando na diagonal, mas no sentido oposto.*/
    int prioridade_casa(ESTADO *e, int plr, COORDENADA c){
        COORDENADA branc = obter_ultimajogada(e);
        int posicao = posicao_em_relacao_branca(c, branc);
        int r=-1;
        if (plr == 1)
        {
            if (posicao==7)
                r=8;
            else if (posicao== 8 || posicao== 6){
                r=6;
            }else if (posicao==1 || posicao==5){
                r=4;
            }else if (posicao==2 || posicao==4){
                r=2;
            }else if (posicao== 3){
                r=0;
            }
        }
        else{
            if (posicao==7)
                r=0;
            else if (posicao== 8 || posicao== 6){
                r=1;
            }else if (posicao==1 || posicao==5){
                r=3;
            }else if (posicao==2 || posicao==4){
                r=5;
            }else if (posicao== 3){
                r=7;
            }
        }
        return r;
    }

/** Função que recebe um ESTADO e uma LISTA de casas vizinhas vazias e devolve a COORDENADA da melhor jogada segundo a Eurística Euclidiana:
 * Ao invés de calcular a distância, a estratégia foi dando ás casas vazias uma prioridade para cada jogador.
 * Assim esta função começa por percorrer essa lista, comparando dois a dois a prioridade e guardando sempre o maior valor.*/
    COORDENADA jogadaEclidiana(ESTADO *e, LISTA l1, int plr) {
        COORDENADA *melhor = NULL;
        int maior=-1 ,n;

        if (length_lista(l1)==1)
            melhor = (COORDENADA *) l1->variavel;
        else {

            if (plr == 1) {
                while (l1 && l1->prox != NULL) {
                    if (prioridade_casa(e, 1, (*(COORDENADA *) l1->variavel)) >= prioridade_casa(e, 1, (*(COORDENADA *) l1->prox->variavel))) {
                        n = prioridade_casa(e, 1, (*(COORDENADA *) l1->variavel));
                        if (n > maior) {
                            maior = n;
                            melhor = (COORDENADA *) l1->variavel;
                        }
                    }
                    else {
                        n = prioridade_casa(e, 1, (*(COORDENADA *) l1->prox->variavel));
                        if (n > maior) {
                            maior = n;
                            melhor = (COORDENADA *) l1->prox->variavel;
                        }
                    }
                    l1 = l1->prox;
                }
            } else {
                while (l1 && l1->prox != NULL) {
                    if (prioridade_casa(e, 2, (*(COORDENADA *) l1->variavel)) >= prioridade_casa(e, 2, (*(COORDENADA *) l1->prox->variavel))) {
                        n = prioridade_casa(e, 2, (*(COORDENADA *) l1->variavel));
                        if (n > maior) {
                            maior = n;
                            melhor = (COORDENADA *) l1->variavel;
                        }
                    }
                    else {
                        n = prioridade_casa(e, 2, (*(COORDENADA *) l1->prox->variavel));
                        if (n > maior) {
                            maior = n;
                            melhor = (COORDENADA *) l1->prox->variavel;
                        }
                    }
                    l1 = l1->prox;
                }
            }
        }
        return *melhor;
    }

/** Função que verifica se a peça branca está presa e se sim devolve 1, se não retorna 0.*/
    int branca_presa(ESTADO *e) {
        COORDENADA branc = obter_ultimajogada(e);
        LISTA L = armazena_branca(e, branc);
        if (lista_esta_vazia(L) == 1) {
            return 1;
        }
        return 0;
    }


/** Função que verifica se o jogo acabou e se sim então devolve o nº do jogador vencedor, caso contrário devolve zero.*/
    int end_game(ESTADO *e) {
        COORDENADA branc = obter_ultimajogada(e);
        int x, y, r;
        x = branc.linha;
        y = branc.coluna;
        if (x == 0 && y == 7)
            r = 2;
        else {
            if (x == 7 && y == 0) r = 1;
            else {
                if (branca_presa(e) == 1)
                    r = obter_jogador_atual(e) == 1 ? 2 : 1;
                else r = 0;
            }
        }
        return r;
    }

/**===================================================================================================================*/
