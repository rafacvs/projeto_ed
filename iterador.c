#include "iterador.h"

#include <stdio.h>
#include <stdlib.h>

ite first(lista* l ){
    ite i;
    i.posicao = l->head->next;
    i.estrutura = l;
    return i;
}
ite last(lista* l ){
    ite i;
    i.posicao = l->head->prev;
    i.estrutura = l;
    return i;
}
char elemento(ite l){
    return l.posicao->reg.chave;
}

ite next(ite l){
    if(!acabou(l)){
        l.posicao = l.posicao->next;
        return l;
    }//oq fazer se estiver no ultimo ?

}

int acabou( ite i ) {
    return i.posicao->next == i.estrutura->head;
}
