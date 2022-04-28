/*
Gabriel Bellon de Carvalho - 802430
Ivan Capeli Navas - 802286
Rafael de Campos Villa da Silveira - 801968
*/

#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

int sizeLista(lista *l) {
  return l->qtd;  // Retorna o campo que contem o numero de itens da estrutura.
}

void initializeLista(lista *l) {
  l->head = (POINTER)malloc(sizeof(ELEM));  // Aloca espaco para a sentinela
  l->head->next = l->head;                  // Inicializa os ponteiros para a propria sentinela, ate que algum elemento seja adicionado.
  l->head->prev = l->head;
  l->qtd = 0;  // Tamanho comeca em 0.
}

void insertLista(lista *l, char reg) {          // Funcao para inserir no comeco da lista, isso eh, logo dps da sentinela.
  POINTER new = (POINTER)malloc(sizeof(ELEM));  // Pointer eh um typedef, ponteiro do tipo ELEM.
  new->reg = reg;                               // Coloca o registro no seu respectivo campo, o registro eh o dado em si.
  int tam = sizeLista(l);                       // Chama a funcao do tamanho e retorna-o.

  new->next = l->head->next;  // Elemento a ser inserido aponta para o proximo.

  l->head->next->prev = new;  // Elemento que antes era o primeiro aponta como antecessor o novo elemento.

  l->head->next = new;  // Proximo da cabeca aponta para o elemento novo.

  new->prev = l->head;  // Elemento novo aponta pra cabeca como antecessor.

  l->qtd++;
}

void printaLista(lista *l) {  // Percorre a lista inteira e printa seus respectivos elementos/chaves.
  int result = 0;
  POINTER end = l->head->next;
  while (end != l->head) {
    printf("carta %c\n", end->reg);
    end = end->next;
  }
}

void insertEndLista(lista *l, char reg) {  // Insere um elemento no final da lista.
  POINTER new = (POINTER)malloc(sizeof(ELEM));
  new->reg = reg;

  new->next = l->head;        // O proximo elemento do final   a cabeca.
  new->prev = l->head->prev;  // O antes do novo agr  o elemento que era antes da cabeca.

  new->prev->next = new;  // O elemento anterior agr aponta para o elemento novo.

  l->head->prev = new;  // O anterior da cabeca agr aponta para  o novo.
  l->qtd++;
}

int removeItemLista(lista *l) {  // Remove um item do comeco da lista.
  POINTER remove = l->head->next;

  int itemremovido = remove->reg;  // Coloca o item a ser removido em uma variavel.

  l->head->next = remove->next;  // Agora o proximo da sentinela apontara para o elemento depois do removido.
  remove->next->prev = l->head;  // Agora o elemento depois do removido tem como anterior a sentinela.

  free(remove);  // Libera a memoria do elemento a ser removido.
  l->qtd--;
  return itemremovido;
}

int removeItemEndLista(lista *l) {  // Remove o ultimo elemento da estrutura.
  POINTER remove = l->head->prev;   // Ultimo elemento.

  int itemremovido = remove->reg;

  l->head->prev = remove->prev;  // Anterior da cabeca agora aponta para o elemento anterior ao removido.
  remove->prev->next = l->head;  // O elemento anterior do removido agora aponta para a cabeca.
  free(remove);                  // Libera a memoria do item removido.
  l->qtd--;

  return itemremovido;
}

void clearLista(lista *l) {  // Percorre a lista e esvazia.O(N);
  int i = 0;
  // tirar a cabeca por ultimo.
  while (i <= sizeLista(l)) {
    removeItemLista(l);
    i++;
  }

  l->qtd = 0;  // Seta a quantidade = 0.
}

void destroiLista(lista *l) {
  clearLista(l);  // Esvazia a lista.
  free(l->head);  // Destroi a lista.
}

ite first(lista *l) {  // Funcao que retorna um apontador para o primeiro elemento de uma lista.
  ite i;
  i.posicao = l->head->next;
  i.estrutura = l;
  return i;
}
ite last(lista *l) {  // Funcao que retorna um apontador para o ultimo elemento de uma lista.
  ite i;
  i.posicao = l->head->prev;
  i.estrutura = l;
  return i;
}

char elemento(ite l) {  // Funcao que retorna o elemento que um iterador(apontador) aponta.
  return l.posicao->reg;
}

ite next(ite l) {  // Para iterar ao longo da estrutura, ate chegar no ultimo elemento.
  if (!acabou(l) || l.estrutura->qtd == 0) {
    l.posicao = l.posicao->next;
    return l;
  }
}

int acabou(ite i) {  // Denota o final da estrutura, que eh quando a posicao do apontar eh a mesma que a da sentinela.
  return i.posicao == i.estrutura->head;
}

// Para adicionar no meio, tem duas opcoes, depois de certo item, ou antes.
// se foi depois do el2 ficaria =   <-head -> (<-el1) -> (<-el2) -> (<-el3)
// <-head -> (<-el1) -> (<-el2) ->(<-el4)-> (<-el3)

void insertMiddleLista(lista *l, char reg, ite i) {  // Funcao que insere um elemento no meio da lista, isso eh logo apos a um iterador
  POINTER new = (POINTER)malloc(sizeof(ELEM));
  new->reg = reg;
  int tam = sizeLista(l);

  new->next = i.posicao->next;
  i.posicao->next->prev = new;  // Caso especial, um item na lista.
  i.posicao->next = new;
  new->prev = i.posicao;

  l->qtd++;
}

char removeItemMiddleLista(lista *l, ite i) {  // Remove o item que o iterador aponta.
  if (l->qtd == 0) {
    return -1;  // So nao pode remover a head/sentinela.
  }
  ite inicio = first(l);
  POINTER remove = (POINTER)malloc(sizeof(ELEM));

  int itemremovido = remove->reg;

  if (i.posicao->next == i.estrutura->head) {  // Caso o item seja o ultimo da lista.
    itemremovido = removeItemEndLista(l);
    return itemremovido;
  } else if (inicio.posicao == i.posicao) {  // Caso seja o primeiro elemento.
    itemremovido = removeItemLista(l);
    return itemremovido;
  }

  i.posicao->next->prev = i.posicao->prev;  // Proximo do item removido agr aponta para o anterior do removido.
  i.posicao->prev->next = i.posicao->next;  // Anterior aponta para o proximo.

  free(remove);
  l->qtd--;
  return itemremovido;
}

void swapi(ite one, ite two) {  // Faz um swap entre dois apontadores, mudando apenas o seus respectivos registros de lugar.
  char temp;
  temp = two.posicao->reg;
  two.posicao->reg = one.posicao->reg;
  one.posicao->reg = temp;
}

void sortlist(lista pi, int (*listComparisson)(ite, ite)) {
  // Funcao que dada uma lista e uma funcao de ordenacao, ordena essa lista
  // a partir do resultado das comparacoes de listComparisson, 1 quando para que uma troca seja feita(swapi) e 0 caso nao queira uma troca.

  for (ite um = first(&pi); !acabou(um); um = next(um)) {  // Faz um sort simples com complexidade quadratica.
    for (ite dois = next(um); !acabou(dois); dois = next(dois)) {
      if (listComparisson(um, dois) == 1) {
        swapi(um, dois);
      }
    }
  }
}
