#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "pilha.h"
#include "utils.h"

#define baralhoSize 52

typedef struct {
  lista mao;
  int soma;
  int gameover;
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
    jogadores[i].soma = 0;
    initializeLista(&jogadores[i].mao);

    printf("JOGADOR %i\n", i + 1);
    for (int j = 0; j < 2; j++) {
      int aceValue = -1;

      REG reg;

      topoPilha(&p, &reg.chave);

      if (reg.chave == 65) {
        printf("A vale 11? 1 pra SIM 0 pra NAO\n");
        scanf("%i", &aceValue);
      }

      jogadores[i].soma += getValue(reg.chave, aceValue);

      insertLista(&jogadores[i].mao, reg);

      removePilha(&p);
    }
    printaLista(&jogadores[i].mao);

    printf("soma = %i\n", jogadores[i].soma);

    printf("\n");
  }

  return 0;
}
