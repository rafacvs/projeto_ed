#ifndef PILHA_H
#define PILHA_H
/*
Gabriel Bellon de Carvalho - 802430
Ivan Capeli Navas - 802286
Rafael de Campos Villa da Silveira - 801968
*/
typedef char CARTA;

typedef struct {
  unsigned topo;
  CARTA *v;
} pilha;

void inicializePilha(pilha *p, int size);
int emptyPilha(pilha *p);
int fullPilha(pilha *p, int size);
unsigned sizePilha(pilha *p);
void insertPilha(pilha *p, CARTA item, int size);
void removePilha(pilha *p);
int topoPilha(pilha *p, CARTA *item);
int destroiPilha(pilha *p);
int clearPilha(pilha *p);

#endif
