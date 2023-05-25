/**
@file Dados.h
Definição do estado e das funções que a manipulam.
*/

#ifndef LI2PL7G05_DADOS_H
#define  LI2PL7G05_DADOS_H
#define BUF_SIZE 1024

/**===============================================CAMADA DOS DADOS====================================================*/

/**
\brief Tipo de dados para os erros.
*/
typedef enum {
    OK,
    COORDENADA_INVALIDA,
    JOGADA_INVALIDA,
    ERRO_LER_TAB,
    ERRO_ABRIR_FICHEIRO
} ERROS;

/**
\brief Tipo de dados para a casa: '1' = jogador 1; '2' = jogador 2; '.' = lugar ainda não utilizado, vazio; '*' = peça branca, só há uma,
é a peça que os jogadores movem ao fazer a jogada; '#' = peça preta, cada vez que os jogadores movem a peça branca, uma peça preta é
colocada nesse lugar.
*/
typedef enum {
    UM = '1',
    DOIS = '2',
    VAZIO = '.',
    BRANCA = '*',
    PRETA = '#'
} CASA;

/**
\brief Tipo de dados para as coordenadas.
*/
typedef struct {
    int linha;
    int coluna;
} COORDENADA;

/**
\brief Tipo de dados para a jogada.
*/
typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;

/**
\brief Tipo de dados para as jogadas.
*/
typedef JOGADA JOGADAS[32];

/**
\brief Tipo de dados para o estado.
*/

typedef struct {
    int cmd;
    int n_pos;
} COMANDO;

typedef struct {
    /** O tabuleiro */
    CASA tab[8][8];
    /** As jogadas */
    JOGADAS jogadas;
    /** O número das jogadas, usado no prompt */
    int num_jogadas;
    /** O jogador atual */
    int jogador_atual;
    /** O nº de comando, usado no prompt */
    int num_comando;
    /** A coordenada da última jogada */
    COORDENADA ultima_jogada;
    COMANDO ultimo_comando;
} ESTADO;

                                   /**----Funções de inicialização:----*/

/**
\brief Função que inicializa o array das jogadas com -1.
@param e Apontador para o ESTADO
@param plays para JOGADAS
*/
void start_jogadas(ESTADO *e);
/**
\brief Função que inicializa um estado vazio e com o tabuleiro inicializado.
*/
ESTADO *inicializar_estado();

                          /**----Funções que devolvem um certo dado do ESTADO----*/

/**
\brief Função que devolve o número do jogador atual.
@param e Apontador para o ESTADO
*/
int obter_jogador_atual(ESTADO *e);

/**
\brief Função que devolve o número de jogadas que foram efetuadas (cada jogada contém os dois movimentos dos jogadores).
@param e Apontador para o ESTADO
*/
int obter_numero_de_jogadas(ESTADO *e);

/**
\brief Função que devolve a coordenada da última jogada efetuada.
@param e Apontador para o ESTADO
*/
COORDENADA obter_ultimajogada(ESTADO *e);

/**
\brief Função que devolve o nº de comandos usados no prompt.
@param e Apontador para o ESTADO
*/
int obter_numero_comando(ESTADO *estado);

/**
\brief Função que devolve a CASA dado uma COORDENADA.
@param e Apontador para o ESTADO
@param c A COORDENADA
*/
CASA obter_estado_casa(ESTADO *e, COORDENADA c);

/**
\brief Função que devolve o último comando executado.
@param e Apontador para o ESTADO
*/
int obter_ultimo_comand(ESTADO *e);

/**
\brief Função que retorna a coordenada da jogada dado um ESTADO, o número da jogada e o número do jogador.
@param e Apontador para o Estado
@param num inteiro para o número da jogada
@param plr inteiro para número do jogador
*/
COORDENADA obter_coord_jogadaX(ESTADO *e, int num, int plr);

/**
\brief Função que devolve uma certa jogada.
@param e Apontador para o ESTADO
@param num inteiro para o número da jogada
*/
JOGADA obter_jogada(ESTADO *e, int n_jogada);

/**
\brief Função que devolve o nº da jogada, guardada no comando pos.
@param e Apontador para o ESTADO
*/
int obter_jog_pos(ESTADO *estado);

                            /**----Funções de atualização de estado----*/

/**
\brief Função que modifica o ESTADO se a jogada for válida.
@param e Apontador para o ESTADO
@param c A coordenada
*/
void atualiza_estado(ESTADO *e, COORDENADA c);

/**
\brief Função que atualiza o nº da jogada.
@param e Apontador para o ESTADO
@param num inteiro para o número da jogada
*/
void atualiza_num_jogada(ESTADO *e,int num_jog);

/**
\brief Função que altera o ESTADO conforme vai lendo dados de um tabuleiro.
@param e Apontador para o ESTADO
@param c variável do tipo COORDENADA
@param valor variável do tipo CASA
*/
void set_casa(ESTADO *e, COORDENADA c, CASA valor);

/**
\brief Função que introduz uma JOGADA 'jgd' no array de índice 'jogada'-1.
@param e Apontador para o ESTADO
@param c variável do tipo JOGADA
@param num inteiro para o número da jogada
*/
void armazenar_jogada(ESTADO *e, JOGADA c, int jogada);

/**
\brief Função que atualiza a última jogada.
@param e Apontador para o ESTADO
@param variável do tipo JOGADA
*/
void atualiza_ultima_jog_e_jogador(ESTADO *e, JOGADA jgd);

/**
\brief Função que atualiza o nº de comandos.
@param e Apontador para o ESTADO
*/
void atualiza_num_comandos(ESTADO *e);

/**
\brief Função que copia o nº de comandos de um estado para o outro.
@param e Apontador para o ESTADO
@param e Apontador para o novo ESTADO
*/
void copia_num_comandos(ESTADO *novo,ESTADO *e);

/**
\brief Função que atualiza o último comando executado na estrutura do ESTADO.
 * Usado principalmente para o comando 'pos' que atribui-lhe o número '5' e guarda o número de
 * jogada a qual se pretende retroceder.
@param e Apontador para o Estado
@param cmd Apontador do tipo char
@param num variável do tipo int
 */
void atualiza_comando(ESTADO *e, char *cmd, int num);

/**
\brief Função que atualiza o ESTADO quando o comando 'pos' é executado.
@param e Apontador para o ESTADO
@param play para JOGADA
*/
void executa_jogada(ESTADO *e, JOGADA play);


#endif //LI2PL7G05_DADOS_H
