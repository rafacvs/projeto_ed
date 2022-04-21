
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

typedef struct{
    POINTER posicao;
    lista* estrutura;
}ite;

void initializeLista(lista *l);
void insertLista(lista *l, REG reg);     // insere elemento no comeÃ§o
void insertEndLista(lista *l, REG reg);  // insere elemento no final
int removeItemLista(lista *l, REG reg);
int removeItemEndLista(lista *l, REG reg);
int sizeLista(lista *l);
void printaLista(lista *l);
void destroiLista(lista *l);
void clearLista(lista *l);
void swapi(ite one, ite two);

ite first(lista* l );
ite last(lista* l);
ite next(ite l);

int acabou( ite i );

char elemento(ite l);
char removeItemMiddleLista(lista *l, REG reg, ite i);

void insertMiddleLista(lista *l,REG reg, ite i);
int listComparisson(ite ite1, ite ite2);
void sortlist(lista pi);
#endif
