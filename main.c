
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista.h"
#include "pilha.h"
#include "utils.h"

#define baralhoSize 52

int main() {
  int qtdJogadores, stopGame = 0, isFirst = 1;

  int baralho[52] = {'A', 'A', 'A', 'A', '2', '2', '2', '2', '3', '3', '3', '3', '4', '4', '4', '4', '5', '5', '5', '5', '6', '6', '6', '6', '7', '7', '7', '7', '8', '8', '8', '8', '9', '9', '9', '9', 'X', 'X', 'X', 'X', 'J', 'J', 'J', 'J', 'Q', 'Q', 'Q', 'Q', 'K', 'K', 'K', 'K'};
  pilha p;

  printf("bem vindo\nregras: cada jogador comeca com 1250 fichas. perdeu = fraco.\n\n");
  printf("Insira a quantidade de jogadores:\n");
  scanf("%i", &qtdJogadores);
  qtdJogadores++;  // jogadores qtd - 1 = mesa

  printf("\n\n");

  PERSON jogadores[qtdJogadores];

  for (int i = 0; i < qtdJogadores; i++) {
    jogadores[i].fichas = 1250;
  }

  while (stopGame == 0) {
    int quitQtd = 0;

    for (int i = 0; i < qtdJogadores - 1; i++) {
      quitQtd += jogadores[i].quit;
    }

    if (quitQtd == qtdJogadores - 1) {
      stopGame = 1;
    } else {
      printf("\n\nloooop\n\n");

      if (isFirst == 1) {
        inicializePilha(&p, baralhoSize);  // Cria uma estrutura de pilha que vai conter todas as cartas de um baralho padrao.}
      } else {
        clearPilha(&p);
      }

      shuffle(baralho, baralhoSize);

      for (int i = 0; i < baralhoSize; i++) {
        insertPilha(&p, baralho[i], baralhoSize);
      }

      initializePlayers(qtdJogadores, jogadores, isFirst);

      firstRound(p, qtdJogadores, jogadores);

      printf("Press Any Key to Continue\n");

      getch();

      rounds(p, qtdJogadores, jogadores);

      printf("Press Any Key to Continue\n");

      getch();

      jogadaMesa(jogadores, qtdJogadores, &p);

      PERSON mesa = jogadores[qtdJogadores - 1];

      summary(qtdJogadores, jogadores, mesa);

      printf("Press Any Key to Continue\n");

      getch();

      stopGame = 1;

      for (int i = 0; i < qtdJogadores - 1; i++) {
        if (jogadores[i].fichas > 0) stopGame = 0;
      }

      for (int i = 0; i < qtdJogadores - 1; i++) {
        if (jogadores[i].quit != 1) {
          char option;

          system("@cls||clear");
          printf("JOGADOR %i\n", i + 1);
          printf("-----------\n");
          printf("deseja sair? (S ou N)\n");

          scanf(" %c", &option);

          if (option == 'S') {
            jogadores[i].quit = 1;
          }
        }
      }

      isFirst = 0;
    }
  }

  printf("obrigado por jogar viu\n");

  getch();

  return 0;
}