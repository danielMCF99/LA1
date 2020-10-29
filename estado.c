#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include "estado.h"
#include "COMUNS.h"
#include "interpretadorBOT.h"
#include "interpretador.h"
#include "stack.h"

ESTADO leFicheiro (ESTADO e,char *peca,char *modo,char *bot ,char *file) {
    int linhas = 0, colunas = 0;
    char aux;
    FILE *ficheiro = NULL;

    ficheiro = fopen(file, "r");
    fscanf(ficheiro,"%s",modo);

    if(modo[0]=='A') {
        fscanf(ficheiro, "%s %s", peca, bot);
    }else{
        fscanf(ficheiro,"%s",peca);
    }

    if(peca[0]=='O'){e.peca=VALOR_O;}
    else if(peca[0]=='X'){e.peca=VALOR_X;}

    for (linhas=0;linhas<8;linhas++){
        for (colunas=0; colunas<8; colunas++){
            fscanf(ficheiro," %c",&aux);
            if (aux=='-'){
                e.grelha[linhas][colunas] = VAZIA;
            }
            else if (aux == 'X'){
                e.grelha[linhas] [colunas] = VALOR_X;
            }
            else if (aux =='O'){
                e.grelha[linhas][colunas] = VALOR_O;
            }
        }
    }
    fclose(ficheiro);
    if(modo[0]=='M'){menu();}else if(modo[0]=='A'){menuBOT();}
    score(e);
    printf("\n");
    printf("%s",modo);
    if(e.peca==VALOR_O) {
        printf(" O");
    }
    else if(e.peca==VALOR_X){
        printf(" X");
    }
    if(bot[0] == '1'){
        printf(" 1");
    }
    else if(bot[0] == '2'){
        printf(" 2");
    }
    else if(bot[0] == '3'){
        printf(" 3");
    }
    printa(e);
    push(e);
    return e;
}

/*
 * Função para converter peças
 */
ESTADO converter(ESTADO e,char *l, char *c){
    int a = 0, b = 0,linhas,colunas,li,lc;
    linhas=(l[0]-'0')-1;
    colunas=(c[0]-'0')-1;

    VALOR jogadorAD = ' ';
    if (e.peca == VALOR_X) {
        jogadorAD = VALOR_O;
    }
    else if (e.peca == VALOR_O) {
        jogadorAD = VALOR_X;
    }

    for (li=0;li<8;li++) {                                  //CICLOS para mudar uma peça
        for (lc = 0; lc < 8; lc++) {
            if (li == linhas && lc == colunas) {
                a = linhas + 1;
                b = colunas;
                while(e.grelha[a][b]==jogadorAD){
                    a++;
                }
                if (e.grelha[a][b]==e.peca){
                    a--;
                }
                while (e.grelha[a][b] == jogadorAD) {
                    e.grelha[a][b] = e.peca;
                    a--;
                }
                a = linhas - 1;
                b = colunas;
                while (e.grelha[a][b]==jogadorAD){
                    a--;
                }
                if (e.grelha[a][b]==e.peca){
                    a++;
                }
                while (e.grelha[a][b] == jogadorAD) {
                    e.grelha[a][b] = e.peca;
                    a++;
                }

                a = linhas;
                b = colunas + 1;
                while(e.grelha[a][b]==jogadorAD && b<8){
                    b++;
                }
                    if (e.grelha[a][b] == e.peca) {
                        b--;
                    }
                while (e.grelha[a][b] == jogadorAD && b<8) {

                    e.grelha[a][b] = e.peca;
                    b--;
                }
                a = linhas;
                b = colunas - 1;
                while(e.grelha[a][b]==jogadorAD){
                    b--;
                }
                if(e.grelha[a][b]==e.peca){
                    b++;
                }
                while (e.grelha[a][b] == jogadorAD) {
                    e.grelha[a][b] = e.peca;
                    b++;
                }
                a = linhas - 1;
                b = colunas - 1;
                while(e.grelha[a][b]==jogadorAD){
                    a--;
                    b--;
                }
                if (e.grelha[a][b]==e.peca){
                    a++;b++;
                }
                while (e.grelha[a][b] == jogadorAD) {
                    e.grelha[a][b] = e.peca;
                    a++;
                    b++;
                }
                a = linhas - 1;
                b = colunas + 1;
                while (e.grelha[a][b]==jogadorAD){
                    a--;b++;
                }
                if (e.grelha[a][b]==e.peca){
                    a++;b--;
                }
                while (e.grelha[a][b] == jogadorAD) {
                    e.grelha[a][b] = e.peca;
                    a++;
                    b--;
                }

                a = linhas + 1;
                b = colunas - 1;
                while(e.grelha[a][b]==jogadorAD){
                    a++;b--;
                }
                if (e.grelha[a][b]==e.peca){
                    a--;b++;
                }
                while (e.grelha[a][b] == jogadorAD) {
                    e.grelha[a][b] = e.peca;
                    a--;
                    b++;
                }

                a = linhas + 1;
                b = colunas + 1;
                while(e.grelha[a][b]==jogadorAD){
                    a++;b++;
                }
                if(e.grelha[a][b]==e.peca){
                    a--;b--;
                }
                while (e.grelha[a][b] == jogadorAD) {
                    e.grelha[a][b] = e.peca;
                    a--;
                    b--;
                }
            }
        }
    }
    return e;
}


