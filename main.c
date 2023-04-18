#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ** lerArquivo(int *n, int *m, int *k, FILE* arquivo){
    
    if(arquivo == NULL){
        perror("Erro ao ler o arquivo");
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

    fclose(arquivo);

    return matriz;
}

int dfs(
    int i, int j, int val, int ** vizitados, 
    int ** mat, int m, int n
) {
    vizitados[i][j] = 1;
    int max_depth = 0;
    if (i == 0 || i == n-1 || j == 0 || j == m-1) {
        max_depth = 1;
    }
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (int d = 0; d < 4; d++) {
        int ni = i + dirs[d][0];
        int nj = j + dirs[d][1];
        if (ni >= 0 && ni < n && nj >= 0 && nj < m && !vizitados[ni][nj] && mat[ni][nj] == val) {
            int depth = dfs(ni, nj, val, vizitados, mat, m, n);
            if (depth > max_depth) {
                max_depth = depth;
            }
        }
    }
    vizitados[i][j] = 0;
    return max_depth + 1;
}

int main(int argc, char **argv){
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

    // Matriz de vizitados
    int ** vizitados = (int**)calloc(n, sizeof(int*));
    if(vizitados == NULL){
        perror("Erro ao alocar vetor de int");
        exit(1);
    }
    for(int i = 0; i < n; i++){
        vizitados[i] = (int*)calloc(m, sizeof(int));
        if(vizitados[i] == NULL){
            perror("Erro ao alocar vetor de int");
            exit(1);
        }
    }

    // inicialização do array de profundidades máximas
    int profundidade_max = -1;

    int chosen_value = -1;
    int chosen_i = -1;
    int chosen_j = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int v = 1; v <= k; v++) {
                if (arquivo[i][j] != v) {
                    int depth = dfs(i, j, v, vizitados, arquivo, m, n);
                    if (depth > profundidade_max) {
                        profundidade_max = depth;
                        chosen_value = v;
                        chosen_i = i;
                        chosen_j = j;
                    }
                }
            }
        }
    }
    printf("Chosen value: %d\n", chosen_value);
    printf("Chosen corner: (%d, %d)\n", chosen_i, chosen_j);

    if (chosen_i == 0 && chosen_j == 0) 
        printf("Canto escolhido: canto superior esquerdo\n");
    else if (chosen_i == 0 && chosen_j == m-1)
        printf("Canto escolhido: canto superior direito\n");
    else if (chosen_i == n-1 && chosen_j == 0)
        printf("Canto escolhido: canto inferior esquerdo\n");
    else if (chosen_i == n-1 && chosen_j == m-1)
        printf("Canto escolhido: canto inferior direito\n");

    for (int i = 0; i < n; i++)
        free(arquivo[i]);
    free(arquivo);

    return 0;
}