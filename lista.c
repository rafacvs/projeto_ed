#include "lista.h"

#include <stdio.h>
#include <stdlib.h>
// Ivan Capeli Navas
// 802286

int size(LISTA* p) {
  POINTER end = p->head->next;
  int tam = 0;
  while (end != p->head) {
    tam++;
    end = end->next;
  }
  return tam;
}

void initialize(LISTA* p) {
  p->head = (POINTER)malloc(sizeof(ELEM));
  p->head->next = p->head;
  p->head->prev = p->head;
}

void insert(LISTA* p, REG reg) {
  POINTER new = (POINTER)malloc(sizeof(ELEM));
  new->reg = reg;
  int tam = size(p);

  new->next = p->head->next;  // Elemento a ser inserido aponta para o proximo.

  if (p->head->next != p->head) {
    p->head->next->prev = new;  // elemento que antes era o primeiro aponta como antecessor o novo elemento.
  }

  p->head->next = new;  // proximo da cabe�a aponta para o elemento novo.

  new->prev = p->head;  // elemento novo aponta pra cabe�a como antecessor

  if (tam == 0) {
    p->head->prev = new;  // Se for o primeito elemento a ser adicionado o antecessor da cabeca aponta pra ele.
  }
}

void printar(LISTA* p) {
  int result = 0;
  POINTER end = p->head->next;
  while (end != p->head) {
    printf("Elemento %d\n", end->reg.chave);
    end = end->next;
  }
}

void Endinsert(LISTA* p, REG reg) {
  POINTER new = (POINTER)malloc(sizeof(ELEM));
  new->reg = reg;

  new->next = p->head;        // o proximo elemento do final �  a cabeca.
  new->prev = p->head->prev;  // o antes do novo agr � o elemento que era antes da cabeca;

  new->prev->next = new;  // o elemento anterior agr aponta para o elemento novo

  p->head->prev = new;  // o anterior da cabeca agr � o novo.
}

int removeItem(LISTA* p, REG reg) {
  POINTER remove = p->head->next;
  reg = remove->reg;
  int itemremovido = reg.chave;

  if (p->head->next == p->head) {
    return -1;  // Esperque nao de problema.
  }
  p->head->next = remove->next;
  remove->next->prev = p->head;

  free(remove);

  return itemremovido;
}

int EndremoveItem(LISTA* p, REG reg) {
  POINTER remove = p->head->prev;
  reg = remove->reg;
  int itemremovido = reg.chave;

  if (p->head->prev == p->head) {
    return -1;  // Espero que nao de problema, em tese nao � pra entrar aqui.
  }
  p->head->prev = remove->prev;  // anterior da cabeca agr aponta para o elemento anterior ao removido.
  remove->prev->next = p->head;  // o elemento anterior do removido agr aponta para a cabeca.
  free(remove);
  return itemremovido;
}

void clearLISTA(LISTA* p) {
  int i = 0;
  // tirar a cabeca por ultimo.
  while (i <= size(p)) {
    removeItem(p, p->head->next->reg);
    i++;
  }
  // free(p->head);
  free(p);
}