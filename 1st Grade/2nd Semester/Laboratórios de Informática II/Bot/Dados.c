#include <stdlib.h>
#include "Dados.h"
#include "Logicadoprograma.h"
#include <string.h>


/**===============================================CAMADA DOS DADOS====================================================*/

                                        //----Funções de inicialização:----//

/** Função que inicia o array das jogadas com Coordenadas a -1.*/
void start_jogadas(ESTADO *e) {
    for (int i = 0; i < 32; i++){
        e->jogadas[i] = (JOGADA) {(COORDENADA){-1,-1}, (COORDENADA){-1,-1}};
    }
}

/** Função que inicializa um estado vazio e com o tabuleiro inicializado.*/
ESTADO *inicializar_estado() {

    ESTADO *e =  (ESTADO *) calloc(1, sizeof(ESTADO));

    e->jogador_atual = 1;
    e->num_jogadas = 0;
    start_jogadas(e);
    e->ultima_jogada.linha = 3;
    e->ultima_jogada.coluna = 4;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            e->tab[i][j] = VAZIO;
    }

    e->tab[0][7] = DOIS;
    e->tab[7][0] = UM;
    e->tab[3][4] = BRANCA;

    e->num_comando = 1;
    e->ultimo_comando.cmd = 0;
    e->ultimo_comando.n_pos = -1;

    return e;
}


                                //----Funções que devolvem um certo dado do ESTADO----//

/** Função que devolve o número do jogador atual.*/
int obter_jogador_atual(ESTADO *estado){
    return estado->jogador_atual;
}

/** Função que devolve o número de jogadas que foram efetuadas (cada jogada contém os dois movimentos dos jogadores).*/
int obter_numero_de_jogadas(ESTADO *estado){
    return estado->num_jogadas;
}

/** Função que devolve a coordenada da última jogada efetuada.*/
COORDENADA obter_ultimajogada(ESTADO *e){
    return (e->ultima_jogada);
}

/** Função que devolve o nº de comandos usados no prompt.*/
int obter_numero_comando(ESTADO *estado){
    return estado->num_comando;
}

/** Função que devolve a CASA dado uma COORDENADA.*/
CASA obter_estado_casa(ESTADO *e, COORDENADA c){
    int col, lin;
    col=c.coluna;
    lin=c.linha;

    return e->tab[lin][col];
}

/** Função que devolve o último comando executado.*/
int obter_ultimo_comand(ESTADO *e){
    return e->ultimo_comando.cmd;
}

/** Função que retorna a coordenada da jogada dado um ESTADO, o número da jogada e o número do jogador.*/
COORDENADA obter_coord_jogadaX(ESTADO *e, int num, int plr){
    COORDENADA c1;
    if (plr == 1)
        c1 = e->jogadas[num-1].jogador1;
    else c1 = e->jogadas[num-1].jogador2;
    return c1;
}

/** Função que devole uma certa jogada.*/
JOGADA obter_jogada(ESTADO *e, int n_jogada){
    return e->jogadas[n_jogada -1];
}

/** Função que devolve o nº da jogada, guardado no comando pos.*/
int obter_jog_pos(ESTADO *estado){
    return estado->ultimo_comando.n_pos;
}

                                    //----Funções de atualização de estado----//

/** Função que modifica o ESTADO se a jogada for válida/*/
void atualiza_estado(ESTADO *e, COORDENADA c){
    int i, j, x, y;

    COORDENADA branc = obter_ultimajogada(e);
    i=branc.linha;
    j=branc.coluna;
    x=c.linha;
    y=c.coluna;

    e->tab[i][j] = PRETA;
    e->tab[x][y] = BRANCA;

    if (obter_numero_de_jogadas(e) == 0)
        e->num_jogadas = 1;

    e->ultima_jogada.linha = x;
    e->ultima_jogada.coluna = y;

    if (obter_jogador_atual(e)==1){
        int num = obter_numero_de_jogadas(e);
        e->jogadas[num-1].jogador1 = obter_ultimajogada(e);
        e->jogador_atual = 2;
    }else if (obter_jogador_atual(e)==2){
        int num = obter_numero_de_jogadas(e);
        e->jogadas[num -1].jogador2 = obter_ultimajogada(e);
        e->jogador_atual = 1;
        e->num_jogadas++;
    }
}

