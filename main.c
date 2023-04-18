#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ** lerArquivo(int *n, int *m, int *k, FILE* arquivo){
    
    if(arquivo == NULL){
        perror("Erro ao ler o arquivo");
        exit(1);
    }
    // Contador para saber se ja leu os tres parametros
    int valores = 0;
    // Contador para percorrer os parametros
    int contp = 0;
    // Contador para percorrer o numero 
    int contn = 0;
    // String para coletar um parametro por vez
    char * numero = (char*)calloc(4, sizeof(char));
    if(numero == NULL){
        perror("Erro ao alocar string");
        exit(1);
    }
    // String que contera todos os parametros da primeira linha
    char* parametros = (char*)calloc(14, sizeof(char));
    if(parametros == NULL){
        perror("Erro ao alocar string");
        exit(1);
    }

    // Coletando a linha de parametros
    fscanf(arquivo, "%d %d %d", n, m, k);

    // Matriz com as cores
    int ** matriz = (int**)calloc(*n, sizeof(int*));
    if(matriz == NULL){
        perror("Erro ao alocar vetor de int");
        exit(1);
    }
    for(int i = 0; i < *n; i++){
        matriz[i] = (int*)calloc(*m, sizeof(int));
        if(matriz[i] == NULL){
            perror("Erro ao alocar vetor de int");
            exit(1);
        }
    }

    for(int i = 0; i < *n; i++)
        for(int l = 0; l < *m; l++)
            fscanf(arquivo, "%d", &matriz[i][l]);

    return matriz;
}

void main(int argc, char **argv){
    int n = 0;
    int m = 0;
    int k = 0;
    int ** arquivo;
    FILE * nome_arquivo;

    if(argc > 1)
        nome_arquivo = fopen(argv[1], "r");
    else 
        nome_arquivo = stdin;

    arquivo = lerArquivo(&n, &m, &k, nome_arquivo);

    for (int i = 0; i < n; i++){
        for (int l = 0; l < m; l++)
            printf("%d ", arquivo[i][l]);
        printf("\n");
    }
    
}