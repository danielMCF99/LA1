//
// Created by Carlos Beiramar on 2019-04-21.
//

#ifndef PROJFINAL_BOT_H
#define PROJFINAL_BOT_H

void define_amarelo(Posicao *amarelo);

void define_vermelho(Posicao *vermelho);

void define_azul_claro(Posicao *azul_claro);

void define_azul_escuro(Posicao *azul_escuro);

void define_verde(Posicao *verde);

int verifica_azul_escuro(ESTADO e,Posicao *jogadas, Posicao *azul_escuro,Posicao *melhor_jogada);

int verifica_azul_claro(ESTADO e,Posicao *jogadas, Posicao *azul_claro,Posicao *melhor_jogada);

int verifica_amarelo(ESTADO e,Posicao *jogadas, Posicao *amarelo,Posicao *melhor_jogada);

int verifica_verde(ESTADO e,Posicao *jogadas, Posicao *verde,Posicao *melhor_jogada);

int verifica_vermelho(ESTADO e,Posicao *jogadas, Posicao *vermelho,Posicao *melhorjogada);

ESTADO jogadaFacil(ESTADO e,Posicao *amarelo,Posicao *vermelho,Posicao *azul_escuro,Posicao *azul_claro,Posicao *verde,Posicao *jogadas,Posicao *melhorjogada);

ESTADO jogar_peca_bot (ESTADO e,Posicao *melhorjogada);

ESTADO jogadaMedio(ESTADO e,Posicao *melhorjogada);

ESTADO jogaDificl(ESTADO e,Posicao *amarelo,Posicao *vermelho,Posicao *azul_escuro,Posicao *azul_claro,Posicao *verde,Posicao *jogadas,Posicao *melhorjogada);

ESTADO bot_joga(ESTADO e,char *bot, Posicao *amarelo,Posicao *vermelho,Posicao *azul_escuro,Posicao *azul_claro,Posicao *verde,Posicao *jogadas,Posicao *melhorjogada);

#endif //PROJFINAL_BOT_H
