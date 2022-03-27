#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
#include <stdlib.h>
// Ivan Capeli Navas
// 802286
#define TAMANHO_MAXIMO_LISTA 550000

typedef struct {
  int chave;
} REG;

typedef struct aux {
  REG reg;

  struct aux* prev;
  struct aux* next;
} ELEM;

typedef ELEM* POINTER;

typedef struct {
  POINTER head;
  unsigned qtd;
} LISTA;

void initialize(LISTA* p);

void insert(LISTA* p, REG reg);     // insere elemento no começo
void Endinsert(LISTA* p, REG reg);  // insere elemento no final

int removeItem(LISTA* p, REG reg);
int EndremoveItem(LISTA* p, REG reg);

int size(LISTA* p);
void printar(LISTA* p);
void destroiLista(LISTA *p);
void clearLISTA(LISTA* p);

#endif
