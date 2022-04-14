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
void swap(int v[], int a, int b);
void shuffle(int vetor[], int n);
void comprarCarta(pilha *p, PERSON *jogador, int mesa);
void jogadaMesa(PERSON jogadores[], int qtdJogadores, pilha *p);
void initializePlayers(int qtdJogadores, PERSON jogadores[qtdJogadores]);
void firstRound(pilha p, int qtdJogadores, PERSON jogadores[qtdJogadores]);
void rounds(pilha p, int qtdJogadores, PERSON jogadores[qtdJogadores]);
void summary(int qtdJogadores, PERSON jogadores[qtdJogadores], PERSON mesa);
void printRules();

#endif
