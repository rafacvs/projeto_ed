#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
void inicializa(pilha *p, int size) {
  p->v = (char *)malloc(size * sizeof(char));

  p->topo = 0;
}

int vazia(pilha *p) {
  return p->topo == 0;//Retorna 1 se estiver vazia.
}

int cheia(pilha *p, int size) {
  return p->topo == size;//Retorna 1 se estiver cheia.
}

unsigned tamanho(pilha *p) {
  return p->topo;//topo guarda o n° de elementos
}

void insere(pilha *p, CARTA item, int size) {
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

int topo(pilha *p, CARTA *item) {
  if (!vazia(p)) {
    *item = p->v[p->topo - 1];//coloca o ultimo elemento no endereço de item. retorna 1 caso tenha sucesso.
    return 1;
  }
  return 0;
}
