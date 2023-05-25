#include "estrategia.h"
#include <stdlib.h>
#include "Interface.h"

/**==================================BOT DO JOGO DE MESA: "RASTROS"==================================================*/


int main(int argc, char *argv[ ]) {

    if (argc < 2)
        exit(0);

    else {
        ESTADO  *provisorio = inicializar_estado();

        ler(provisorio ,argv[1]);


        int plr = obter_jogador_atual(provisorio);
        COORDENADA branc = obter_ultimajogada(provisorio);

        estrategia_main(provisorio, plr, branc);

        gravar(provisorio,argv[2]);


        free(provisorio);
    }
    return 0;
}


/**===================================================================================================================*/
