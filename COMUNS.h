#ifndef PROJETO_COMUNS_H
#define PROJETO_COMUNS_H

void printprompt (ESTADO e);

ESTADO novojogo(char *peca);

void escreve_txt (ESTADO e,char *file,char *modo,char *peca, char *bot);

void printa(ESTADO);

void score (ESTADO e);

ESTADO muda_jogador(ESTADO e);

int jogoAcabou(ESTADO e,Posicao *jogadas,int acaba);

void menu();

void menuBOT();

#endif //PROJETO_COMUNS_H
