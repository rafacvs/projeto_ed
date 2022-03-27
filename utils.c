#include "utils.h"

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
