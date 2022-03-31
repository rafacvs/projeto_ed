#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void inicializePilha(pilha *p, int size) {
  p->v = (char *)malloc(size * sizeof(char));

  p->topo = 0;
}

int emptyPilha(pilha *p) {
  return p->topo == 0;//Retorna 1 se estiver vazia.
}

int fullPilha(pilha *p, int size) {
  return p->topo == size;//Retorna 1 se estiver cheia.
}

unsigned sizePilha(pilha *p) {
  return p->topo;//topo guarda o numero de elementos
}

void insertPilha(pilha *p, CARTA item, int size) {
  if (!fullPilha(p, size)) {
    p->v[p->topo] = item;
    p->topo++;
  }
}

void removePilha(pilha *p) {
  if (!emptyPilha(p)) {
    p->topo--;
  }
}

int topoPilha(pilha *p, CARTA *item) {
  if (!emptyPilha(p)) {
    *item = p->v[p->topo - 1];//coloca o ultimo elemento no endere�o de item. retorna 1 caso tenha sucesso.
    return 1;
  }
  return 0;
}

int destroiPilha(pilha *p) {
    free(p);
    return 1;
}

int clearPilha(pilha *p) {
    p->topo = 0;
    return 0;
}
