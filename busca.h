#ifndef __BUSCA__
#define __BUSCA__

#include "leitura.h"
#include <stdbool.h>

typedef struct {
    char canto;
    int cor;
} passo;

bool e_valido(int i, int j, int val, posicao ** mat, int m, int n);

bool e_valido2(int i, int j, int val, posicao ** mat, int m, int n);

void dfs(int i, int j, int val, posicao ** mat, int m, int n, int cor);

int dfs2(int i, int j, int val, posicao ** mat, int m, int n);

passo * buscaNoCanto(posicao ** mat, int n, int m, int k, int *n_passos);

#endif