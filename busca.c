#include "busca.h"
#include <stdlib.h>

// Verifica se a posição esta dentro da matriz e se a posição da 
// matriz tem uma cor igual a da primeira posição
bool e_valido(int i, int j, int val, posicao ** mat, int m, int n) {
    return i >= 0 && i < n && j >= 0 && j < m && mat[i][j].cor == val;
}

// Verifica se a posição esta dentro da matriz e se a posição da 
// matriz tem uma cor igual a cor desjada
bool e_valido2(int i, int j, int val, posicao ** mat, int m, int n) {
    return i >= 0 && i < n && j >= 0 && j < m && mat[i][j].teste == val;
}

// Busca em profundidade iterativa, pinta a matriz com a cor escolhida
void dfs(int i, int j, int val, posicao ** mat, int m, int n, int cor) {
    int *pilha_i = (int *)calloc(m*n, sizeof(int));
    if(pilha_i == NULL){
        perror("Erro ao alocar vetor de int");
        exit(1);
    }
    int *pilha_j = (int *)calloc(m*n, sizeof(int));
    if(pilha_j == NULL){
        perror("Erro ao alocar vetor de int");
        exit(1);
    }
    int top_pilha = 0;

    pilha_i[top_pilha] = i;
    pilha_j[top_pilha] = j;

    while (top_pilha >= 0) {
        int ci = pilha_i[top_pilha];
        int cj = pilha_j[top_pilha];
        top_pilha--;

        if (e_valido(ci, cj, val, mat, m, n)) {
            mat[ci][cj].teste = -1;
            mat[ci][cj].cor = cor;

            int di[] = {-1, 0, 1, 0};
            int dj[] = {0, 1, 0, -1};
            for (int d = 0; d < 4; d++) {
                int ni = ci + di[d];
                int nj = cj + dj[d];
                if (e_valido(ni, nj, val, mat, m, n)) {
                    top_pilha++;
                    pilha_i[top_pilha] = ni;
                    pilha_j[top_pilha] = nj;
                }
            }
        }
    }

    free(pilha_i);
    free(pilha_j);
}

// Busca em profundidade iterativa, retorna o numero de casas preenchidas
int dfs2(int i, int j, int val, posicao ** mat, int m, int n) {
    int *pilha_i = (int *)calloc(m*n, sizeof(int));
    if(pilha_i == NULL){
        perror("Erro ao alocar vetor de int");
        exit(1);
    }
    int *pilha_j = (int *)calloc(m*n, sizeof(int));
    if(pilha_j == NULL){
        perror("Erro ao alocar vetor de int");
        exit(1);
    }
    int top_pilha = 0;
    int preenchidos = 0;

    pilha_i[top_pilha] = i;
    pilha_j[top_pilha] = j;

    while (top_pilha >= 0) {
        int ci = pilha_i[top_pilha];
        int cj = pilha_j[top_pilha];
        top_pilha--;

        if (e_valido(ci, cj, val, mat, m, n)) {

            if(mat[ci][cj].passou != -1){
                mat[ci][cj].passou = -1;
                preenchidos++;
            }
            
            int di[] = {-1, 0, 1, 0};
            int dj[] = {0, 1, 0, -1};
            for (int d = 0; d < 4; d++) {
                int ni = ci + di[d];
                int nj = cj + dj[d];
                if (e_valido(ni, nj, val, mat, m, n) && mat[ni][nj].passou != -1) {
                    top_pilha++;
                    pilha_i[top_pilha] = ni;
                    pilha_j[top_pilha] = nj;
                    mat[ni][nj].passou = -1;
                    preenchidos++;
                }
            }
        }
    }

    free(pilha_i);
    free(pilha_j);

    return preenchidos;
}

passo * buscaNoCanto(posicao ** mat, int n, int m, int k, int *n_passos) {
    passo * vet_passos = (passo *)calloc(n*m, sizeof(passo));
    if(vet_passos == NULL){
        perror("Erro ao alocar vetor de passos");
        exit(1);
    }
    posicao ** matriz = (posicao**)calloc(n, sizeof(posicao*));
    // Matriz aux
    if(matriz == NULL){
        perror("Erro ao alocar vetor de int");
        exit(1);
    }
    for(int i = 0; i < n; i++){
        matriz[i] = (posicao*)calloc(m, sizeof(posicao));
        if(matriz[i] == NULL){
            perror("Erro ao alocar vetor de int");
            exit(1);
        }
    }
    int preenchidos = 0;
    int passos = 0;
    while(preenchidos < m*n){
        for(int i = 0; i < n; i++)
            for(int l = 0; l < m; l++)
                matriz[i][l].cor = mat[i][l].cor;

        int profundidade_max = -1;
        int i_escolhido = -1, j_escolhido = -1, val_escolhido = -1;
        int di[] = {0, 0, n-1, n-1};
        int dj[] = {0, m-1, 0, m-1};
        // Testando todas as cores
        for (int val = 1; val <= k; val++) {
            // Passando pelos 4 cantos
            for (int d = 0; d < 4; d++){
                // Verifica se a cor escolhida ja não esta no canto
                if (mat[di[d]][dj[d]].cor != val) {    
                    // Faz a busca 
                    dfs(di[d], dj[d], mat[di[d]][dj[d]].cor, mat, m, n, val);
                    int profundidade = dfs2(di[d], dj[d], val, mat, m, n);
                    for(int i = 0; i < n; i++)
                        for(int l = 0; l < m; l++){
                            mat[i][l].cor = matriz[i][l].cor;
                            mat[i][l].passou = 0;
                            mat[i][l].teste = matriz[i][l].cor;
                        }
                    // --------------------------HEURISTICA!----------------------------
                    // Se a busca encontrou um caminho mais fundo que o anterior, salva
                    if (profundidade > profundidade_max) {
                        profundidade_max = profundidade;
                        i_escolhido = di[d];
                        j_escolhido = dj[d];
                        val_escolhido = val;
                    }
                    // ----------------------------------------------------------------
                }
                for(int i = 0; i < n; i++)
                    for(int l = 0; l < m; l++){
                        mat[i][l].cor = matriz[i][l].cor;
                        mat[i][l].passou = 0;
                        mat[i][l].teste = matriz[i][l].cor;
                    }
            }
        }

        dfs(i_escolhido, j_escolhido, mat[i_escolhido][j_escolhido].cor, mat, m, n, val_escolhido);
        preenchidos = dfs2(i_escolhido, j_escolhido, val_escolhido, mat, m, n);

        for(int i = 0; i < n; i++)
            for(int l = 0; l < m; l++)
                if(mat[i][l].passou == -1){
                    mat[i][l].cor = val_escolhido;
                    mat[i][l].teste = val_escolhido;
                }

        if(i_escolhido == 0 && j_escolhido == 0)
            vet_passos[passos].canto = 'a';
        else if(i_escolhido == 0 && j_escolhido == m-1)
            vet_passos[passos].canto = 'b';
        else if(i_escolhido == n-1 &&  j_escolhido == 0)
            vet_passos[passos].canto = 'd';
        else if(i_escolhido == n-1 &&  j_escolhido == m-1)
            vet_passos[passos].canto = 'c';
        vet_passos[passos].cor = val_escolhido;
        passos++;
    }

    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
    *n_passos = passos;
    return vet_passos;
}