#include "lista.h"


#include <stdio.h>
#include <stdlib.h>
/*
Gabriel Bellon de Carvalho - 802430
Ivan Capeli Navas - 802286
Rafael de Campos Villa da Silveira - 801968
*/
int sizeLista(lista *l) {
  return l->qtd;  // Retorna o campo que contem o numero de itens da estrutura.
}

void initializeLista(lista *l) {
  l->head = (POINTER)malloc(sizeof(ELEM));  // aloca espaco para a sentinela
  l->head->next = l->head;                  // inicializa os ponteiros para a propria sentinela, ate que algum elemento seja adicionado
  l->head->prev = l->head;
  l->qtd = 0;  // tamanho comeca em 0.
}

void insertLista(lista *l, REG reg) {           // funcao para inserir no comeco da lista, isso eh, logo dps da sentinela
  POINTER new = (POINTER)malloc(sizeof(ELEM));  // pointer eh um typedef, ponteiro do tipo ELEM.
  new->reg = reg;                               // coloca o registro no seu respectivo campo, o registro eh o dado em si.
  int tam = sizeLista(l);                       // chama a funcao do tamanho e retorna-o.

  new->next = l->head->next;  // Elemento a ser inserido aponta para o proximo.

  if (l->head->next != l->head) {
    l->head->next->prev = new;  // elemento que antes era o primeiro aponta como antecessor o novo elemento.
  }

  l->head->next = new;  // proximo da cabeca aponta para o elemento novo.

  new->prev = l->head;  // elemento novo aponta pra cabeca como antecessor

  if (tam == 0) {
    l->head->prev = new;  // Se for o primeito elemento a ser adicionado o antecessor da cabeca aponta pra ele.
  }

  l->qtd++;
}

void printaLista(lista *l) {  // percorre a lista inteira e printa seus respectivos elementos/chaves;
  int result = 0;
  POINTER end = l->head->next;
  while (end != l->head) {
    printf("carta %c\n", end->reg.chave);
    end = end->next;
  }
}

void insertEndLista(lista *l, REG reg) {  // insere um elemento no final da lista.
  POINTER new = (POINTER)malloc(sizeof(ELEM));
  new->reg = reg;

  new->next = l->head;        // o proximo elemento do final   a cabeca.
  new->prev = l->head->prev;  // o antes do novo agr  o elemento que era antes da cabeca;

  new->prev->next = new;  // o elemento anterior agr aponta para o elemento novo

  l->head->prev = new;  // o anterior da cabeca agr aponta para  o novo.
  l->qtd++;
}

int removeItemLista(lista *l, REG reg) {  // remove um item do comeco da lista
  POINTER remove = l->head->next;
  reg = remove->reg;
  int itemremovido = reg.chave;  // coloca o item a ser removido em uma variavel

  if (l->head->next == l->head) {  // caso o proximo elemento da sentinela for ela mesmo.
    return -1;
  }

  l->head->next = remove->next;  // agr o proximo da sentinela apontara para o elemento depois do removido.
  remove->next->prev = l->head;  // agora o elemento depois do removido tem como anterior a sentinela.

  free(remove);  // libera a memoria do elemento a ser removido.
  l->qtd--;
  return itemremovido;
}

int removeItemEndLista(lista *l, REG reg) {  // Remove o ultimo elemento da estrutura.
  POINTER remove = l->head->prev;            // ultimo elemento.
  reg = remove->reg;
  int itemremovido = reg.chave;

  if (l->head->prev == l->head) {
    return -1;
  }
  l->head->prev = remove->prev;  // anterior da cabeca agr aponta para o elemento anterior ao removido.
  remove->prev->next = l->head;  // o elemento anterior do removido agr aponta para a cabeca.
  free(remove);                  // libera a memoria do item removido.
  l->qtd--;
  return itemremovido;
}

void clearLista(lista *l) {  // percorre a lista e esvazia.O(N);
  int i = 0;
  // tirar a cabeca por ultimo.
  while (i <= sizeLista(l)) {
    removeItemLista(l, l->head->next->reg);
    i++;
  }

  l->qtd = 0;  // Seta a quantidade =0.
}

void destroiLista(lista *l) {
  clearLista(l);  // esvazia a lista.
  free(l->head);  // destroi a lista.
}


