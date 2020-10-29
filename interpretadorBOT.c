#include "interpretadorBOT.h"
#include "estado.h"
#include "stack.h"
#include "interpretador.h"
#include "bot.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "COMUNS.h"

ESTADO interpretarBOT (ESTADO e, char *linha,char *bot,char *peca){
    char cmd[MAX_BUFFER];
    char file[MAX_BUFFER];
    char l[MAX_BUFFER];
    char c[MAX_BUFFER];
    char modo[MAX_BUFFER];
    char temp[8][8];
    char flag[1];
    Posicao jogadas[MAX_BUFFER];        //jogadas possiveis num array
    Posicao melhorjogada[1];            //mete a melhor jogada no array
    Posicao amarelo[4];                 //posicoes do tabuleiro(ver cor no algoritmo minimax
    Posicao vermelho[12];               //posicoes do tabuleiro(ver cor no algoritmo minimax
    Posicao azul_claro[16];             //posicoes do tabuleiro(ver cor no algoritmo minimax
    Posicao azul_escuro[16];            //posicoes do tabuleiro(ver cor no algoritmo minimax
    Posicao verde[16];                  //posicoes do tabuleiro(ver cor no algoritmo minimax
    int x;
    int n;
    int acabou=FALSE;

    sscanf(linha,"%s",cmd);
    switch (toupper(cmd[0])) {

        case 'N':                                                //PARA NOVO JOGO
            n = sscanf(linha, "%s %s", cmd, peca);
            if (n == 2) {
                modo[0] = 'A';
                e = novojogo(peca);
                push(e);
                x = conta_jogadas_possiveis2(e, jogadas);
                printf("Jogadas possiveis: %d\n", x);
                score(e);
                printa(e);
            } else {
                printf("erro: é preciso um paramentro\n");
            }
            break;
        case 'E':                                                //ESCREVER EM FICHEIRO ESTADO DO JOGO (DAR save)
            n = sscanf(linha, "%s %s",cmd, file);

            if (n == 2) {
                escreve_txt(e, file, modo, peca,bot);
                printa(e);
            } else {
                printf("erro: precisa de outro parametro\n");
            }
            break;

        case 'L':                                                //PARA LER UM JOGO DE FICHEIRO
            n = sscanf(linha,"%s %s",cmd,file);
            if (n==2){
                e=leFicheiro(e,peca,modo,bot,file);
                if (modo[0] == 'M') {
                    interpretador(e);
                }
            }
            else {
                printf("erro: precisa de outro parametro\n");
            }
            break;

        case 'J':                                   //JOGAR PEÇA ATUAL NA POSICAO L C
            n = sscanf(linha, "%s %s %s", cmd, l, c);
            if (n == 3) {
                acabou = jogoAcabou(e, jogadas, acabou);
                if (acabou == TRUE) {
                    printf("O jogo acabou pois nenhum jogador tem jogadas possíveis.\n");
                    score(e);
                    exit(0);
                } else {
                    x = conta_jogadas_possiveis2(e, jogadas);
                    if (x > 0) {
                        push(e);
                        printf("\n");
                        e = jogavel(e);
                        e = jogar_peca(e, l, c, flag,jogadas);
                        e = limpa_pontos(e);
                        push(e);
                        if (flag[0] == 1) {
                                e = bot_joga(e, bot, amarelo, vermelho, azul_escuro, azul_claro, verde, jogadas,
                                             melhorjogada);
                        }
                        acabou = jogoAcabou(e, jogadas, acabou);
                        if (acabou == TRUE) {
                            printf("O jogo acabou pois nenhum jogador tem jogadas possíveis.\n");
                            score(e);
                            exit(0);
                        }
                        else if(x==0){
                            printf("O bot nao tem jogadas.\n");
                        }
                    }
                    if (x == 0) {
                        printf("Nao tem jogadas possiveis:\n"
                               "\tP -> passar a vez.\n"
                               "\tU -> para dar undo\n");
                    }
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
                menuBOT();
                e=muda_jogador(e);
                e = bot_joga(e,bot,amarelo, vermelho, azul_escuro, azul_claro, verde, jogadas,
                             melhorjogada);
            }else{
                printf("Erro nos parametros");
            }
            break;

        case 'S':                                   //PARA IMPRIMIR UM PONTO NAS POSICOES DE JOGADA VALIDA
            n=sscanf(linha,"%s",cmd);
            if (n==1){
                x = conta_jogadas_possiveis2(e, jogadas);
                if(x>0) {
                    menuBOT();
                    pontosArray(e, temp);
                }else {printf("\nNao tem jogadas possiveis:\n"
                              "\tP -> passar a vez.\n"
                              "\tU -> para dar undo\n");
                    printf("\n");
                }
            }
            else{printf("parametros a mais.\n");}
            break;

        case 'H':                           //PARA SUGERIR UMA JOGADA
            n=sscanf(linha,"%s",cmd);
            if(n==1) {
                melhor_jogada(melhorjogada, e,jogadas);
                printf("\n");
                score(e);
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
            menuBOT();
            x = conta_jogadas_possiveis2(e, jogadas);
            printf("Jogadas possiveis: %d\n", x);
            score(e);
            printa(e);
            break;

        case 'Q':
            exit(0);

        default:
            printf("Comando invalido (rtfm)!\n");
    }
    return e;
}

void interpretadorBOT (ESTADO e,char *bot,char *peca){
    char linha[MAX_BUFFER];
    printprompt (e);
    while (fgets (linha,MAX_BUFFER,stdin)){
        e=interpretarBOT(e,linha,bot,peca);
        printprompt (e);

    }
}