/*
 * A funcao que se segue verifica se uma posicao está dentro do tabuleiro ou nao.
 */
int jogada_possivel (int l, int c){
    int res;
    if (l>=0 && l<8 && c>=0 && c<8 ){res=1;}
    else{res=0;}
    return res;
}

/*
FUNCAO JOGAR_PECA:

 Inicialmente verifica se a posicao que o jogador jogou é valida, se for valida coloca lá a peca que está a ser jogada
 no momento. De seguida percorre o tabuleiro até ir à posicao onde o jogador jogou e vai mudar as pecas(função converter) conforme a sua
 jogada.

 MUDAR JOGADOR: Após este processo alterámos a peça a ser jogada.

*/
ESTADO jogar_peca (ESTADO e, char *l,char *c, char *flag,Posicao *jogadas) {
    int joga_linha, joga_coluna,x;
    joga_linha = l[0] - '0';
    joga_linha--;
    joga_coluna = c[0] - '0';
    joga_coluna--;
    if (jogada_possivel(joga_linha, joga_coluna) && e.grelha[joga_linha][joga_coluna] == VALOR_PONTO) {
        if (e.peca == VALOR_X) {
            e.grelha[joga_linha][joga_coluna] = VALOR_X;
        } else if (e.peca == VALOR_O) {
            e.grelha[joga_linha][joga_coluna] = VALOR_O;
        }
        flag[0] = 1;
        e = converter(e,l,c);
        e = muda_jogador(e);
        e = limpa_pontos(e);
        menu();
        x = conta_jogadas_possiveis2(e,jogadas);
        printf("Jogadas possiveis: %d\n", x);
        score(e);
        printa(e);
    }
    else{
        e = limpa_pontos(e);
        printf("Posicao invalida.\n");
        printa(e);
        flag[0] = 0;
    }
    return e;
}
 /*
  * a Funcao jogavel ajuda-nos a perceber as posições onde os jogadores podem jogar, alterando o estado para colocar um ponto nessa posição
  * recebe como argumento o estado atual
  *
  * NOTA : Daí a criação da função limpa pontos , para fazer com que o estado deixe de ter os pontos
  */

