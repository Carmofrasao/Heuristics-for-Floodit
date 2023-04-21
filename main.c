#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"
#include "busca.h"

int main(int argc, char **argv){
    int n = 0;
    int m = 0;
    int k = 0;
    int n_passos = 0;
    posicao ** arquivo;
    FILE * nome_arquivo;

    if(argc > 1)
        nome_arquivo = fopen(argv[1], "r");
    else 
        nome_arquivo = stdin;

    arquivo = lerArquivo(&n, &m, &k, nome_arquivo);

    passo * vet_passos = buscaNoCanto(arquivo, n, m, k, &n_passos);

    printf("%d\n", n_passos);
    for(int i = 0; i < n_passos; i++)
        printf("%c %d ", vet_passos[i].canto, vet_passos[i].cor);
    printf("\n");

    for (int i = 0; i < n; i++)
        free(arquivo[i]);
    free(arquivo);
    free(vet_passos);

    return 0;
}