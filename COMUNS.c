#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "estado.h"
#include "interpretadorBOT.h"
#include "bot.h"
#include "stack.h"

void printa(ESTADO e){
    char c = ' ';
    int numero=1;
    printf("\n");
    printf("  1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ",numero);
        numero++;
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VALOR_PONTO:{
                    c = '.';
                    break;
                }
                case MELHOR_JOGADA:{
                    c='?';
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
            }
            printf("%c ", c);

        }
        printf("\n");
    }
    printf("\n");
}

/*
 * Esta funcao vai atualizando sobre a quantidade de pecas de cada jogador durante o jogo.
 */
void score (ESTADO e){
    int l=0,c=0;
    int contaX=0,contaY=0;
    for (l=0;l<8;l++){
        for (c=0;c<8;c++){
            if (e.grelha[l][c]==VALOR_X){
                contaX++;
            }else if(e.grelha[l][c]==VALOR_O){
                contaY++;
            }
        }
    }
    printf("JogadorX: %d\n"
           "JodagorO: %d\n",contaX,contaY);
}

ESTADO novojogo(char *peca){
    ESTADO e={0};
    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;

    if(peca[0]=='O'){e.peca=VALOR_O;}
    else if(peca[0]=='X'){e.peca=VALOR_X;}

    switch (toupper(peca[0])){
        case 'X':
            e.peca = VALOR_X;
            break;
        case 'O':
            e.peca = VALOR_O;
            break;
        default:
            printf("A peça tem de ser X ou O \n");
    }
    return e;
}

void printprompt (ESTADO e){
    switch (e.peca){
        case VALOR_X:
            printf("Reversi X ►");
            break;
        case VALOR_O:
            printf("Reversi O ►");
            break;
        default:
            printf("Reversi ? ►");
            break;
    }
}

void escreve_txt (ESTADO e,char *file,char *modo,char *peca,char *bot){
    int linhas=0,colunas=0;
    FILE *ficheiro = NULL;

    if(modo[0] == 'M') {
        ficheiro = fopen(file, "w");
        fprintf(ficheiro,"%c %c\n",modo[0],toupper(peca[0]));

        for (linhas = 0; linhas < 8; linhas++) {
            for (colunas = 0; colunas < 8; colunas++) {
                if (e.grelha[linhas][colunas] == VAZIA) {
                    fprintf(ficheiro, " %c", '-');
                }
                if (e.grelha[linhas][colunas] == VALOR_X) {
                    fprintf(ficheiro, " %c", 'X');
                }
                if (e.grelha[linhas][colunas] == VALOR_O) {
                    fprintf(ficheiro, " %c", 'O');
                }
            }
            fprintf(ficheiro, "\n");
        }
        fclose(ficheiro);
    }
    if(modo[0] == 'A'){
        ficheiro = fopen(file,"w");
        fprintf(ficheiro,"%c %c %c\n",modo[0],toupper(peca[0]),bot[0]);

        for (linhas = 0; linhas < 8; linhas++) {
            for (colunas = 0; colunas < 8; colunas++) {
                if (e.grelha[linhas][colunas] == VAZIA) {
                    fprintf(ficheiro, " %c", '-');
                }
                if (e.grelha[linhas][colunas] == VALOR_X) {
                    fprintf(ficheiro, " %c", 'X');
                }
                if (e.grelha[linhas][colunas] == VALOR_O) {
                    fprintf(ficheiro, " %c", 'O');
                }
            }
            fprintf(ficheiro, "\n");
        }
        fclose(ficheiro);
    }
}

/*
 * Função para alterar o jogo conforme se vai jogando
 */
ESTADO muda_jogador(ESTADO e){
    if (e.peca==VALOR_X){
        e.peca=VALOR_O;
    }
    else if(e.peca==VALOR_O){
        e.peca=VALOR_X;
    }
    return e;
}

/*
 * Função que retorna TRUE se o jogo acabou ou FALSE caso algum jogador ainda tenha jogadas possiveis
 */
int jogoAcabou(ESTADO e,Posicao *jogadas,int acaba){
    ESTADO e2;
    int x,y;
    x=conta_jogadas_possiveis2(e,jogadas);
    e2=muda_jogador(e);
    y=conta_jogadas_possiveis2(e2,jogadas);
    if(x==0 && y==0){
        acaba=TRUE;
    }else{
        acaba=FALSE;
    }
    return acaba;
}

void menuBOT (){
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━MENU_BOT━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃\t                                                                                       ┃\n");
    printf("┃\t[N] <peca>         ➤ para novo jogo onde o primeiro jogador é o jogador peca.          ┃\n");
    printf("┃\t[L] <ficheiro>     ➤ para ler um jogo do ficheior.                                     ┃\n");
    printf("┃\t[E] <ficheiro>     ➤ para guardar o estado do ficheiro.                                ┃\n");
    printf("┃\t[J] <L> <C>        ➤ jogar peça atual na posição (L,C).                                ┃\n");
    printf("┃\t[P]                ➤ para passar a vez.                                                ┃\n");
    printf("┃\t[S]                ➤ para imprimir '.' nas jogadas possíveis.                          ┃\n");
    printf("┃\t[H]                ➤ para imprimir '?' na jogada recomendade.                          ┃\n");
    printf("┃\t[U]                ➤ para dar undo.                                                    ┃\n");
    printf("┃\t[Q]                ➤ para terminar o programa.                                         ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n");
}

void menu (){
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━MENU━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃\t                                                                                       ┃\n");
    printf("┃\t[N] <peca>         ➤ para novo jogo onde o primeiro jogador é o jogador peca.          ┃\n");
    printf("┃\t[L] <ficheiro>     ➤ para ler um jogo do ficheior.                                     ┃\n");
    printf("┃\t[E] <ficheiro>     ➤ para guardar o estado do ficheiro.                                ┃\n");
    printf("┃\t[J] <L> <C>        ➤ jogar peça atual na posição (L,C).                                ┃\n");
    printf("┃\t[P]                ➤ para passar a vez.                                                ┃\n");
    printf("┃\t[S]                ➤ para imprimir '.' nas jogadas possíveis.                          ┃\n");
    printf("┃\t[H]                ➤ para imprimir '?' na jogada recomendade.                          ┃\n");
    printf("┃\t[U]                ➤ para dar undo.                                                    ┃\n");
    printf("┃\t[A] <peca> <nivel> ➤ começar novo jogo com o bot.                                      ┃\n");
    printf("┃\t[Q]                ➤ para terminar o programa.                                         ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n");
}