ESTADO jogavel(ESTADO e){
    int a,b;
    int l,c;

    VALOR jogadorAd = ' ';
    if (e.peca == VALOR_X) {
        jogadorAd = VALOR_O;
    }
    else if (e.peca == VALOR_O) {
        jogadorAd = VALOR_X;
    }

    for(l=0;l<8;l++) {
        for (c=0;c<8;c++) {
            //VERIFICAR A DIAGONAL DA ESQUERDA PARA A DIREITA PARA CIMA
            if (e.grelha[l][c] == e.peca) {
                a = l - 1;
                b = c - 1;
                if (e.grelha[a][b] == jogadorAd && jogada_possivel(a, b)) {
                    while (jogada_possivel(a, b) && e.grelha[a][b] == jogadorAd && a>0 && b>0) {
                        a--;
                        b--;
                    }
                    if (e.grelha[a][b]==VAZIA) {
                        e.grelha[a][b] = VALOR_PONTO;
                    }
                }
            }

            //VERIFICAR PARA CIMA
            if (e.grelha[l][c] == e.peca) {
                a = l - 1;
                b = c;
                if (e.grelha[a][b] == jogadorAd && jogada_possivel(a, b)) {
                    while (jogada_possivel(a, b) && e.grelha[a][b] == jogadorAd && a>0) {
                        a--;
                    }
                    if (e.grelha[a][b]==VAZIA) {
                        e.grelha[a][b] = VALOR_PONTO;
                    }
                }
            }

            //TESTAR DIAGONAL DA DIREITA PARA A ESQUERDA PARA CIMA
            if (e.grelha[l][c] == e.peca) {
                a = l - 1;
                b = c + 1;
                if (e.grelha[a][b] == jogadorAd && jogada_possivel(a, b)) {
                    while (e.grelha[a][b] == jogadorAd && jogada_possivel(a, b) && a>0 && b<7) {
                        a--;
                        b++;
                    }
                    if (e.grelha[a][b]==VAZIA) {
                        e.grelha[a][b] = VALOR_PONTO;
                    }
                }
            }


            //TESTAR CAMINHO PARA A ESQUERDA
            if (e.grelha[l][c] == e.peca) {
                a = l;
                b = c - 1;
                if (e.grelha[a][b] == jogadorAd && jogada_possivel(a, b)) {
                    while (jogada_possivel(a, b) && e.grelha[a][b] == jogadorAd && b>0) {
                        b--;
                    }
                    if (e.grelha[a][b]==VAZIA) {
                        e.grelha[a][b] = VALOR_PONTO;
                    }
                }
            }

            //TESTAR CAMINHO PARA A DIREITA
            if (e.grelha[l][c] == e.peca) {
                a = l;
                b = c + 1;
                if (e.grelha[a][b] == jogadorAd && jogada_possivel(a, b)) {
                    while (jogada_possivel(a, b) && e.grelha[a][b] == jogadorAd && b<7) {
                        b++;
                    }
                    if (e.grelha[a][b]==VAZIA) {
                        e.grelha[a][b] = VALOR_PONTO;
                    }
                }
            }

            //TESTAR DIAGONAL ESQUERDA PARA BAIXO
            if (e.grelha[l][c] == e.peca) {
                a = l+1;
                b = c-1;
                if(e.grelha[a][b]==jogadorAd && jogada_possivel(a, b)) {
                    while (jogada_possivel(a, b) && e.grelha[a][b] == jogadorAd && a<7 && b>0) {
                        a++;
                        b--;
                    }
                    if (e.grelha[a][b]==VAZIA) {
                        e.grelha[a][b] = VALOR_PONTO;
                    }
                }
            }

            //TESTAR CAMINHO PARA BAIXO
            if (e.grelha[l][c]==e.peca) {
                a = l + 1;
                b = c;
                if(e.grelha[a][b]==jogadorAd && jogada_possivel(a, b)) {
                    while (jogada_possivel(a, b) && e.grelha[a][b] == jogadorAd && a<7) {
                        a++;
                    }
                    if (e.grelha[a][b]==VAZIA) {
                        e.grelha[a][b] = VALOR_PONTO;
                    }
                }
            }

            //TESTAR DIAGONAL DIREITA PARA BAIXO
            if (e.grelha[l][c]==e.peca) {
                a = l + 1;
                b = c + 1;
                if (e.grelha[a][b]==jogadorAd && jogada_possivel(a, b)) {
                    while (jogada_possivel(a, b) && e.grelha[a][b] == jogadorAd && a<7 && b<7) {
                        a++;
                        b++;
                    }
                    if (e.grelha[a][b]==VAZIA) {
                        e.grelha[a][b] = VALOR_PONTO;
                    }
                }
            }
        }
    }
    return e;
}

