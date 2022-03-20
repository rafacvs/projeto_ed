#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pilha.h"

#define baralhoSize 52

void swap(int v[], int a, int b) {
  int temp = v[a];
  v[a] = v[b];
  v[b] = temp;
}

void shuffle(int vetor[], int n) {
  srand(time(NULL));

  for (int i = 0; i < n; i++) {
    int j = i + rand() % (n - i);

    swap(vetor, i, j);
  }
}

int main() {
  int baralho[52] = {'A', 'A', 'A', 'A', '1', '1', '1', '1', '2', '2', '2', '2', '3', '3', '3', '3', '4', '4', '4', '4', '5', '5', '5', '5', '6', '6', '6', '6', '7', '7', '7', '7', '8', '8', '8', '8', '9', '9', '9', '9', 'X', 'X', 'X', 'X', 'J', 'J', 'J', 'J', 'Q', 'Q', 'Q', 'Q', 'K', 'K', 'K', 'K'};
  pilha p;

  inicializa(&p, baralhoSize);

  shuffle(baralho, baralhoSize);

  for (int i = 0; i < baralhoSize; i++) {
    insere(&p, baralho[i], baralhoSize);
  }

  printf("is cheia? %i\n\n", cheia(&p, baralhoSize));

  for (int i = 0; i < baralhoSize; i++) {
    char r;

    if (topo(&p, &r)) {
      if (r == 'X') {
        printf("10");
      } else {
        printf("%c", r);
      }
      printf("\n");
      retira(&p);
    }
  }

  return 0;
}