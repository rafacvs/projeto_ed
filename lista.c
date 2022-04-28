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

void insertLista(lista *l, char reg) {           // funcao para inserir no comeco da lista, isso eh, logo dps da sentinela
  POINTER new = (POINTER)malloc(sizeof(ELEM));  // pointer eh um typedef, ponteiro do tipo ELEM.
  new->reg = reg;                               // coloca o registro no seu respectivo campo, o registro eh o dado em si.
  int tam = sizeLista(l);                       // chama a funcao do tamanho e retorna-o.

  new->next = l->head->next;  // Elemento a ser inserido aponta para o proximo.


  l->head->next->prev = new;  // elemento que antes era o primeiro aponta como antecessor o novo elemento.


  l->head->next = new;  // proximo da cabeca aponta para o elemento novo.

  new->prev = l->head;  // elemento novo aponta pra cabeca como antecessor


  //l->head->prev = new;  // Se for o primeito elemento a ser adicionado o antecessor da cabeca aponta pra ele.

  l->qtd++;
}

void printaLista(lista *l) {  // percorre a lista inteira e printa seus respectivos elementos/chaves;
  int result = 0;
  POINTER end = l->head->next;
  while (end != l->head) {
    printf("carta %c\n", end->reg);
    end = end->next;
  }
}

void insertEndLista(lista *l, char reg) {  // insere um elemento no final da lista.
  POINTER new = (POINTER)malloc(sizeof(ELEM));
  new->reg = reg;

  new->next = l->head;        // o proximo elemento do final   a cabeca.
  new->prev = l->head->prev;  // o antes do novo agr  o elemento que era antes da cabeca;

  new->prev->next = new;  // o elemento anterior agr aponta para o elemento novo

  l->head->prev = new;  // o anterior da cabeca agr aponta para  o novo.
  l->qtd++;
}

int removeItemLista(lista *l) {  // remove um item do comeco da lista
  POINTER remove = l->head->next;

  int itemremovido = remove->reg;  // coloca o item a ser removido em uma variavel


  l->head->next = remove->next;  // agr o proximo da sentinela apontara para o elemento depois do removido.
  remove->next->prev = l->head;  // agora o elemento depois do removido tem como anterior a sentinela.

  free(remove);  // libera a memoria do elemento a ser removido.
  l->qtd--;
  return itemremovido;
}

int removeItemEndLista(lista *l) {  // Remove o ultimo elemento da estrutura.
  POINTER remove = l->head->prev;            // ultimo elemento.

  int itemremovido = remove->reg;


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
    removeItemLista(l);
    i++;
  }

  l->qtd = 0;  // Seta a quantidade =0.
}

void destroiLista(lista *l) {
  clearLista(l);  // esvazia a lista.
  free(l->head);  // destroi a lista.
}



ite first(lista* l ){//funcao que retorna um apontador para o primeiro elemento de uma lista.
    ite i;
    i.posicao = l->head->next;
    i.estrutura = l;
    return i;
}
ite last(lista* l ){//funcao que retorna um apontador para o ultimo elemento de uma lista.
    ite i;
    i.posicao = l->head->prev;
    i.estrutura = l;
    return i;
}

char elemento(ite l){//funcao que retorna o elemento que um iterador(apontador) aponta.
    return l.posicao->reg;
}

ite next(ite l){//para iterar ao longo da estrutura, ate chegar no ultimo elemento.
    if(!acabou(l) || l.estrutura->qtd==0){
        l.posicao = l.posicao->next;
        return l;
    }//oq fazer se estiver no ultimo ?

}

int acabou( ite i ) {//denota o final da estrutura, que eh quando a posicao do apontar eh a mesma que a da sentinela.
    return i.posicao == i.estrutura->head;
}

//para adicionar no meio, tem duas op��es, dps de certo item, ou antes
// se foi dps do el2 ficaria =   <-head -> (<-el1) -> (<-el2) -> (<-el3)
// <-head -> (<-el1) -> (<-el2) ->(<-el4)-> (<-el3)

void insertMiddleLista(lista *l,char reg, ite i){//funcao que insere um elemento no meio da lista, isso eh logo apos a um iterador
    POINTER new = (POINTER)malloc(sizeof(ELEM));
    new->reg = reg;
    int tam = sizeLista(l);

    new->next = i.posicao->next;
    i.posicao->next->prev = new;//caso especial, um item na lista.
    i.posicao->next = new;
    new->prev = i.posicao;

    l->qtd++;
}

char removeItemMiddleLista(lista *l, ite i){//remove o item que o iterador aponta.
    if(l->qtd==0){
        return -1;//so nao posso remover a head/sentinela.
    }
    ite inicio = first(l);
    POINTER remove = (POINTER)malloc(sizeof(ELEM));

    int itemremovido = remove->reg;

    if(i.posicao->next==i.estrutura->head){//caso o item seja o ultimo da lista.
        itemremovido = removeItemEndLista(l);
        return itemremovido;
    }
    else if(inicio.posicao == i.posicao){//caso seja o primeiro elemento.
        itemremovido = removeItemLista(l);
        return itemremovido;
    }

    i.posicao->next->prev = i.posicao->prev;//proximo do item removido agr aponta para o anterior do removido.
    i.posicao->prev->next = i.posicao->next;//anterior aponta para o proximo.

    free(remove);
    l->qtd--;
    return itemremovido;
}

void swapi(ite one, ite two){//faz um swap entre dois apontadores, mudando apenas o seus respectivos registros de lugar.
    char temp;
    temp = two.posicao->reg;
    two.posicao->reg = one.posicao->reg;
    one.posicao->reg = temp;

}


/* int listComparisson(ite ite1, ite ite2){//retorna 1 caso o elemento do primeiro argumento seja maior que o segundo
    if(elemento(ite1)>elemento(ite2)){//compara os elementos(registros) dos argumentos dados.
        return 1;
    }
    return 0;
 }*/

void sortlist(lista pi,int (*listComparisson)(ite,ite)){//funcao que dada uma lista e uma funcao de ordenacao, ordena essa lista
    //apartir do resultado das comparacoes de listComparisson, 1 quando para que uma troca seja feita(swapi) e 0 caso nao queira uma troca.


 for(ite um = first(&pi);!acabou(um);um = next(um)){//faz um sort simples com complexidade quadratica.
        for(ite dois = next(um);!acabou(dois);dois = next(dois)){
             if(   listComparisson(um,dois) == 1   ){//
                swapi(um,dois);
             }
        }
    }
}


