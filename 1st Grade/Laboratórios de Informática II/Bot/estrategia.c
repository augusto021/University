#include "estrategia.h"
#include "Logicadoprograma.h"
#include "Interface.h"

/**=============================================CAMADA DA ESTRATÉGIA===================================================*/


/** Função que define as premissas da vitória.*/
int premissas_win(ESTADO *e, int plr, COORDENADA c){

    if (plr == 1) {
        if (c.linha > 5 && c.coluna < 2) {
            atualiza_estado(e, (COORDENADA) {7, 0});
            return 1;
        }
    } else {
        if (c.linha < 2 && c.coluna > 5) {
            atualiza_estado(e, (COORDENADA) {0, 7});
            return 1;
        }
    }
    return 0;
}

/** Função que efetua a primeira jogada se é o caso.*/
void first_play(ESTADO *e, int plr, COORDENADA c){

    if (plr==1 && c.linha==3 && c.coluna==4)
        atualiza_estado(e,(COORDENADA) {2,5});
    else if (plr==2 && c.linha==4 && c.coluna==3)
        atualiza_estado(e, (COORDENADA) {5,2});
    else jogada_automatica(e);
}

/** Funções que efetuam a segunda e terceira jogada se tudo correr como planeado.*/
void second_third(ESTADO *e, int plr, COORDENADA c){
    ERROS erro = jogar(e,(COORDENADA) {c.linha+1, c.coluna});
    ERROS erro2 = jogar(e, (COORDENADA) {c.linha - 1, c.coluna});

    if (plr ==1){
        if (c.linha <2 && c.coluna > 5 && (erro == OK))
            atualiza_estado(e, (COORDENADA) {c.linha+1, c.coluna}); //jogar para baixo, de forma a bloquear a casa adeversária;
        else jogar_pelas_bordas(e, 1, c);
    }
    else {
        if (plr == 2 && (erro2 == OK))
            atualiza_estado(e, (COORDENADA) {c.linha - 1, c.coluna}); //jogar para cima, de forma a bloquear a casa adeversária;
        else jogar_pelas_bordas(e, 2, c);
    }
}

/** Função que prende a branca, se for possível.*/
int prende_branca(ESTADO *e, COORDENADA c) {
    ESTADO *tmp = inicializar_estado();
    LISTA casas = armazena_branca(e, c);

    while (casas){
        *tmp = *e;
        COORDENADA *coord = devolve_cabeca(casas);
        atualiza_estado(tmp, *coord);
        if (branca_presa(tmp)==1)
            break;
        casas = proximo(casas);
    }
    free(tmp);
    if (casas) {
        atualiza_estado(e, (*(COORDENADA *) casas->variavel));
        return 1;
    } else
        return 0;
}

/** Função auxiliar, da função jogar_pelas_bordas, mas apenas para o jogador1.*/
void jogada_para_player1(ESTADO *e,COORDENADA branc){
    LISTA casas = armazena_branca(e, branc);
    COORDENADA onde_jogar;
    int priority = 10;

    while (casas){
        if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==1 && branc.coluna == 5 && branc.linha==1) {
            onde_jogar = (*(COORDENADA *) casas->variavel);
            priority = 1;
        }
        else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==5 && branc.coluna == 6) {
            if (priority > 1) {
                priority = 2;
                onde_jogar = (*(COORDENADA *) casas->variavel);
            }
        }else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==4 && branc.coluna == 6){
            if (priority > 2){
                priority = 3;
                onde_jogar = (*(COORDENADA *) casas->variavel);
            }
        } else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==6 && branc.coluna == 7) {
            if (priority > 3) {
                priority = 4;
                onde_jogar = (*(COORDENADA *) casas->variavel);
            }
        } else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==8 && branc.linha == 7) {
            onde_jogar = (*(COORDENADA *) casas->variavel);
            priority = 1;
        }else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==5 && branc.linha == 6 && branc.coluna==6) {
            if (priority > 1){
                priority = 2;
                onde_jogar = (*(COORDENADA *) casas->variavel);
            }
        }else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==6 && branc.linha == 6) {
            if (priority > 2){
                priority = 3;
                onde_jogar = (*(COORDENADA *) casas->variavel);
            }
        }else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==7 && branc.linha == 6) {
            if (priority > 3) {
                priority = 4;
                onde_jogar = (*(COORDENADA *) casas->variavel);
            }
        }
        casas = casas->prox;
    }

    if (priority != 10)
        atualiza_estado(e, onde_jogar);
    else
        jogada_automatica(e);
}

/** Função auxiliar, da função jogar_pelas_bordas, mas apenas para o jogador2.*/
void jogada_para_player2(ESTADO *e,COORDENADA branc){
    LISTA casas = armazena_branca(e, branc);
    COORDENADA onde_jogar;
    int priority = 10;


    while (casas){
        if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==3 && branc.coluna == 0){
            onde_jogar = (*(COORDENADA *) casas->variavel);
            priority = 1;
        }else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==8 && branc.coluna == 1){
            if (priority > 1){
                priority = 2;
                onde_jogar = (*(COORDENADA *) casas->variavel);
            }
        } else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==1 && branc.coluna == 1) {
            if (priority > 2) {
                priority = 3;
                onde_jogar = (*(COORDENADA *) casas->variavel);
            }
        } else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==4 && branc.linha == 0) {
            onde_jogar = (*(COORDENADA *) casas->variavel);
            priority = 1;
        }else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==2 && branc.linha == 1) {
            if (priority > 1){
                priority = 2;
                onde_jogar = (*(COORDENADA *) casas->variavel);
            }
        }else if (posicao_em_relacao_branca((*(COORDENADA *) casas->variavel),branc)==3 && branc.linha == 1) {
            if (priority > 2) {
                priority = 3;
                onde_jogar = (*(COORDENADA *) casas->variavel);
            }
        }
        casas = casas->prox;
    }

    if (priority != 10)
        atualiza_estado(e, onde_jogar);
    else
        jogada_automatica(e);
}

/** Função que vai jogando pela borda do tabuleiro, na direção da nossa casa.*/
void jogar_pelas_bordas( ESTADO *e, int plr, COORDENADA branc){
    LISTA casas = armazena_branca(e, branc);

    if (length_lista(casas)==1)
        atualiza_estado(e, (*(COORDENADA *) casas->variavel));
    else {
        if (plr == 1)
            jogada_para_player1(e, branc);
        else
            jogada_para_player2(e,branc);
    }
}

/** Função que retorna a Coordenada que seria a melhor jogada.*/
void jogar_fino(ESTADO *e, int plr, COORDENADA branc){
    if (prende_branca(e, branc)==0){
        jogar_pelas_bordas(e, plr, branc);
    }
}

/** Função que define a estrategia principal do jogo.*/
void estrategia_main(ESTADO *e, int plr, COORDENADA branc){
    int n_jogadas = obter_numero_de_jogadas(e);

    if (premissas_win(e,plr,branc)==0) {

        if (n_jogadas == 0 || n_jogadas == 1)
            first_play(e, plr, branc);
        else {
            if (n_jogadas == 2 || n_jogadas == 3)
                second_third(e, plr, branc);
            else {
                jogar_fino(e, plr, branc);
            }
        }
    }
}


/**===================================================================================================================*/
