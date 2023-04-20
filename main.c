#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

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

// Verifica se a posição esta dentro da matriz e se a posição da 
// matriz tem uma cor igual a da primeira posição
bool is_valid(int i, int j, int val, int ** mat, int m, int n) {
    return i >= 0 && i < n && j >= 0 && j < m && mat[i][j] == val;
}

// Busca em profundidade, retorna a maior profundidade
void dfs(int i, int j, int val, int ** mat, int m, int n, int cor) {
    int max_depth = 0;
    int *stack_i = (int *)calloc(m*n, sizeof(int));
    int *stack_j = (int *)calloc(m*n, sizeof(int));
    int *stack_d = (int *)calloc(m*n, sizeof(int));
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
            if (cd > max_depth)
                max_depth = cd;

            mat[ci][cj] = cor;

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
                    mat[ni][nj] = cor;
                }
            }
        }
    }

    free(stack_i);
    free(stack_j);
    free(stack_d);
}

// Busca em profundidade, retorna o numero de casas preenchidas
int dfs2(int i, int j, int val, int ** mat, int m, int n) {
    int max_depth = 0;
    int *stack_i = (int *)calloc(m*n, sizeof(int));
    int *stack_j = (int *)calloc(m*n, sizeof(int));;
    int *stack_d = (int *)calloc(m*n, sizeof(int));;
    int stack_top = 0;
    int preenchidos = 0;

    stack_i[stack_top] = i;
    stack_j[stack_top] = j;
    stack_d[stack_top] = 0;

    while (stack_top >= 0) {
        int ci = stack_i[stack_top];
        int cj = stack_j[stack_top];
        int cd = stack_d[stack_top];
        stack_top--;

        // O PROBLEMA É ESSE TESTE VVVV, ELE TA COM -1 EM mat[ci][cj], Q É DIFERENTE DE val!!!!
        if (is_valid(ci, cj, val, mat, m, n)) {
            if (cd > max_depth)
                max_depth = cd;

            mat[ci][cj] = -1;
            
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
                    preenchidos++;
                }
            }
        }
    }

    free(stack_i);
    free(stack_j);
    free(stack_d);

    return preenchidos;
}

void search_corners(int ** mat, int n, int m, int k) {
    int preenchidos = 0;
    while(preenchidos <= m*n){
        // Matriz aux
        int ** matriz1 = (int**)calloc(n, sizeof(int*));
        if(matriz1 == NULL){
            perror("Erro ao alocar vetor de int");
            exit(1);
        }
        for(int i = 0; i < n; i++){
            matriz1[i] = (int*)calloc(m, sizeof(int));
            if(matriz1[i] == NULL){
                perror("Erro ao alocar vetor de int");
                exit(1);
            }
        }

        for(int i = 0; i < n; i++)
            for(int l = 0; l < m; l++)
                matriz1[i][l] = mat[i][l];

        int max_depth1 = -1;
        int max_depth2 = -1;
        int chosen_i = -1, chosen_j = -1, chosen_val = -1;
        int di[] = {0, 0, n-1, n-1};
        int dj[] = {0, m-1, 0, m-1};
        // Testando todas as cores
        for (int val = 1; val <= k; val++) {
            // Passando pelos 4 cantos
            for (int d = 0; d < 4; d++){
                // Verifica se a cor escolhida ja não esta no canto
                if (mat[di[d]][dj[d]] != val) {
                    // Faz a busca 
                    dfs(di[d], dj[d], mat[di[d]][dj[d]], mat, m, n, val);
                    int depth2 = dfs2(di[d], dj[d], val, mat, m, n);
                    for(int i = 0; i < n; i++)
                        for(int l = 0; l < m; l++)
                            mat[i][l] = matriz1[i][l];
                    // Se a busca encontrou um caminho mais fundo que o anterior, salva
                    if (depth2 > max_depth2) {
                        max_depth2 = depth2;
                        chosen_i = di[d];
                        chosen_j = dj[d];
                        chosen_val = val;
                    }
                }
                for(int i = 0; i < n; i++)
                    for(int l = 0; l < m; l++)
                        mat[i][l] = matriz1[i][l];
            }
        }

        // O ERRO PROVAVELMENTE ESTA AQUI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

        dfs(chosen_i, chosen_j, mat[chosen_i][chosen_j], mat, m, n, chosen_val);
        preenchidos = dfs2(chosen_i, chosen_j, chosen_val, mat, m, n);

        for(int i = 0; i < n; i++)
            for(int l = 0; l < m; l++)
                if(mat[i][l] == -1)
                    mat[i][l] = chosen_val;

        if(chosen_i == 0 && chosen_j == 0)
            printf("a ");
        else if(chosen_i == 0 && chosen_j == m-1)
            printf("b ");
        else if(chosen_i == n-1 &&  chosen_j == 0)
            printf("c ");
        else if(chosen_i == n-1 &&  chosen_j == m-1)
            printf("d ");
        printf("%d\n", chosen_val);
        usleep(500*1000);
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