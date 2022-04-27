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
  unsigned tamanho;
} pilha;

void inicializePilha(pilha *p, int size); // Aloca memoria para a pilha e inicializa ela.
int emptyPilha(pilha *p); // Verifica se a pilha esta vazia.
int fullPilha(pilha *p); // Verifica se a pilha esta cheia.
unsigned sizePilha(pilha *p); // Retorna o tamanho.
void insertPilha(pilha *p, CARTA item); // Insere um elemento na pilha.
void removePilha(pilha *p); // Remove um elemento da pilha.
int topoPilha(pilha *p); // Retorna o topo da pilha.
int destroiPilha(pilha *p); // Destroi a pilha e inutiliza ela.
int clearPilha(pilha *p); // Remove todos os elementos da pilha, limpando ela.

#endif
