#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

int comparacao(ite ite1, ite ite2){//retorna 1 caso o elemento do primeiro argumento seja maior que o segundo
    if(elemento(ite1)>elemento(ite2)){//compara os elementos(registros) dos argumentos dados.
        return 1;
    }
    return 0;
 }

int main(){



    lista pi;
    char reg = 'c';
    initializeLista(&pi);
    for(int j=0;j<8;j++){
        reg = 'a'+j;
        insertLista(&pi,reg);
    }
    insertLista(&pi,'c');
    insertLista(&pi,'z');
    insertLista(&pi,'x');
    insertLista(&pi,'y');
    insertLista(&pi,'o');
    insertLista(&pi,'P');
    printf("\n\n");

      //ite dois = last(&pi);
    //listComparisson = &comparacao;
    sortlist(pi,&comparacao);

    printaLista(&pi);

    return 0;
}
