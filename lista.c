#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

int sizeLista(lista *l) {
    return l->qtd;
}

void initializeLista(lista *l) {
  l->head = (POINTER)malloc(sizeof(ELEM));//aloca espaco para a sentinela
  l->head->next = l->head;//inicializa os ponteiros para a propria sentinela, ate que algum elemento seja adicionado
  l->head->prev = l->head;
  l->qtd = 0;//tamanho comeca em 0.
}

void insertLista(lista *l, REG reg) {
  POINTER new = (POINTER)malloc(sizeof(ELEM));
  new->reg = reg;
  int tam = sizeLista(l);

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

void printaLista(lista *l) { //percorre a lista inteira e printa seus respectivos elementos/chaves;
  int result = 0;
  POINTER end = l->head->next;
  while (end != l->head) {
    printf("Elemento %d\n", end->reg.chave);
    end = end->next;
  }
}

void insertEndLista(lista *l, REG reg) {
  POINTER new = (POINTER)malloc(sizeof(ELEM));
  new->reg = reg;

  new->next = l->head;        // o proximo elemento do final   a cabeca.
  new->prev = l->head->prev;  // o antes do novo agr  o elemento que era antes da cabeca;

  new->prev->next = new;  // o elemento anterior agr aponta para o elemento novo

  l->head->prev = new;  // o anterior da cabeca agr Ã© o novo.
  l->qtd++;
}

int removeItemLista(lista *l, REG reg) {
  POINTER remove = l->head->next;
  reg = remove->reg;
  int itemremovido = reg.chave;

  if (l->head->next == l->head) {
    return -1;
  }
  l->head->next = remove->next;
  remove->next->prev = l->head;

  free(remove);
  l->qtd--;
  return itemremovido;
}

int removeItemEndLista(lista *l, REG reg) {
  POINTER remove = l->head->prev;
  reg = remove->reg;
  int itemremovido = reg.chave;

  if (l->head->prev == l->head) {
    return -1;
  }
  l->head->prev = remove->prev;  // anterior da cabeca agr aponta para o elemento anterior ao removido.
  remove->prev->next = l->head;  // o elemento anterior do removido agr aponta para a cabeca.
  free(remove);
  l->qtd--;
  return itemremovido;
}

void clearLista(lista *l) {
  int i = 0;
  // tirar a cabeca por ultimo.
  while (i <= sizeLista(l)) {
    removeItemLista(l, l->head->next->reg);
    i++;
  }
  l->qtd =0;

}

void destroiLista(lista *l) {
    clearLista(l);
    free(l->head);
    free(l);
}
