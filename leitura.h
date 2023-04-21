#ifndef __LEITURA__
#define __LEITURA__

#include <stdio.h>

typedef struct {
    int cor;
    int passou;
    int teste;
} posicao;

posicao ** lerArquivo(int *n, int *m, int *k, FILE* arquivo);

#endif