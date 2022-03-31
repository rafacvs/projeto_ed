#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista.h"
#include "pilha.h"
#include "utils.h"

#define baralhoSize 52

int main() {
  int baralho[52] = {'A', 'A', 'A', 'A', '2', '2', '2', '2', '3', '3', '3', '3', '4', '4', '4', '4', '5', '5', '5', '5', '6', '6', '6', '6', '7', '7', '7', '7', '8', '8', '8', '8', '9', '9', '9', '9', 'X', 'X', 'X', 'X', 'J', 'J', 'J', 'J', 'Q', 'Q', 'Q', 'Q', 'K', 'K', 'K', 'K'};
  pilha p;

  inicializePilha(&p, baralhoSize);//Cria uma estrutura de pilha que vai conter todas as cartas de um baralho padrao.

  shuffle(baralho, baralhoSize);

  for (int i = 0; i < baralhoSize; i++) {
    insertPilha(&p, baralho[i], baralhoSize);
  }
  lista *l = (lista*)malloc(sizeof(lista));
  REG reg;

  reg.chave = 5;

  initializeLista(l);
  insertLista(l,reg);

  printaLista(l);
  destroiLista(l);


  for (int i = 0; i < baralhoSize; i++) {
    char r;

    if (topoPilha(&p, &r)) {
      if (r == 'X') {
        printf("10");
      } else {
        printf("%c", r);
      }
      printf("\n");
      removePilha(&p);
    }
  }
  return 0;
}
