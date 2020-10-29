//
// Created by Carlos Beiramar on 2019-04-21.
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "estado.h"
#include "bot.h"
#include "stack.h"
#include "COMUNS.h"
#include "interpretadorBOT.h"

/*
 * Todas as seguintes funções define , servem para definir as zonas do tabuleiro conforme a sua utilidade para jogar
 */

void define_amarelo(Posicao *amarelo){

    amarelo[0].x=0;                                                                 amarelo[1].x=0;
    amarelo[0].y=0;                                                                 amarelo[1].y=7;

    amarelo[2].x=7;                                                                 amarelo[3].x=7;
    amarelo[2].y=0;                                                                 amarelo[3].y=7;
}

void define_vermelho(Posicao *vermelho){

                        vermelho[0].x=0;                        vermelho[3].x=0;
                        vermelho[0].y=1;                        vermelho[3].y=6;

    vermelho[2].x=1;    vermelho[1].x=1;                        vermelho[4].x=1;    vermelho[5].x=1;
    vermelho[2].y=0;    vermelho[1].y=1;                        vermelho[4].y=6;    vermelho[5].y=7;

    vermelho[6].x=6;    vermelho[7].x=6;                        vermelho[9].x=6;    vermelho[11].x=6;
    vermelho[6].y=0;    vermelho[7].y=1;                        vermelho[9].y=6;    vermelho[11].y=7;

                        vermelho[8].x=7;                        vermelho[10].x=7;
                        vermelho[8].y=1;                        vermelho[10].y=6;
}

void define_azul_claro(Posicao *azul_claro){

                    azul_claro[4].x=0;  azul_claro[5].x=0;  azul_claro[6].x=0;  azul_claro[7].x=0;
                    azul_claro[4].y=2;  azul_claro[5].y=3;  azul_claro[6].y=4;  azul_claro[7].y=5;

    azul_claro[0].x=2;                                                                          azul_claro[8].x=2;
    azul_claro[0].y=0;                                                                          azul_claro[8].y=7;
    azul_claro[1].x=3;                                                                          azul_claro[9].x=3;
    azul_claro[1].y=0;                                                                          azul_claro[9].y=7;
    azul_claro[2].x=4;                                                                          azul_claro[10].x=4;
    azul_claro[2].y=0;                                                                          azul_claro[10].y=7;
    azul_claro[3].x=5;                                                                          azul_claro[11].x=5;
    azul_claro[3].y=0;                                                                          azul_claro[11].y=7;

                    azul_claro[12].x=7; azul_claro[13].x=7; azul_claro[14].x=7; azul_claro[15].x=7;
                    azul_claro[12].y=2; azul_claro[13].y=3; azul_claro[14].y=4; azul_claro[15].y=5;
}

void define_azul_escuro(Posicao *azul_escuro){
    azul_escuro[0].x=2;
    azul_escuro[0].y=1;
    azul_escuro[1].x=3;
    azul_escuro[1].y=1;
    azul_escuro[2].x=4;
    azul_escuro[2].y=1;
    azul_escuro[3].x=5;
    azul_escuro[3].y=1;

    azul_escuro[4].x=1;
    azul_escuro[4].y=2;
    azul_escuro[5].x=1;
    azul_escuro[5].y=3;
    azul_escuro[6].x=1;
    azul_escuro[6].y=4;
    azul_escuro[7].x=1;
    azul_escuro[7].y=5;

    azul_escuro[8].x=2;
    azul_escuro[8].y=6;
    azul_escuro[9].x=3;
    azul_escuro[9].y=6;
    azul_escuro[10].x=4;
    azul_escuro[10].y=6;
    azul_escuro[11].x=5;
    azul_escuro[11].y=6;

    azul_escuro[12].x=6;
    azul_escuro[12].y=2;
    azul_escuro[13].x=6;
    azul_escuro[13].y=3;
    azul_escuro[14].x=6;
    azul_escuro[14].y=4;
    azul_escuro[15].x=6;
    azul_escuro[15].y=5;
}

void define_verde(Posicao *verde){
    int linhas=0, colunas=0,indice=0;
    for(linhas=2;linhas<6;linhas++){
        for(colunas=2;colunas<6;colunas++){
            verde[indice].x=linhas;
            verde[indice].y=colunas;
            indice++;
        }
    }
}

/*
 * Estas funções recebem o estado, o array de posições que pode jogar, o array com a respetiva cor da zona e o array melhor jogada
 * o objetivo desta função é colocar no melhorjogada a melhor posição para ser jogada
 */

int verifica_vermelho(ESTADO e,Posicao *jogadas, Posicao *vermelho,Posicao *melhorjogada){
    int x = conta_jogadas_possiveis2(e,jogadas);
    int encontrado = 0;
    int i = 0;
    int j = 0;
    while(i < x && encontrado == 0){
        while(j < 12 && encontrado == 0) {
            if ((jogadas[i].x == vermelho[j].x) && (jogadas[i].y == vermelho[j].y)) {
                encontrado = 1;
                melhorjogada[0].x = vermelho[j].x;
                melhorjogada[0].y = vermelho[j].y;
            } else {
                j++;
            }
        }
        i++;
        j = 0;
    }
    return encontrado;
}

