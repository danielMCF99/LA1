#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H
#define MAX_BUFFER 1024
#define TRUE 0
#define FALSE 1


/**
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/


// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O,VALOR_PONTO,MELHOR_JOGADA} VALOR;


/**
Estrutura que armazena o estado do jogo
*/
typedef struct estado {
    VALOR peca; // peça do jogador que vai jogar!
    VALOR grelha[8][8];
    //char bot; // dificuldade em que se está a jogar! 1-> facil, 2-> medio, 3-> dificil
} ESTADO;

typedef struct posicao {
    int x, y;
} Posicao;

ESTADO converter(ESTADO e,char *l, char *c);

int jogada_possivel (int l, int c);

ESTADO leFicheiro (ESTADO e,char *peca,char *modo,char *bot, char *file);

ESTADO jogar_peca (ESTADO e, char *l,char *c,char *flag,Posicao *jogadas);

ESTADO jogavel(ESTADO e);

ESTADO limpa_pontos(ESTADO e);

void melhor_jogada(Posicao *melhorjogada,ESTADO e,Posicao *jogadas);

void pontosArray(ESTADO e,char temp[8][8]);

void mete_ajuda(ESTADO e,Posicao *melhorjogada, char temp[8][8],Posicao* jogadas);

void printaPontos(char temp[8][8]);

int conta_jogadas_possiveis2 (ESTADO e,Posicao *jogadas);

#endif //PROJ_ESTADO_H