/** Função que atualiza o nº da jogada.*/
void atualiza_num_jogada(ESTADO *e,int num_jog){
    e->num_jogadas = num_jog;
}

/** Função que altera o ESTADO conforme vai lendo dados de um tabuleiro.*/
void set_casa(ESTADO *e, COORDENADA c, CASA valor) {
    switch(valor) {
        case '*' :  e->tab[c.linha][c.coluna] = BRANCA; break;
        case '#' :  e->tab[c.linha][c.coluna] = PRETA; break;
        case '1' : e->tab[c.linha][c.coluna] = UM; break;
        case '2' : e->tab[c.linha][c.coluna] = DOIS; break;
        default:
            e->tab[c.linha][c.coluna] = VAZIO;
    }
}

/** Função que introduz uma JOGADA 'jgd' no array de índice 'jogada'-1.*/
void armazenar_jogada(ESTADO *e, JOGADA jgd, int jogada){
    COORDENADA c1 = jgd.jogador1;
    COORDENADA c2 = jgd.jogador2;

    e->jogadas[jogada-1].jogador1 = c1;
    e->jogadas[jogada-1].jogador2 = c2;
}

/** Função que atualiza a última jogada.*/
void atualiza_ultima_jog_e_jogador(ESTADO *e,JOGADA jgd){
    COORDENADA c1 = jgd.jogador1;
    COORDENADA c2 = jgd.jogador2;

    if (c2.linha == -1 && c2.coluna == -1) {
        e->jogador_atual = 2;
        e->ultima_jogada = c1;
    }
    else {
        e->jogador_atual = 1;
        e->ultima_jogada = c2;
    }
}

/** Função que atualiza o nº de comandos.*/
void atualiza_num_comandos(ESTADO *e){
    e->num_comando++;
}

/** Função que copia o nº de comandos de um estado para o outro.*/
void copia_num_comandos(ESTADO *novo,ESTADO *e){
    novo->num_comando = e->num_comando;
}

/** Função que atualiza o último comando executado na estrutura do ESTADO.
 * Usado principalmente para o comando 'pos' que atribui-lhe o numero '5' e guarda o numero de
 * jogada a qual se pretende retroceder */
void atualiza_comando(ESTADO *e, char *cmd, int num){
    if (num == -1) {
        if (strcmp(cmd, "movs") == 0)
            e->ultimo_comando.cmd = 2;
        else if (strcmp(cmd, "gr") == 0)
            e->ultimo_comando.cmd = 3;
        else if (strcmp(cmd, "ler") == 0)
            e->ultimo_comando.cmd = 4;
        else if (strcmp(cmd, "jog") == 0)
            e->ultimo_comando.cmd = 6;
        else if (strcmp(cmd, "jog2") == 0)
            e->ultimo_comando.cmd = 7;
        else if (strcmp(cmd, "Q") == 0)
            e->ultimo_comando.cmd = 8;
        else if (strcmp(cmd, "tab") == 0)
            e->ultimo_comando.cmd = 9;
        else e->ultimo_comando.cmd = 1;
    } else
        e->ultimo_comando = (COMANDO) {5, num};
}

/** Função que atualiza o ESTADO quando o comando 'pos' é executado.*/
void executa_jogada(ESTADO *e, JOGADA play){
    COORDENADA pl1 = play.jogador1;
    COORDENADA pl2 = play.jogador2;

    COORDENADA branc = obter_ultimajogada(e);
    e->tab[branc.linha][branc.coluna] = PRETA;

    if (jogada_completa(play)==1){
        e->tab[pl1.linha][pl1.coluna] = PRETA;
        e->tab[pl2.linha][pl2.coluna] = BRANCA;
        e->jogador_atual = 1;
        e->ultima_jogada = pl2;
    } else {
        e->tab[pl1.linha][pl1.coluna] = BRANCA;
        e->jogador_atual = 2;
        e->ultima_jogada = pl1;
    }
    e->num_jogadas++;
}

/**===================================================================================================================*/
