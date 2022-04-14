#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getValue(char card, int aceValue) {
  switch (card) {
    case 'A':
      if (aceValue == 1) {
        return 11;
      } else {
        return 1;
      }
      break;
    case '2':
      return 2;
      break;
    case '3':
      return 3;
      break;
    case '4':
      return 4;
      break;
    case '5':
      return 5;
      break;
    case '6':
      return 6;
      break;
    case '7':
      return 7;
      break;
    case '8':
      return 8;
      break;
    case '9':
      return 9;
      break;
    case 'X':
      return 10;
      break;
    case 'J':
      return 10;
      break;
    case 'Q':
      return 10;
      break;
    case 'K':
      return 10;
      break;
  }
}

void swap(int v[], int a, int b) {
  int temp = v[a];
  v[a] = v[b];
  v[b] = temp;
}

void shuffle(int vetor[], int n) {
  srand(time(NULL));

  for (int i = 0; i < n; i++) {
    int j = i + rand() % (n - i);

    swap(vetor, i, j);
  }
}

void comprarCarta(pilha *p, PERSON *jogador) {
  int aceValue = -1;
  char option;

  REG reg;

  topoPilha(p, &reg.chave);

  if (reg.chave == 'X') {
    printf("carta = 10\n");
  } else {
    printf("carta = %c\n", reg.chave);
  }

  if (reg.chave == 65) {
    printf("A vale 11? (S ou N)\n");
    scanf(" %c", &option);

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

void initalizeGame(int qtdJogadores, PERSON jogadores[qtdJogadores], pilha p) {
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
      comprarCarta(&p, &jogadores[i]);
    }

    printf("soma = %i\n\n", jogadores[i].soma);

    printf("\n");
  }
}

void round(int qtdJogadores, PERSON jogadores[qtdJogadores], pilha p) {
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
        comprarCarta(&p, &jogadores[i]);
        printf("\n");
      } else {
        stop = 1;
      }
    }
  }
}

void summary(int qtdJogadores, PERSON jogadores[qtdJogadores], PERSON mesa) {
  // RESUMO DA PARTIDA
  printf("\n\n======== RESUMO DA PARTIDA ========\n\n");
  for (int i = 0; i < qtdJogadores - 1; i++) {
    printf("JOGADOR %i\n", i + 1);
    printf("-----------\n");

    if (jogadores[i].gameover == 1) {
      printf("PERDESTES!\n");
    } else {
      if (jogadores[i].soma > mesa.soma) {
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
}