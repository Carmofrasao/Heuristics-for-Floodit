#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

bool is_valid(int i, int j, int val, int ** mat, int m, int n) {
    return i >= 0 && i < n && j >= 0 && j < m && mat[i][j] == val;
}

int dfs(int i, int j, int val, int depth, int ** mat, int m, int n) {
    int max_depth = 0;
    int stack_i[n*m], stack_j[n*m], stack_d[n*m];
    int stack_top = 0;

    stack_i[stack_top] = i;
    stack_j[stack_top] = j;
    stack_d[stack_top] = 0;

    while (stack_top >= 0) {
        int ci = stack_i[stack_top];
        int cj = stack_j[stack_top];
        int cd = stack_d[stack_top];
        stack_top--;

        if (is_valid(ci, cj, val, mat, m, n)) {
            if (cd > max_depth) {
                max_depth = cd;
            }

            int di[] = {-1, 0, 1, 0};
            int dj[] = {0, 1, 0, -1};
            for (int d = 0; d < 4; d++) {
                int ni = ci + di[d];
                int nj = cj + dj[d];
                if (is_valid(ni, nj, val, mat, m, n)) {
                    stack_top++;
                    stack_i[stack_top] = ni;
                    stack_j[stack_top] = nj;
                    stack_d[stack_top] = cd + 1;
                    mat[ni][nj] = -1;
                }
            }
        }
    }

    return max_depth;
}

void search_corners(int ** mat, int n, int m, int k) {
    int max_depth = -1;
    int chosen_i = -1, chosen_j = -1, chosen_val = -1;
    for (int val = 1; val <= k; val++) {
        if (mat[0][0] != val) {
            int depth = dfs(0, 0, mat[0][0], 0, mat, m, n);
            if (depth > max_depth) {
                max_depth = depth;
                chosen_i = 0;
                chosen_j = 0;
                chosen_val = val;
            }
        }
        if (mat[0][m-1] != val) {
            int depth = dfs(0, m-1, mat[0][m-1], 0, mat, m, n);
            if (depth > max_depth) {
                max_depth = depth;
                chosen_i = 0;
                chosen_j = m-1;
                chosen_val = val;
            }
        }
        if (mat[n-1][0] != val) {
            int depth = dfs(n-1, 0, mat[n-1][0], 0, mat, m, n);
            if (depth > max_depth) {
                max_depth = depth;
                chosen_i = n-1;
                chosen_j = 0;
                chosen_val = val;
            }
        }
        if (mat[n-1][m-1] != val) {
            int depth = dfs(n-1, m-1, mat[n-1][m-1], 0, mat, m, n);
            if (depth > max_depth) {
                max_depth = depth;
                chosen_i = n-1;
                chosen_j = m-1;
                chosen_val = val;
            }
        }
    }

    printf("valor escolhido: %d\n", chosen_val);
    if (chosen_i == 0 && chosen_j == 0)
        printf("Canto escolhido: canto superior esquerdo\n");
    else if (chosen_i == 0 && chosen_j == m-1)
        printf("Canto escolhido: canto superior direito\n");
    else if (chosen_i == n-1 && chosen_j == 0)
        printf("Canto escolhido: canto inferior esquerdo\n");
    else if (chosen_i == n-1 && chosen_j == m-1)
        printf("Canto escolhido: canto inferior direito\n");
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

    search_corners(arquivo, n, m, k);

    for (int i = 0; i < n; i++)
        free(arquivo[i]);
    free(arquivo);

    return 0;
}