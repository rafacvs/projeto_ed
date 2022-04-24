#include "utils.h"

#include <conio.h>
#include <ctype.h>
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

void comprarCarta(pilha *p, PERSON *jogador, int mesa) {
  if (jogador->soma < 21) {
    // se mesa for igual a 1, quer dizer que a mesa esta comprandos cartas.

    int aceValue = -1;
    char option;

    REG reg;

    char element = writeReg(&reg,topoPilha(p));


    if (element == 'X') {
      printf("carta = 10\n");
    } else {
      printf("carta = %c\n", element);  // mudar o acesso ao campo, com iterador.
    }

    if (element == 65) {

      if (mesa == 0) {
        printf("A vale 11? (S ou N)\n");
        scanf(" %c", &option);
      } else {
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

    jogador->soma += getValue(element, aceValue);

    insertLista(&jogador->mao, reg);

    removePilha(p);
  }
}

void jogadaMesa(PERSON jogadores[], int qtdJogadores, pilha *p) {
  printf("MESA\n");
  printf("-----------\n");

  int num, ganhou;  // ganhou verifica de quantos jogadores a mesa ganhou.
  int players_out = 0;

  srand(time(NULL));
  num = rand() % 100;

  for (int i = 0; i < qtdJogadores - 1; i++) {
    if (jogadores[i].gameover == 1) players_out++;
  }

  if (players_out != qtdJogadores - 1) {
    if (num <= 15) {
      printf("Mesa comprou!\n\n");
      comprarCarta(p, &jogadores[qtdJogadores - 1], 1);
      printf("soma atual: %i\n\n", jogadores[qtdJogadores - 1].soma);
    } else if (num > 30) {
      for (int j = 0;; j++) {
        ganhou = 0;

        for (int i = 0; i < qtdJogadores - 1; i++) {
          // Se a mesa ganhar da maioria ela nao compra, se nao ela compra e checamos de novo.
          if (jogadores[qtdJogadores - 1].soma > jogadores[i].soma)
            ganhou += 1;
        }

        if (jogadores[qtdJogadores - 1].soma >= 21 || ganhou >= ((qtdJogadores - 1) / 2) + 1) {
          if (j == 0)
            printf("Mesa nao comprou!\n\n");

          break;
        } else {
          printf("Mesa comprou!\n\n");
          comprarCarta(p, &jogadores[qtdJogadores - 1], 1);
          printf("soma atual: %i\n\n", jogadores[qtdJogadores - 1].soma);
        }
      }
    } else
      printf("Mesa nao comprou!\n\n");
  } else {
    printf("Mesa nao comprou!\n\n");
  }
}

void initializePlayers(int qtdJogadores, PERSON jogadores[qtdJogadores], int isFirst) {
  // INITALIZE PLAYER DATA
  for (int i = 0; i < qtdJogadores; i++) {
    if (isFirst == 1) {
      initializeLista(&jogadores[i].mao);
    } else {
      clearLista(&jogadores[i].mao);
    }

    jogadores[i].soma = 0;
    jogadores[i].gameover = 0;
    // jogadores[i].fichas = 1250;
  }
}

void firstRound(pilha p, int qtdJogadores, PERSON jogadores[qtdJogadores]) {
  system("@cls||clear");

  printf("=========== DISTRIBUINDO CARTAS ===========\n\n");
  // ROUND INICIAL: 2 CARTAS PARA CADA JOGAODR E MESA
  for (int i = 0; i < qtdJogadores; i++) {
    if (jogadores[i].quit != 1 || i == qtdJogadores - 1) {
      if (i == qtdJogadores - 1) {
        printf("MESA\n");
      } else {
        printf("JOGADOR %i\n", i + 1);
      }
      printf("--------------\n");
      if (i != qtdJogadores - 1) {
        while (1) {
          printf("fichas atuais: %i\n", jogadores[i].fichas);
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
        if (i == qtdJogadores - 1)
          comprarCarta(&p, &jogadores[i], 1);
        else
          comprarCarta(&p, &jogadores[i], 0);
      }

      printf("soma = %i\n\n", jogadores[i].soma);

      printf("\n");
    }
  }
}

void rounds(pilha p, int qtdJogadores, PERSON jogadores[qtdJogadores]) {
  system("@cls||clear");
  printf("=========== JOGADAS INVIDUAIS ===========\n\n");
  // ROUNDS
  for (int i = 0; i < qtdJogadores - 1; i++) {
    if (jogadores[i].quit != 1) {
      int stop = 0;
      char option;

      while (stop == 0) {
        if (jogadores[i].soma > 21) {
          jogadores[i].gameover = 1;
          stop = 1;
          break;
        } else if (jogadores[i].soma < 21) {
          system("@cls||clear");

          printf("JOGADOR %i\n", i + 1);
          printf("-----------\n");

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
        } else {
          printf("ganhou! soma = 21\n");
          stop = 1;
        }
      }
    }

    if (jogadores[i].soma > 21) {
      printf("perdeu! soma = %i\n\n", jogadores[i].soma);
      prosseguir();
    }
  }
}

void summary(int qtdJogadores, PERSON jogadores[qtdJogadores], PERSON mesa) {
  // RESUMO DA PARTIDA
  printf("\n\n======== RESUMO DA PARTIDA ========\n\n");
  for (int i = 0; i < qtdJogadores - 1; i++) {
    if (jogadores[i].quit != 1) {
      printf("JOGADOR %i\n", i + 1);
      printf("-----------\n");

      if (jogadores[i].gameover == 1) {
        printf("\nPERDESTES!\n");
      } else {
        if (jogadores[i].soma > 21) {
          jogadores[i].gameover = 1;
          printf("\nPERDESTES!\n");
        } else if ((mesa.soma > 21 || jogadores[i].soma > mesa.soma)) {
          jogadores[i].fichas += (jogadores[i].aposta_atual * 2);

          printf("ganhou mt bom\n");
        } else if (jogadores[i].soma < mesa.soma) {
          jogadores[i].gameover = 1;
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
}

void printRules() {
  printf("=========== REGRAS ===========\n\n");
  printf("BEM VINDO!\n\n");
  printf("Cada jogador comeca com 1250 fichas.\nSe todas forem perdidas o jogador eh eliminado.\n\n");
  printf("O jogador perde a rodada quando:\nA soma de suas cartas eh maior que 21.\nA soma das cartas da mesa eh maior que a soma dele.\n\n");
  printf("O jogador ganha a rodada quando:\nA soma de suas cartas eh maior que a soma das cartas da mesa.\n\n");
  printf("O jogador empata a rodada quando:\nA soma de suas cartas for igual a soma da mesa.\n\n");
  printf("Empate: As fichas apostadas sao devolvidas.\nVitoria: As fichas apostadas sao dobradas.\nDerrota: As fichas apostadas sao perdidas.\n\n");
}

void prosseguir() {
  printf("Press Any Key to Continue\n");
  getch();

  system("@cls||clear");
}
