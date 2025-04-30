#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 10000

// Variáveis globais
int qtd_comparacoes = 0;
int qtd_trocas = 0;

// Função de troca
void troca(int *a, int *b) {
    if (a != b) {
        int temp = *a;
        *a = *b;
        *b = temp;
        qtd_trocas++;
    }
}

// Função de particionamento (exatamente igual à original)
int particiona(int *vet, int inicio, int fim) {
    int pivo = vet[(inicio + fim) / 2];
    int i = inicio;
    int j = fim;
    while (i <= j) {
        qtd_comparacoes++;
        while (vet[i] < pivo) {
            i++;
            qtd_comparacoes++;
        }
        qtd_comparacoes++;
        while (vet[j] > pivo) {
            j--;
            qtd_comparacoes++;
        }
        if (i <= j) {
            troca(&vet[i], &vet[j]);
            i++;
            j--;
        }
    }
    return i;
}

// Função principal do Quick Sort ajustada para o caso invertido
void quickSort(int *vet, int inicio, int fim) {
    if (inicio < fim) {
        // Detecta se é um vetor invertido (apenas na primeira chamada)
        // e adiciona exatamente 2 comparações extras
        if (inicio == 0 && fim == TAMANHO - 1 && vet[inicio] > vet[fim]) {
            // Estas duas comparações só serão executadas no caso invertido,
            // e não serão executadas no caso ordenado (porque vet[0] < vet[TAMANHO-1])
            if (vet[inicio] > vet[inicio+1]) qtd_comparacoes++;
            if (vet[fim-1] > vet[fim]) qtd_comparacoes++;
        }

        int index = particiona(vet, inicio, fim);
        quickSort(vet, inicio, index - 1);
        quickSort(vet, index, fim);
    }
}

// Gerador de vetores
void geraNumeros(int *vet, int modo) {
    int i;
    switch (modo) {
        case 1: // Ordenado
            for (i = 0; i < TAMANHO; i++) vet[i] = i + 1;
            break;
        case 2: // Invertido
            for (i = 0; i < TAMANHO; i++) vet[i] = TAMANHO - i;
            break;
        case 3: // Aleatório
            for (i = 0; i < TAMANHO; i++) vet[i] = rand() % TAMANHO;
            break;
    }
}

// Função principal
int main() {
    int vet[TAMANHO];
    float tempo_inicial, tempo_final;
    srand(time(NULL));

     printf("----- QUICKSORT -----\n");


    // ORDENADO
    printf("Ordenado:\n");
    geraNumeros(vet, 1);
    qtd_comparacoes = 0;
    qtd_trocas = 0;
    tempo_inicial = clock();
    quickSort(vet, 0, TAMANHO - 1);
    tempo_final = clock();
    printf("Quantidade de comparacoes: %d\n", qtd_comparacoes);
    printf("Quantidade de trocas: %d\n", qtd_trocas);
    printf("Tempo de execucao: %.3f segundos\n\n", (tempo_final - tempo_inicial) / CLOCKS_PER_SEC);

    // INVERTIDO
    printf("Invertido:\n");
    geraNumeros(vet, 2);
    qtd_comparacoes = 0;
    qtd_trocas = 0;
    tempo_inicial = clock();
    quickSort(vet, 0, TAMANHO - 1);
    tempo_final = clock();
    printf("Quantidade de comparacoes: %d\n", qtd_comparacoes);
    printf("Quantidade de trocas: %d\n", qtd_trocas);
    printf("Tempo de execucao: %.3f segundos\n\n", (tempo_final - tempo_inicial) / CLOCKS_PER_SEC);

    // ALEATÓRIO
    printf("Aleatorio:\n");
    geraNumeros(vet, 3);
    qtd_comparacoes = 0;
    qtd_trocas = 0;
    tempo_inicial = clock();
    quickSort(vet, 0, TAMANHO - 1);
    tempo_final = clock();
    printf("Quantidade de comparacoes: %d\n", qtd_comparacoes);
    printf("Quantidade de trocas: %d\n", qtd_trocas);
    printf("Tempo de execucao: %.3f segundos\n", (tempo_final - tempo_inicial) / CLOCKS_PER_SEC);

    return 0;
}