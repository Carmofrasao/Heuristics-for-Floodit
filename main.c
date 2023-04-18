#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ** lerArquivo(int *n, int *m, int *k, char* nome){
    // Arquivo a ser aberto
    FILE* arquivo = fopen(nome, "r");
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
    char * resultado = fgets(parametros, 14, arquivo);
    if(resultado == 0){
        perror("Não foi possivel ler os parametros");
        exit(1);
    }
    
    // Percorrer toda string até achar os tres parametros
    while(valores < 3){
        while(parametros[contp] != ' '){
            numero[contn] = parametros[contp];
            contn++;
            contp++;
        }
        contp++;
        
        if(valores == 0)
            *n = atoi(numero);
        else if(valores == 1)
            *m = atoi(numero);
        else if(valores == 2)
            *k = atoi(numero);

        contn = 0;
        memset(numero, '\0', 4*sizeof(char));
        valores++;
    }

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

    // String que contera todos os parametros da primeira linha
    char* linha = (char*)calloc(2*(*m), sizeof(char));
    if(linha == NULL){
        perror("Erro ao alocar string");
        exit(1);
    }

    // Coletando a linha de cor
    resultado = fgets(linha, 2*(*m)-1, arquivo);
    if(resultado == 0){
        perror("Não foi possivel ler a linha");
        exit(1);
    }

    // String para coletar a cor, uma por vez
    char * sCor = (char*)calloc(1, sizeof(*k));
    if(sCor == NULL){
        perror("Erro ao alocar string");
        exit(1);
    }

    int contl = 0;
    int contc = 0;
    for(int i = 0; i < *n; i++){
        for(int l = 0; l < *m; l++){
            while(linha[contl] != ' '){
                sCor[contc] = linha[contl];
                contc++;
                contl++;
            }
            contl++;
            
            matriz[i][l] = atoi(sCor);

            contc = 0;
            memset(sCor, '\0', *k*sizeof(char));
        }
        memset(linha, '\0', 2*(*m)*sizeof(char));
        resultado = fgets(linha, 2*(*m)-1, arquivo);
        if(resultado == 0){
            perror("Não foi possivel ler a linha");
            exit(1);
        }
        contl = 0;
    }

    for(int i = 0; i < *n; i++){
        for(int l = 0; l < *m; l++)
            printf("%d ", matriz[i][l]);
        printf("\n");
    }
}

void main(int argc, char **argv){
    int n = 0;
    int m = 0;
    int k = 0;
    int ** arquivo;

    if(argc > 1)
        arquivo = lerArquivo(&n, &m, &k, argv[1]);
    // else
    //     arquivo = lerEntrada(&n, &m, &k);
}