int verifica_amarelo(ESTADO e,Posicao *jogadas, Posicao *amarelo,Posicao *melhorjogada){
    int x = conta_jogadas_possiveis2(e,jogadas);
    int encontrado = 0;
    int indice = 0;
    int indice2 = 0;
    while(indice < x && encontrado == 0){
        while(indice2 < 4 && encontrado == 0) {
            if ((jogadas[indice].x== amarelo[indice2].x) && (jogadas[indice].y== amarelo[indice2].y)) {
                encontrado = 1;
                melhorjogada[0].x = amarelo[indice2].x;
                melhorjogada[0].y = amarelo[indice2].y;
            } else {
                indice2++;
            }
        }
        indice++;
        indice2 = 0;
    }
    return encontrado;
}

int verifica_azul_claro(ESTADO e,Posicao *jogadas, Posicao *azul_claro,Posicao *melhorjogada){
    int x = conta_jogadas_possiveis2(e,jogadas);
    int encontrado = 0;
    int indice = 0;
    int indice2 = 0;
    while(indice < x && encontrado == 0){
        while(indice2 < 16 && encontrado == 0) {
            if ((jogadas[indice].x == azul_claro[indice2].x) && (jogadas[indice].y == azul_claro[indice2].y)) {
                encontrado = 1;
                melhorjogada[0].x = azul_claro[indice2].x;
                melhorjogada[0].y = azul_claro[indice2].y;
            } else {
                indice2++;
            }
        }
        indice++;
        indice2 = 0;
    }
    return encontrado;
}

int verifica_azul_escuro(ESTADO e,Posicao *jogadas, Posicao *azul_escuro,Posicao *melhorjogada){
    int x = conta_jogadas_possiveis2(e,jogadas);
    int encontrado = 0;
    int indice = 0;
    int indice2 = 0;
    while(indice < x && encontrado == 0){
        while(indice2 < 16 && encontrado == 0) {
            if ((jogadas[indice].x == azul_escuro[indice2].x) && (jogadas[indice].y == azul_escuro[indice2].y)) {
                encontrado = 1;
                melhorjogada[0].x = azul_escuro[indice2].x;
                melhorjogada[0].y = azul_escuro[indice2].y;
            } else {
                indice2++;
            }
        }
        indice++;
        indice2 = 0;
    }
    return encontrado;
}

int verifica_verde(ESTADO e,Posicao *jogadas, Posicao *verde,Posicao *melhorjogada){
    int x = conta_jogadas_possiveis2(e,jogadas);
    int encontrado = 0;
    int indice = 0;
    int indice2 = 0;
    while(indice < x && encontrado == 0){
        while(indice2 < 12 && encontrado == 0) {
            if ((jogadas[indice].x== verde[indice2].x) && (jogadas[indice].y== verde[indice2].y)) {
                melhorjogada[0].x = verde[indice2].x;
                melhorjogada[0].y = verde[indice2].y;
                encontrado = 1;
            } else {
                indice2++;
            }
        }
        indice++;
        indice2 = 0;
    }
    return encontrado;
}

/*
 * ---------------------------------------------------------------------------------------------------------------------
 */

/*
 * a funcao jogar_peca_bot recebe o estado e o array melhorjogada, e vai alterar o estado conforme o q esta no array
 * melhorjogada.
 */

ESTADO jogar_peca_bot (ESTADO e,Posicao *melhorjogada){
    int joga_linha,joga_coluna;
    joga_linha = melhorjogada[0].x;
    joga_coluna = melhorjogada[0].y;
    int linhas,colunas;

    linhas=(melhorjogada[0].x);
    colunas=(melhorjogada[0].y);

    char l[MAX_BUFFER];
    l[0] = (char)(linhas + 1 + '0');
    char c[MAX_BUFFER];
    c[0] = (char)(colunas + 1 + '0');


    if (jogada_possivel(joga_linha,joga_coluna) && e.grelha[joga_linha][joga_coluna]==VALOR_PONTO){
        if (e.peca == VALOR_X) {
            e.grelha[joga_linha][joga_coluna] = VALOR_X;

        } else if (e.peca == VALOR_O) {
            e.grelha[joga_linha][joga_coluna] = VALOR_O;
        }
        e = converter(e,l,c);
        e = muda_jogador(e);
    }
    return e;
}

/*
 * a funcao jogadaFacil é o modo facil do bot.
 */

