#ifndef PILHA_H
#define PILHA_H

typedef char CARTA;

typedef struct {
  unsigned topo;
  CARTA *v;
} pilha;

void inicializa(pilha *p, int size);
int vazia(pilha *p);
int cheia(pilha *p, int size);
unsigned tamanho(pilha *p);
void insere(pilha *p, CARTA item, int size);
void retira(pilha *p);
int topo(pilha *p, CARTA *item);

#endif
