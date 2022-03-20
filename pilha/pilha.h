#ifndef PILHA_H
#define PILHA_H

typedef char T;

typedef struct {
  unsigned topo;
  T *v;
} pilha;

void inicializa(pilha *p, int size);
int vazia(pilha *p);
int cheia(pilha *p, int size);
unsigned tamanho(pilha *p);
void insere(pilha *p, T item, int size);
void retira(pilha *p);
int topo(pilha *p, T *item);

#endif