/*
Gabriel Bellon de Carvalho - 802430
Ivan Capeli Navas - 802286
Rafael de Campos Villa da Silveira - 801968
*/

#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

void inicializePilha(pilha *p, int size) {
  p->v = (char *)malloc(size * sizeof(char));  // Aloca dinamicamente um espaço de memoria do tamanho size.
  p->tamanho = size;                           // Tamanho eh o tamanho maximo da pilha.
  p->topo = 0;                                 // Topo eh 0 (a pilha nao tem nenhum item).
}

int emptyPilha(pilha *p) {
  return p->topo == 0;  // Retorna 1 se estiver vazia.
}

int fullPilha(pilha *p) {
  return p->topo == p->tamanho;  // Retorna 1 se estiver cheia.
}

unsigned sizePilha(pilha *p) {
  return p->topo;  // Topo guarda o numero de elementos da pilha (tamanho).
}

void insertPilha(pilha *p, CARTA item) {
  if (!fullPilha(p)) {     // Verifica se a pliha esta cheia e so insere um novo elemento se ela nao estiver.
    p->v[p->topo] = item;  // Insere o elemento no topo da pilha.
    p->topo++;             // Aumenta o topo em 1.
  }
}

void removePilha(pilha *p) {
  if (!emptyPilha(p)) {  // Verifica se a pilha nao esta vazia.
    p->topo--;           // Remove o elemento do topo.
  }
}

int topoPilha(pilha *p) {
  if (!emptyPilha(p)) {        // Verifica se a pilha nao esta vazia.
                               // Coloca o ultimo elemento no endereco de item.
    return p->v[p->topo - 1];  // Retorna o elemento do topo.
  }
}

int destroiPilha(pilha *p) {
  free(p->v);  // Desaloca o espaco de memoria de p, destruindo a pilha.
  return 1;
}

int clearPilha(pilha *p) {
  p->topo = 0;  // Remove todos os elementos da pilha igualando o topo a 0.
  return 1;
}
