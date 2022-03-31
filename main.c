#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "pilha.h"
#include "utils.h"

#define baralhoSize 52

typedef struct {
  int gameover;
  lista mao;
} PERSON;

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

  PERSON jogadores[qtdJogadores];

  for (int i = 0; i < qtdJogadores; i++) {
    for (int j = 0; j < 1; j++) {
      REG reg;

      topoPilha(&p, &reg.chave);

      printf("ponteiro: %p\n", &jogadores[i]);
      printf("ponteiro: %p\n", &jogadores[i].mao);

      // insertLista(&jogadores[i].mao, reg);
      // removePilha(&p);
    }
    printf("\n");
  }

  // for (int i = 0; i < qtdJogadores; i++) {
  //   printaLista(&jogadores[i].mao);
  // }

  // for (int i = 0; i < baralhoSize; i++) {
  //   char r;

  //   if (topoPilha(&p, &r)) {
  //     if (r == 'X') {
  //       printf("10");
  //     } else {
  //       printf("%c", r);
  //     }
  //     printf("\n");
  //     removePilha(&p);
  //   }
  // }
  return 0;
}
