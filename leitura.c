#include "leitura.h"
#include <stdlib.h>

posicao ** lerArquivo(int *n, int *m, int *k, FILE* arquivo){
    
    if(arquivo == NULL){
        perror("Erro ao ler o arquivo");
        exit(1);
    }

    // Coletando a linha de parametros
    fscanf(arquivo, "%d %d %d", n, m, k);

    // Matriz com as cores
    posicao ** matriz = (posicao**)calloc(*n, sizeof(posicao*));
    if(matriz == NULL){
        perror("Erro ao alocar vetor de int");
        exit(1);
    }
    for(int i = 0; i < *n; i++){
        matriz[i] = (posicao*)calloc(*m, sizeof(posicao));
        if(matriz[i] == NULL){
            perror("Erro ao alocar vetor de int");
            exit(1);
        }
    }

    // Coletando a matriz
    for(int i = 0; i < *n; i++)
        for(int l = 0; l < *m; l++){
            fscanf(arquivo, "%d", &matriz[i][l].cor);
            matriz[i][l].teste = matriz[i][l].cor;
        }

    fclose(arquivo);

    return matriz;
}