ESTADO jogadaFacil(ESTADO e,Posicao *amarelo,Posicao *vermelho,Posicao *azul_escuro,Posicao *azul_claro,Posicao *verde,Posicao *jogadas,Posicao *melhorjogada){

    if(verifica_azul_escuro(e,jogadas,azul_escuro,melhorjogada)){
        e = jogavel(e);
        e = jogar_peca_bot(e, melhorjogada);
    }
    else if(verifica_verde(e,jogadas,verde,melhorjogada)){
        e = jogavel(e);
        e = jogar_peca_bot(e, melhorjogada);
    }
    else if(verifica_vermelho(e,jogadas,vermelho,melhorjogada)){
        e = jogavel(e);
        e = jogar_peca_bot(e, melhorjogada);
    }
    else if(verifica_azul_claro(e,jogadas,azul_claro,melhorjogada)){
        e = jogavel(e);
        e = jogar_peca_bot(e, melhorjogada);
    }
    else if(verifica_amarelo(e,jogadas,amarelo,melhorjogada)){
        e = jogavel(e);
        e = jogar_peca_bot(e, melhorjogada);
    }
    return e;
}

/*
 * a funcao jogadaMedio é o modo medio do bot.
 */
ESTADO jogadaMedio(ESTADO e,Posicao *melhorjogada){
    e=jogavel(e);
    e=jogar_peca_bot(e,melhorjogada);
    return e;
}

/*
 * a funcao jogaDificl é o modo dificl do bot.
 */

ESTADO jogaDificl(ESTADO e,Posicao *amarelo,Posicao *vermelho,Posicao *azul_escuro,Posicao *azul_claro,Posicao *verde,Posicao *jogadas,Posicao *melhorjogada){

    if(verifica_amarelo(e,jogadas,amarelo,melhorjogada)){
        e = jogavel(e);
        e = jogar_peca_bot(e, melhorjogada);
    }
    else if(verifica_azul_claro(e,jogadas,azul_claro,melhorjogada)){
        e = jogavel(e);
        e = jogar_peca_bot(e, melhorjogada);
    }
    else if(verifica_vermelho(e,jogadas,vermelho,melhorjogada)){
        e = jogavel(e);
        e = jogar_peca_bot(e, melhorjogada);
    }
    else if(verifica_azul_escuro(e,jogadas,azul_escuro,melhorjogada)){
        e = jogavel(e);
        e = jogar_peca_bot(e, melhorjogada);
    }
    else if(verifica_verde(e,jogadas,verde,melhorjogada)){
        e = jogavel(e);
        e = jogar_peca_bot(e, melhorjogada);
    }
    return e;
}

/*
 * a funcao bot_joga vai mostrar a jogada do bot conforme o nivel escolhido.
 */
ESTADO bot_joga(ESTADO e,char *bot, Posicao *amarelo,Posicao *vermelho,Posicao *azul_escuro,Posicao *azul_claro,Posicao *verde,Posicao *jogadas,Posicao *melhorjogada){
    int x;
    define_amarelo(amarelo);
    define_vermelho(vermelho);
    define_azul_claro(azul_claro);
    define_azul_escuro(azul_escuro);
    define_verde(verde);

    if(bot[0] == '1'){
        x=conta_jogadas_possiveis2(e,jogadas);
        if (x>0) {
            e = jogadaFacil(e, amarelo, vermelho, azul_escuro, azul_claro, verde, jogadas,melhorjogada);
            printf("\n");
            e = limpa_pontos(e);
            score(e);
            printf("Jogada do bot -> (%d,%d)\n",melhorjogada[0].x+1,melhorjogada[0].y+1);
            x = conta_jogadas_possiveis2(e, jogadas);
            printf("Jogadas possiveis: %d\n", x);
            printa(e);
        }
        else{
            printf("O bot nao tem uma jogada possivel.\n");
            e=muda_jogador(e);
            printa(e);
        }
    }
    else if(bot[0] == '2'){
        x=conta_jogadas_possiveis2(e,jogadas);
        if(x>0) {
            melhor_jogada(melhorjogada,e,jogadas);
            e = jogadaMedio(e, melhorjogada);
            printf("\n");
            e = limpa_pontos(e);
            score(e);
            printf("Jogada do bot -> (%d,%d)\n",melhorjogada[0].x+1,melhorjogada[0].y+1);
            x = conta_jogadas_possiveis2(e, jogadas);
            printf("Jogadas possiveis: %d\n", x);
            printa(e);
        }
        else{
            printf("O bot nao tem uma jogada possivel.\n");
            e=muda_jogador(e);
            printa(e);
        }
    }
    else if(bot[0] == '3'){
        x = conta_jogadas_possiveis2(e,jogadas);
        if(x > 0) {
            e = jogaDificl(e, amarelo, vermelho, azul_escuro, azul_claro, verde, jogadas, melhorjogada);
            printf("\n");
            e = limpa_pontos(e);
            score(e);
            printf("Jogada do bot -> (%d,%d)\n",melhorjogada[0].x+1,melhorjogada[0].y+1);
            x = conta_jogadas_possiveis2(e, jogadas);
            printf("Jogadas possiveis: %d\n", x);
            printa(e);
        }
        else {
            printf("O bot nao tem uma jogada possivel.\n");
            e=muda_jogador(e);
            printa(e);
        }
    }
    return e;
}