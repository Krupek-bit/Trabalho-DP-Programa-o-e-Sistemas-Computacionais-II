#include <cstring>
#include "busca_ordenacao.h"

/*
 * insertionSortPorTitulo: ordena o vetor de ponteiros por título (ordem alfabética).
 * Parâmetros: vetor - vetor de Livro*; n - quantidade de elementos.
 * Retorno: nenhum (ordena no próprio vetor).
 * Complexidade: pior caso e caso médio O(n^2); melhor caso (já ordenado) O(n).
 * Espaço extra: O(1). Algoritmo estável. Move ponteiros, não structs inteiras.
 */
void insertionSortPorTitulo(Livro** vetor, int n) {
    for (int i = 1; i < n; i++) {
        Livro* chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && strcmp(vetor[j]->titulo, chave->titulo) > 0) {
            vetor[j + 1] = vetor[j];   // desloca para a direita
            j--;
        }
        vetor[j + 1] = chave;          // insere na posição correta
    }
}

/*
 * buscaSequencialPorTitulo: percorre o vetor do início ao fim até achar o título.
 * Parâmetros: vetor, n - dados; titulo - procurado;
 *             comparacoes - acumula quantas comparações de string foram feitas.
 * Retorno: índice do livro ou -1 se não encontrou.
 * Complexidade: O(n). Não exige vetor ordenado.
 */
int buscaSequencialPorTitulo(Livro** vetor, int n, const char* titulo, long& comparacoes) {
    for (int i = 0; i < n; i++) {
        comparacoes++;
        if (strcmp(vetor[i]->titulo, titulo) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * buscaBinariaPorTitulo: divide o intervalo ao meio a cada passo.
 * Parâmetros: vetor, n - dados (PRECISA estar ordenado por título);
 *             titulo - procurado; comparacoes - acumula as comparações.
 * Retorno: índice do livro ou -1 se não encontrou.
 * Complexidade: O(log n).
 */
int buscaBinariaPorTitulo(Livro** vetor, int n, const char* titulo, long& comparacoes) {
    int inicio = 0;
    int fim = n - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        comparacoes++;
        int cmp = strcmp(vetor[meio]->titulo, titulo);
        if (cmp == 0) {
            return meio;
        }
        if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}
