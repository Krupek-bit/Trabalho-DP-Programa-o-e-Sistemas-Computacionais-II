#include <iostream>
#include <cstring>
#include "livro.h"
using namespace std;

/*
 * criarLivro: monta um Livro disponível e com fila de reservas vazia.
 * Parâmetros: codigo, titulo, autor, ano - dados do livro.
 * Retorno: o Livro pronto (retornado por valor; a fila ainda está vazia,
 *          então a cópia não compartilha nós).
 */
Livro criarLivro(int codigo, const char* titulo, const char* autor, int ano) {
    Livro livro;
    livro.codigo = codigo;
    strncpy(livro.titulo, titulo, sizeof(livro.titulo) - 1);
    livro.titulo[sizeof(livro.titulo) - 1] = '\0';
    strncpy(livro.autor, autor, sizeof(livro.autor) - 1);
    livro.autor[sizeof(livro.autor) - 1] = '\0';
    livro.ano = ano;
    livro.disponivel = true;
    livro.idUsuarioAtual = 0;
    iniciarFila(livro.reservas);
    return livro;
}

/*
 * imprimirLivro: mostra uma linha com os dados e o estado do livro.
 * Parâmetros: livro - livro a mostrar (somente leitura).
 * Retorno: nenhum.
 */
void imprimirLivro(const Livro& livro) {
    cout << "[" << livro.codigo << "] " << livro.titulo << " - " << livro.autor
         << " (" << livro.ano << ") - ";
    if (livro.disponivel) {
        cout << "Disponivel";
    } else {
        cout << "Emprestado ao usuario " << livro.idUsuarioAtual;
    }
    cout << " | reservas: " << livro.reservas.tamanho << endl;
}

/*
 * inserirLivro: insere um livro na ABB de forma RECURSIVA, usando o código como chave.
 * Parâmetros: raiz - raiz da (sub)árvore; livro - livro a inserir;
 *             inserido - recebe true se inseriu, false se o código já existia.
 * Retorno: a raiz da (sub)árvore atualizada.
 * Complexidade: O(h), onde h é a altura (O(log n) se balanceada, O(n) no pior caso).
 */
NoABB* inserirLivro(NoABB* raiz, const Livro& livro, bool& inserido) {
    if (raiz == nullptr) {
        NoABB* novo = new NoABB;
        novo->livro = livro;
        novo->esq = nullptr;
        novo->dir = nullptr;
        inserido = true;
        return novo;
    }
    if (livro.codigo < raiz->livro.codigo) {
        raiz->esq = inserirLivro(raiz->esq, livro, inserido);
    } else if (livro.codigo > raiz->livro.codigo) {
        raiz->dir = inserirLivro(raiz->dir, livro, inserido);
    } else {
        inserido = false;   // código repetido
    }
    return raiz;
}

/*
 * buscarLivro: busca RECURSIVA por código na ABB.
 * Parâmetros: raiz - raiz da (sub)árvore; codigo - chave procurada.
 * Retorno: ponteiro para o nó encontrado ou nullptr.
 */
NoABB* buscarLivro(NoABB* raiz, int codigo) {
    if (raiz == nullptr || raiz->livro.codigo == codigo) {
        return raiz;
    }
    if (codigo < raiz->livro.codigo) {
        return buscarLivro(raiz->esq, codigo);
    }
    return buscarLivro(raiz->dir, codigo);
}

/*
 * percorrerEmOrdem: travessia in-ordem (esquerda, raiz, direita) que imprime
 * os livros em ordem crescente de código.
 * Parâmetros: raiz - raiz da (sub)árvore;
 *             apenasDisponiveis - (default false) se true, só mostra disponíveis.
 * Retorno: nenhum.
 */
void percorrerEmOrdem(const NoABB* raiz, bool apenasDisponiveis) {
    if (raiz == nullptr) {
        return;
    }
    percorrerEmOrdem(raiz->esq, apenasDisponiveis);
    if (!apenasDisponiveis || raiz->livro.disponivel) {
        imprimirLivro(raiz->livro);
    }
    percorrerEmOrdem(raiz->dir, apenasDisponiveis);
}

/*
 * contarLivros: conta os nós da árvore recursivamente.
 * Parâmetros: raiz - raiz da (sub)árvore.
 * Retorno: quantidade de livros.
 */
int contarLivros(const NoABB* raiz) {
    if (raiz == nullptr) {
        return 0;
    }
    return 1 + contarLivros(raiz->esq) + contarLivros(raiz->dir);
}

/*
 * coletarLivros: copia, em ordem de código, o ENDEREÇO de cada livro para um vetor.
 * Guardamos ponteiros (e não cópias) para não duplicar as filas de reserva.
 * Parâmetros: raiz - raiz da árvore; vetor - vetor de Livro* já alocado;
 *             posicao - próximo índice livre (por referência).
 * Retorno: nenhum.
 */
void coletarLivros(NoABB* raiz, Livro** vetor, int& posicao) {
    if (raiz == nullptr) {
        return;
    }
    coletarLivros(raiz->esq, vetor, posicao);
    vetor[posicao] = &raiz->livro;
    posicao++;
    coletarLivros(raiz->dir, vetor, posicao);
}

/*
 * liberarArvore: libera a árvore em PÓS-ORDEM (filhos antes do pai),
 * incluindo a fila de reservas de cada livro.
 * Parâmetros: raiz - raiz da árvore (por referência; termina valendo nullptr).
 * Retorno: nenhum.
 */
void liberarArvore(NoABB*& raiz) {
    if (raiz == nullptr) {
        return;
    }
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    liberarFila(raiz->livro.reservas);
    delete raiz;
    raiz = nullptr;
}
