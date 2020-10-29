#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "interpretador.h"
#include "interpretadorBOT.h"
#include "estado.h"
#include "bot.h"
#include "stack.h"
#include "COMUNS.h"

ESTADO interpretar (ESTADO e, char *linha){
    char cmd[MAX_BUFFER];
    char peca[MAX_BUFFER];
    char file[MAX_BUFFER];
    char modo[MAX_BUFFER];
    char l[MAX_BUFFER];
    char c[MAX_BUFFER];
    char bot[MAX_BUFFER];
    char temp[8][8];
    char flag[1];                       //flag para o modo de jogo com o bot, que marca se o utilizador ja jogou ou nao
    Posicao jogadas[MAX_BUFFER];        //jogadas possiveis num array
    Posicao melhorjogada[1];            //mete a melhor jogada no array
    int x;
    int n;
    int acabou=FALSE;

    Posicao amarelo[4];                 //posicoes do tabuleiro(ver cor no algoritmo minimax
    Posicao vermelho[12];               //posicoes do tabuleiro(ver cor no algoritmo minimax
    Posicao azul_claro[16];             //posicoes do tabuleiro(ver cor no algoritmo minimax
    Posicao azul_escuro[16];            //posicoes do tabuleiro(ver cor no algoritmo minimax
    Posicao verde[16];

    sscanf(linha,"%s",cmd);
    switch (toupper(cmd[0])){

        case 'N':                                                //PARA NOVO JOGO
            n=sscanf(linha,"%s %s",cmd,peca);
            if (n==2){
                modo[0]='M';
                e=novojogo(peca);
                menu();
                push(e);
                x = conta_jogadas_possiveis2(e, jogadas);
                printf("Jogadas possiveis: %d\n",x);
                score(e);
                printa(e);
            }
            else {
                printf("erro: é preciso um paramentro\n");
            }
            break;

        case 'L':                                                //PARA LER UM JOGO DE FICHEIRO
            n = sscanf(linha,"%s %s",cmd,file);
            if (n==2){
                e=leFicheiro(e,peca,modo,bot,file);
                if(modo[0]=='A'){
                    interpretadorBOT(e,bot,peca);
                }
            }
            else {
                printf("erro: precisa de outro parametro\n");
            }
            break;

        case 'E':                                                //ESCREVER EM FICHEIRO ESTADO DO JOGO (DAR save)
            n = sscanf(linha,"%s %s",cmd,file);

            if (n==2){
                escreve_txt(e, file,modo,peca,bot);
                printa(e);
                menu();
            }
            else {
                printf("erro: precisa de outro parametro\n");
            }
            break;

        case 'J':                                   //JOGAR PEÇA ATUAL NA POSICAO L C
            n=sscanf(linha,"%s %s %s",cmd,l,c);
            if (n==3) {
                    x = conta_jogadas_possiveis2(e, jogadas);
                    if (x > 0) {
                        e = jogavel(e);
                        e = jogar_peca(e, l, c,flag,jogadas);
                        e = limpa_pontos(e);
                        push(e);
                        acabou = jogoAcabou(e, jogadas, acabou);
                        if (acabou == TRUE) {
                            printf("O jogo acabou pois nenhum jogador tem jogadas possíveis.\n");
                            score(e);
                            exit(0);
                        }
                    }
                    else {
                        menu();
                        printf("Nao tem jogadas possiveis:\n"
                               "\tP -> passar a vez.\n"
                               "\tU -> para dar undo\n");
                    }
            }
            else if(n<3){
                printf("erro:precisa de outro parametro\n");
            }
            else if(n>3){
                printf("erro:tem parametros a mais");
            }
            break;
        case 'P':
            n=sscanf(linha,"%s",cmd);
            if(n==1 && conta_jogadas_possiveis2(e,jogadas)==0){
                e=muda_jogador(e);
                menu();
                printa(e);
            }else{
                printf("Erro nos parametros");
            }
            break;

        case 'S':                                   //PARA IMPRIMIR UM PONTO NAS POSICOES DE JOGADA VALIDA
            n=sscanf(linha,"%s",cmd);
            if (n==1){
                x = conta_jogadas_possiveis2(e, jogadas);
                if(x>0) {
                    menu();
                    pontosArray(e, temp);
                }else {printf("\nNao tem jogadas possiveis:\n"
                              "\tP -> passar a vez.\n"
                              "\tU -> para dar undo\n");
                menu();
                printf("\n");
                }
            }
            else{printf("parametros a mais.\n");}
            break;

        case 'H':                           //PARA SUGERIR UMA JOGADA
        n=sscanf(linha,"%s",cmd);
        if(n==1) {
            melhor_jogada(melhorjogada, e, jogadas);
            printf("\n");
            score(e);
            menu();
            mete_ajuda(e,melhorjogada,temp,jogadas);

        }
        else{
            printf("Erro nos parametros");
        }
            break;

        case 'U':                           //DAR UNDO
            pop();
            ESTADO jogadaAnterior;
            jogadaAnterior=elementoTopo();
            limpa_pontos(jogadaAnterior);
            e=jogadaAnterior;
            menu();
            x = conta_jogadas_possiveis2(e, jogadas);
            printf("Jogadas possiveis: %d\n", x);
            score(e);
            printa(e);
            break;

        case 'A':               //PECA NIVEL, JOGO CONTRA O BOT COM A PECA E O NIVEL DE DIFICULDADE
            n=sscanf(linha,"%s %s %s",cmd,peca,bot);
            if(n==3){
                e=novojogo(peca);
                if(toupper(peca[0]) == 'O') {
                    e.peca = VALOR_X;
                    menuBOT();
                    e = bot_joga(e,bot,amarelo, vermelho, azul_escuro, azul_claro, verde, jogadas,
                                 melhorjogada);
                    push(e);
                    interpretadorBOT(e, bot, peca);
                }
                else if(toupper(peca[0]) == 'X'){
                    menuBOT();
                    printa(e);
                    push(e);
                    interpretadorBOT(e,bot,peca);
                }
            }
            else if(n>3){printf("tem parametros a mais.\n");}
            else if (n<3){printf("erro:precisa de outro parametro\n");}
            break;

        case 'Q':
            exit(0);

        default:
            printf("Comando invalido (rtfm)!\n");
    }
    return e;
}

void interpretador (ESTADO e){
    char linha[MAX_BUFFER];
    menu();
    printprompt (e);
    while (fgets (linha,MAX_BUFFER,stdin)){
        e=interpretar(e,linha);
        printprompt (e);

    }
}