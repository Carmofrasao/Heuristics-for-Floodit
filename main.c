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

    // Coletando a matriz
    for(int i = 0; i < *n; i++)
        for(int l = 0; l < *m; l++)
            fscanf(arquivo, "%d", &matriz[i][l]);

    fclose(arquivo);

    return matriz;
}

bool is_valid(int i, int j, int val, int ** mat, int m, int n, int cor) {
    return i >= 0 && i < n && j >= 0 && j < m && (mat[i][j] == val || mat[i][j] == cor);
}

// Busca em profundidade, retorna a maior profundidade
int dfs(int i, int j, int val, int depth, int ** mat, int m, int n, int cor) {
    int max_depth = 0;
    int *stack_i = (int *)calloc(m*n, sizeof(int));
    int *stack_j = (int *)calloc(m*n, sizeof(int));;
    int *stack_d = (int *)calloc(m*n, sizeof(int));;
    int stack_top = 0;

    stack_i[stack_top] = i;
    stack_j[stack_top] = j;
    stack_d[stack_top] = 0;

    while (stack_top >= 0) {
        int ci = stack_i[stack_top];
        int cj = stack_j[stack_top];
        int cd = stack_d[stack_top];
        stack_top--;

        if (is_valid(ci, cj, val, mat, m, n, cor)) {
            if (cd > max_depth)
                max_depth = cd;

            int di[] = {-1, 0, 1, 0};
            int dj[] = {0, 1, 0, -1};
            for (int d = 0; d < 4; d++) {
                int ni = ci + di[d];
                int nj = cj + dj[d];
                if (is_valid(ni, nj, val, mat, m, n, cor)) {
                    stack_top++;
                    stack_i[stack_top] = ni;
                    stack_j[stack_top] = nj;
                    stack_d[stack_top] = cd + 1;
                    mat[ni][nj] = -1;
                }
            }
        }
    }
    
    free(stack_i);
    free(stack_j);
    free(stack_d);

    return max_depth;
}

void search_corners(int ** mat, int n, int m, int k) {
    int max_depth = -1;
    int chosen_i = -1, chosen_j = -1, chosen_val = -1;
    int di[] = {0, 0, n-1, n-1};
    int dj[] = {0, m-1, 0, m-1};
    // Testando todas as cores
    for (int val = 1; val <= k; val++) {
        // Passando pelos 4 cantos
        for (int d = 0; d < 4; d++)
            // Verifica se a cor escolhida ja não esta no canto
            if (mat[di[d]][dj[d]] != val) {
                int depth = dfs(di[d], dj[d], mat[di[d]][0], dj[d], mat, m, n, val);
                printf("di = %d, dj = %d, cMat= %d, val = %d, deaph = %d\n", di[d], dj[d], mat[di[d]][dj[d]], val, depth);
                if (depth > max_depth) {
                    max_depth = depth;
                    chosen_i = di[d];
                    chosen_j = dj[d];
                    chosen_val = val;
                }
            }
    }

    printf("valor escolhido: %d\n", chosen_val);
    for (int d = 0; d < 4; d++)
        if (chosen_i == di[d] && chosen_j == dj[d]){
            printf("Canto escolhido: canto superior esquerdo\n");
            break;
        }
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