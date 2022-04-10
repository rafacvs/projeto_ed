
#ifndef LISTA_H
#define LISTA_H


/*
Gabriel Bellon de Carvalho - 802430
Ivan Capeli Navas - 802286
Rafael de Campos Villa da Silveira - 801968
*/

typedef struct {
  char chave;
} REG;

typedef struct aux {
  REG reg;

  struct aux *prev;
  struct aux *next;
} ELEM;

typedef ELEM *POINTER;

typedef struct {
  POINTER head;
  unsigned qtd;
} lista;

void initializeLista(lista *l);
void insertLista(lista *l, REG reg);     // insere elemento no comeÃ§o
void insertEndLista(lista *l, REG reg);  // insere elemento no final
int removeItemLista(lista *l, REG reg);
int removeItemEndLista(lista *l, REG reg);
int sizeLista(lista *l);
void printaLista(lista *l);
void destroiLista(lista *l);
void clearLista(lista *l);

#endif