int conta_jogadas_possiveis2 (ESTADO e,Posicao *jogadas){
    e=jogavel(e);
    int conta=0,indice=0;
    for (int l=0;l<8;l++){
        for(int c=0;c<8;c++){
            if(e.grelha[l][c]==VALOR_PONTO){
                conta++;
                jogadas[indice].x=l;
                jogadas[indice].y=c;
                indice++;
            }
        }
    }
    return conta;
}

ESTADO limpa_pontos(ESTADO e){
    int l=0,c=0;
    for (l=0;l<8;l++){
        for (c=0;c<8;c++){
            if(e.grelha[l][c]==VALOR_PONTO){
                e.grelha[l][c]=VAZIA;
            }
        }
    }
    return e;
}
/*
 * a funcao pontosArray recebe o estado e um array temp como argumentos
 * coloca no array temp o estado e faz printf deste array para mostrar ao utilizador os sitios onde pode jogar
 * nao retorna nada
 */

void pontosArray(ESTADO e,char temp[8][8]) {
    e = jogavel(e);
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(e.grelha[x][y] == VALOR_X){
                temp[x][y] = 'X';
            }
            if(e.grelha[x][y] == VALOR_O){
                temp[x][y] = 'O';
            }
            if(e.grelha[x][y] == VAZIA){
                temp[x][y] = '-';
            }
            if(e.grelha[x][y] == VALOR_PONTO){
                temp[x][y] = '.';
            }
        }
    }
    printf("\n");
    printaPontos(temp);
}

