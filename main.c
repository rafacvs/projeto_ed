#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "pilha.h"
#include "utils.h"
#include "iterador.h"

#define baralhoSize 52

typedef struct {
  lista mao;
  int soma;
  int gameover;
} PERSON;

void comprarCarta(pilha *p, PERSON *jogador) {
  int aceValue = -1;
  char option;

  REG reg;

  topoPilha(p, &reg.chave);

  if (reg.chave == 'X') {
    printf("carta = 10\n");
  } else {
    printf("carta = %c\n", reg.chave);
  }

  if (reg.chave == 65) {
    printf("A vale 11? (S ou N)\n");
    scanf(" %c", &option);

    if (option == 'S') {
      aceValue = 1;
    } else {
      aceValue = 0;
    }
  }

  jogador->soma += getValue(reg.chave, aceValue);

  insertLista(&jogador->mao, reg);

  removePilha(p);
}

int main() {
  int qtdJogadores;

  int baralho[52] = {'A', 'A', 'A', 'A', '2', '2', '2', '2', '3', '3', '3', '3', '4', '4', '4', '4', '5', '5', '5', '5', '6', '6', '6', '6', '7', '7', '7', '7', '8', '8', '8', '8', '9', '9', '9', '9', 'X', 'X', 'X', 'X', 'J', 'J', 'J', 'J', 'Q', 'Q', 'Q', 'Q', 'K', 'K', 'K', 'K'};
  pilha p;

  inicializePilha(&p, baralhoSize);  // Cria uma estrutura de pilha que vai conter todas as cartas de um baralho padrao.

  shuffle(baralho, baralhoSize);

  for (int i = 0; i < baralhoSize; i++) {
    insertPilha(&p, baralho[i], baralhoSize);
  }

  printf("Insira a quantidade de jogadores:\n");
  scanf("%i", &qtdJogadores);
  qtdJogadores++;  // jogadores qtd - 1 = mesa

  printf("\n\n");

  PERSON jogadores[qtdJogadores];

  for (int i = 0; i < qtdJogadores; i++) {
    jogadores[i].soma = 0;
    initializeLista(&jogadores[i].mao);

    if (i == qtdJogadores - 1) {
      printf("MESA %i\n", i + 1);
    } else {
      printf("JOGADOR %i\n", i + 1);
    }

    for (int j = 0; j < 2; j++) {
      comprarCarta(&p, &jogadores[i]);
    }

    printf("soma = %i\n", jogadores[i].soma);

    printf("\n");
  }

  // ------------------------------------------------------------------------------------------------------------------------

  for (int i = 0; i < qtdJogadores - 1; i++) {
    int stop = 0;
    char option;

    printf("\n-----------\nJogador %i\n", i + 1);

    while (stop == 0) {
      if (jogadores[i].soma > 21) {
        printf("\nPERDESTES!\n");
        jogadores[i].gameover = 1;
        stop = 1;
        break;
      }

      printf("O que voce deseja?\n\n");
      printf("soma atual: %i\n\n", jogadores[i].soma);
      printf("Comprar mais ou parar? (C ou P)\n");

      scanf(" %c", &option);
      if (option == 'C') {
        comprarCarta(&p, &jogadores[i]);
        printf("\n");
      } else {
        stop = 1;
      }
    }
  }


 ite iterador = first(&jogadores[0].mao);
 ite ultimo = last(&jogadores[0].mao);
 printf("primeiro elemento da mao do jogador 1 - %c\n\n\n", elemento(iterador));
 printf("proximo elemento da mao do jogador 1 - %c\n\n\n", elemento(next(iterador)));


 printaLista(&jogadores[0].mao);
  return 0;
}
