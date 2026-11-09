#ifndef BUSCA_ORDENACAO_H
#define BUSCA_ORDENACAO_H
#include "livro.h"

void insertionSortPorTitulo(Livro** vetor, int n);
int buscaSequencialPorTitulo(Livro** vetor, int n, const char* titulo, long& comparacoes);
int buscaBinariaPorTitulo(Livro** vetor, int n, const char* titulo, long& comparacoes);

#endif
