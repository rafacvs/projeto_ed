#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "pilha.h"

typedef struct {
  lista mao;
  int soma;
  int fichas;
  int aposta_atual;
  int gameover;
} PERSON;

int getValue(char card, int aceValue);
void shuffle(int vetor[], int n);
void comprarCarta(pilha *p, PERSON *jogador);
void initalizeGame(int qtdJogadores, PERSON jogadores[qtdJogadores], pilha p);
void round(int qtdJogadores, PERSON jogadores[qtdJogadores], pilha p);
void summary(int qtdJogadores, PERSON jogadores[qtdJogadores], PERSON mesa);

#endif