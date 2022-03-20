#include <stdio.h>

#include "pilha.h"

#define baralhoSize 52

int main() {
  pilha p;

  inicializa(&p, baralhoSize);
  insere(&p, 'a', baralhoSize);

  char r;
  if (topo(&p, &r)) printf("%c\n", r);

  return 0;
}