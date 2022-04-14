#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista.h"
#include "pilha.h"
#include "utils.h"

#define baralhoSize 52

int main() {
  int qtdJogadores;

  int baralho[52] = {'A', 'A', 'A', 'A', '2', '2', '2', '2', '3', '3', '3', '3', '4', '4', '4', '4', '5', '5', '5', '5', '6', '6', '6', '6', '7', '7', '7', '7', '8', '8', '8', '8', '9', '9', '9', '9', 'X', 'X', 'X', 'X', 'J', 'J', 'J', 'J', 'Q', 'Q', 'Q', 'Q', 'K', 'K', 'K', 'K'};
  pilha p;

  inicializePilha(&p, baralhoSize);  // Cria uma estrutura de pilha que vai conter todas as cartas de um baralho padrao.

  shuffle(baralho, baralhoSize);

  for (int i = 0; i < baralhoSize; i++) {
    insertPilha(&p, baralho[i], baralhoSize);
  }

  printf("bem vindo\nregras: cada jogador comeca com 1250 fichas. perdeu = fraco.\n\n");
  printf("Insira a quantidade de jogadores:\n");
  scanf("%i", &qtdJogadores);
  qtdJogadores++;  // jogadores qtd - 1 = mesa

  printf("\n\n");

  PERSON jogadores[qtdJogadores];

  initializePlayers(qtdJogadores, jogadores);

  firstRound(p, qtdJogadores, jogadores);

  rounds(p, qtdJogadores, jogadores);

  jogadaMesa(jogadores, qtdJogadores, &p);

  PERSON mesa = jogadores[qtdJogadores - 1];

  summary(qtdJogadores, jogadores, mesa);

  return 0;
}
