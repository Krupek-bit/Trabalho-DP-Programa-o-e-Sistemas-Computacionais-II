#ifndef LIVRO_H
#define LIVRO_H
#include "fila.h"

// Dados de um livro. Cada livro carrega sua própria fila de reservas.
struct Livro {
    int codigo;
    char titulo[60];
    char autor[40];
    int ano;
    bool disponivel;
    int idUsuarioAtual;   // quem está com o livro (0 se disponível)
    Fila reservas;
};

// Nó da Árvore Binária de Busca (catálogo ordenado por código).
struct NoABB {
    Livro livro;
    NoABB* esq;
    NoABB* dir;
};

Livro criarLivro(int codigo, const char* titulo, const char* autor, int ano);
void imprimirLivro(const Livro& livro);
NoABB* inserirLivro(NoABB* raiz, const Livro& livro, bool& inserido);
NoABB* buscarLivro(NoABB* raiz, int codigo);
void percorrerEmOrdem(const NoABB* raiz, bool apenasDisponiveis = false);
int contarLivros(const NoABB* raiz);
void coletarLivros(NoABB* raiz, Livro** vetor, int& posicao);
void liberarArvore(NoABB*& raiz);

#endif
