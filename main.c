#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista.h"
#include "pilha.h"
#include "utils.h"

#define baralhoSize 52

typedef struct {
  lista mao;
  int soma;
  int fichas;
  int aposta_atual;
  int gameover;
} PERSON;

void comprarCarta(pilha *p, PERSON *jogador, int mesa) {
  // se mesa for igual a 1, quer dizer que a mesa esta comprandos cartas.
  
  int aceValue = -1;
  char option;

  REG reg;

  topoPilha(p, &reg.chave);

  if (reg.chave == 'X') {
    printf("carta = 10\n");
  } else {
    printf("carta = %c\n", reg.chave);//mudar o acesso ao campo, com iterador.
  }

  if (reg.chave == 65) {
    if (mesa == 0) {
      printf("A vale 11? (S ou N)\n");
      scanf(" %c", &option);
    }
    else {
      if (jogador->soma + 11 > 21)
        option = 'N';
      else
        option = 'S';
    }

    if (option == 'S') {
      aceValue = 1;
    } else {
      aceValue = 0;
    }
  }

  jogador->soma += getValue(reg.chave, aceValue);

  insertLista(&jogador->mao, reg);

  removePilha(p);
}

void jogadaMesa(PERSON jogadores[], int qtdJogadores, pilha *p) {
  int num, ganhou; // ganhou verifica de quantos jogadores a mesa ganhou.
  
  srand(time(NULL));
  num = rand() % 100;
  
  if (num <= 15) {
    printf("Mesa comprou!\n\n");
    comprarCarta(p, &jogadores[qtdJogadores - 1], 1);
    printf("soma atual: %i\n\n", jogadores[qtdJogadores - 1].soma);
  }
  else if (num > 30) {
    for (int j = 0;; j++) {
      ganhou = 0;
      
      for (int i = 0; i < qtdJogadores - 1; i++) {
        // Se a mesa ganhar da maioria ela nao compra, se nao ela compra e checamos de novo.
        if (jogadores[qtdJogadores - 1].soma > jogadores[i].soma)
          ganhou += 1;
      }

      if (jogadores[qtdJogadores - 1].soma > 21 || ganhou >= ((qtdJogadores - 1) / 2) + 1) {
        if (j == 0)
          printf("Mesa não comprou!\n\n");
        
        break; 
      }
      else {
        printf("Mesa comprou!\n\n");
        comprarCarta(p, &jogadores[qtdJogadores - 1], 1);
        printf("soma atual: %i\n\n", jogadores[qtdJogadores - 1].soma);
      }
    }
  }
  else
    printf("Mesa não comprou!\n\n");  
}

int main() {
  int qtdJogadores;

  int baralho[52] = {'A', 'A', 'A', 'A', '2', '2', '2', '2', '3', '3', '3', '3', '4', '4', '4', '4', '5', '5', '5', '5', '6', '6', '6', '6', '7', '7', '7', '7', '8', '8', '8', '8', '9', '9', '9', '9', 'X', 'X', 'X', 'X', 'J', 'J', 'J', 'J', 'Q', 'Q', 'Q', 'Q', 'K', 'K', 'K', 'K'};
  pilha p;

  inicializePilha(&p, baralhoSize);  // Cria uma estrutura de pilha que vai conter todas as cartas de um baralho padrao.

  shuffle(baralho, baralhoSize);

  for (int i = 0; i < baralhoSize; i++) {
    insertPilha(&p, baralho[i], baralhoSize);
  }
  printf("bem vindo\nregras: cada jogador comeca com 1250 fichas. perdeu = fraco.\n\n");
  printf("Insira a quantidade de jogadores:\n");
  scanf("%i", &qtdJogadores);
  qtdJogadores++;  // jogadores qtd - 1 = mesa

  printf("\n\n");

  PERSON jogadores[qtdJogadores];

  // INITALIZE PLAYER DATA
  for (int i = 0; i < qtdJogadores; i++) {
    initializeLista(&jogadores[i].mao);
    jogadores[i].soma = 0;
    jogadores[i].fichas = 1250;
  }

  printf("=========== DISTRIBUINDO CARTAS ===========\n\n");
  // ROUND INICIAL: 2 CARTAS PARA CADA JOGAODR E MESA
  for (int i = 0; i < qtdJogadores; i++) {
    if (i == qtdJogadores - 1) {
      printf("MESA\n");
    } else {
      printf("JOGADOR %i\n", i + 1);
    }
    printf("--------------\n");
    if (i != qtdJogadores - 1) {
      while (1) {
        printf("quanto quer apostar?\n");
        scanf("%i", &jogadores[i].aposta_atual);

        if (jogadores[i].aposta_atual > jogadores[i].fichas) {
          printf("kk pobre\n");
        } else {
          break;
        }
      }

      jogadores[i].fichas -= jogadores[i].aposta_atual;
    }

    for (int j = 0; j < 2; j++) {
      if (i == qtdJogadores -1)
        comprarCarta(&p, &jogadores[i], 1);
      else
        comprarCarta(&p, &jogadores[i], 0);
    }

    printf("soma = %i\n\n", jogadores[i].soma);

    printf("\n");
  }

  printf("=========== JOGADAS INVIDUAIS ===========\n\n");
  // ROUNDS
  for (int i = 0; i < qtdJogadores - 1; i++) {
    int stop = 0;
    char option;

    printf("JOGADOR %i\n", i + 1);
    printf("-----------\n");

    while (stop == 0) {
      if (jogadores[i].soma > 21) {
        jogadores[i].gameover = 1;
        stop = 1;
        break;
      }

      printf("fichas atuais: %i\n\n", jogadores[i].fichas);
      printf("aposta: %i\n", jogadores[i].aposta_atual);
      printf("soma atual: %i\n\n", jogadores[i].soma);

      printf("O que voce deseja?\n");
      printf("  Comprar mais ou parar? (C ou P)\n");

      scanf(" %c", &option);
      if (option == 'C') {
        comprarCarta(&p, &jogadores[i], 0);
        printf("\n");
      } else {
        stop = 1;
      }
    }
  }

  printf("MESA\n");
  printf("-----------\n");
  jogadaMesa(jogadores, qtdJogadores, &p);
  
  PERSON mesa = jogadores[qtdJogadores - 1];

  // RESUMO DA PARTIDA
  printf("\n\n======== RESUMO DA PARTIDA ========\n\n");
  for (int i = 0; i < qtdJogadores - 1; i++) {
    printf("JOGADOR %i\n", i + 1);
    printf("-----------\n");

    if (jogadores[i].gameover == 1) {
      printf("PERDESTES!\n");
    } else {
      if (mesa.soma > 21 || jogadores[i].soma > mesa.soma) {
        printf("ganhou mt bom\n");
      } else if (jogadores[i].soma < mesa.soma) {
        printf("\nPERDESTES!\n");
      } else {
        printf("empate - fichas devolvidas\n");
        jogadores[i].fichas += jogadores[i].aposta_atual;
        jogadores[i].aposta_atual = 0;
      }
    }
    printf("\n\n");
  }

  return 0;
}