void printaPontos(char temp[8][8]){

    int numero = 1;
    printf("  1 2 3 4 5 6 7 8\n");
    for (int i=0; i<8; i++) {
        printf("%d ", numero);
        numero++;
        for (int j=0; j<8; j++) {
            printf("%c ",temp[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
 * Como melhor jogada nos consideramos a posição que come mais peças
 * recebe um array com as posições que pode jogar, o estado e um array onde vai colocar a posição da melhor jogada
 */

void melhor_jogada(Posicao *melhorjogada,ESTADO e,Posicao *jogadas){
    VALOR jogadorAD = ' ';
    int a=0,b=0,linhas,colunas;
    int conta=0,x=0,indice=0,indice2=0;
    int jogadaspossiveis;

    if (e.peca == VALOR_X) {
        jogadorAD = VALOR_O;
    }
    else if (e.peca == VALOR_O) {
        jogadorAD = VALOR_X;
    }

    jogadaspossiveis=conta_jogadas_possiveis2(e,jogadas);

    if (jogadaspossiveis!=0) {

        while (jogadaspossiveis > 0) {

            linhas = jogadas[indice].x;
            colunas = jogadas[indice].y;

            a = linhas + 1;
            b = colunas;
            while (e.grelha[a][b] == jogadorAD) {
                a++;
            }
            if (e.grelha[a][b] == e.peca) {
                a--;
            }
            while (e.grelha[a][b] == jogadorAD) {
                conta++;
                a--;
            }
            if (conta > x) {
                x = conta;
                melhorjogada[indice2].x = jogadas[indice].x;
                melhorjogada[indice2].y = jogadas[indice].y;
            }
            conta = 0;
            a = linhas - 1;
            b = colunas;
            while (e.grelha[a][b] == jogadorAD) {
                a--;
            }
            if (e.grelha[a][b] == e.peca) {
                a++;
            }
            while (e.grelha[a][b] == jogadorAD) {
                conta++;
                a++;
            }
            if (conta > x) {
                x = conta;
                melhorjogada[indice2].x = jogadas[indice].x;
                melhorjogada[indice2].y = jogadas[indice].y;
            }
            conta = 0;
            a = linhas;
            b = colunas + 1;
            while (e.grelha[a][b] == jogadorAD) {
                b++;
            }
            if (e.grelha[a][b] == e.peca) {
                b--;
            }
            while (e.grelha[a][b] == jogadorAD) {
                conta++;
                b--;
            }
            if (conta > x) {
                x = conta;
                melhorjogada[indice2].x = jogadas[indice].x;
                melhorjogada[indice2].y = jogadas[indice].y;
            }
            conta = 0;
            a = linhas;
            b = colunas - 1;
            while (e.grelha[a][b] == jogadorAD) {
                b--;
            }
            if (e.grelha[a][b] == e.peca) {
                b++;
            }
            while (e.grelha[a][b] == jogadorAD) {
                conta++;
                b++;
            }
            if (conta > x) {
                x = conta;
                melhorjogada[indice2].x = jogadas[indice].x;
                melhorjogada[indice2].y = jogadas[indice].y;
            }
            conta = 0;
            a = linhas - 1;
            b = colunas - 1;
            while (e.grelha[a][b] == jogadorAD) {
                a--;
                b--;
            }
            if (e.grelha[a][b] == e.peca) {
                a++;
                b++;
            }
            while (e.grelha[a][b] == jogadorAD) {
                conta++;
                a++;
                b++;
            }
            if (conta > x) {
                x = conta;
                melhorjogada[indice2].x = jogadas[indice].x;
                melhorjogada[indice2].y = jogadas[indice].y;
            }
            conta = 0;
            a = linhas - 1;
            b = colunas + 1;
            while (e.grelha[a][b] == jogadorAD) {
                a--;
                b++;
            }
            if (e.grelha[a][b] == e.peca) {
                a++;
                b--;
            }
            while (e.grelha[a][b] == jogadorAD) {
                conta++;
                a++;
                b--;
            }
            if (conta > x) {
                x = conta;
                melhorjogada[indice2].x = jogadas[indice].x;
                melhorjogada[indice2].y = jogadas[indice].y;
            }
            conta = 0;

            a = linhas + 1;
            b = colunas - 1;
            while (e.grelha[a][b] == jogadorAD) {
                a++;
                b--;
            }
            if (e.grelha[a][b] == e.peca) {
                a--;
                b++;
            }
            while (e.grelha[a][b] == jogadorAD) {
                conta++;
                a--;
                b++;
            }
            if (conta > x) {
                x = conta;
                melhorjogada[indice2].x = jogadas[indice].x;
                melhorjogada[indice2].y = jogadas[indice].y;
            }
            conta = 0;
            a = linhas + 1;
            b = colunas + 1;
            while (e.grelha[a][b] == jogadorAD) {
                a++;
                b++;
            }
            if (e.grelha[a][b] == e.peca) {
                a--;
                b--;
            }
            while (e.grelha[a][b] == jogadorAD) {
                conta++;
                a--;
                b--;
            }
            if (conta > x) {
                x = conta;
                melhorjogada[indice2].x = jogadas[indice].x;
                melhorjogada[indice2].y = jogadas[indice].y;
            }
            conta = 0;
            indice++;
            jogadaspossiveis--;
        }
    }
}

/*
 * A funcao mete_ajuda vai ao array melhorjogada,o qual so tem uma posicao porque e a posicao que come mais,
 * e vai imprimir nessa posicao um ponto de interrogacao sempre que o utilizador desejar.
 */
void mete_ajuda(ESTADO e,Posicao *melhorjogada, char temp[8][8],Posicao *jogadas){
    int jogadasposiveis=0;
    jogadasposiveis=conta_jogadas_possiveis2(e,jogadas);
    if (jogadasposiveis>0) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (e.grelha[x][y] == VALOR_X) {
                    temp[x][y] = 'X';
                }
                if (e.grelha[x][y] == VALOR_O) {
                    temp[x][y] = 'O';
                }
                if (e.grelha[x][y] == VAZIA) {
                    temp[x][y] = '-';
                }
            }
        }
        temp[melhorjogada[0].x][melhorjogada[0].y]='?';
        printf("Melhor jogada: (%d,%d)\n",melhorjogada[0].x+1,melhorjogada[0].y+1);
        printf("\n");
        printaPontos(temp);
    }else {
        printf("Nao tem jogadas possiveis.\n");
        printa(e);
    }
}