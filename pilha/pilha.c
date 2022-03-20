#include "pilha.h"

void inicializa(pilha *p, int size) {
  p->v = (int *)malloc(size * sizeof(int));

  p->topo = 0;
}

int vazia(pilha *p) {
  return p->topo == 0;
}

int cheia(pilha *p, int size) {
  return p->topo == size;
}

unsigned tamanho(pilha *p) {
  return p->topo;
}

void insere(pilha *p, T item, int size) {
  if (!cheia(p, size)) {
    p->v[p->topo] = item;
    p->topo++;
  }
}

void retira(pilha *p) {
  if (!vazia(p)) {
    p->topo--;
  }
}

int topo(pilha *p, T *item) {
  if (!vazia(p)) {
    *item = p->v[p->topo - 1];
    return 1;
  }
  return 0;
}