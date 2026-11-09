#include <iostream>
#include "historico.h"
using namespace std;

/*
 * inserirHistorico: insere um registro no FINAL da lista encadeada.
 * Parâmetros: cabeca - início da lista (por referência, pode mudar);
 *             codigoLivro - livro envolvido; tipo - empréstimo ou devolução.
 * Retorno: nenhum.
 * Usa ponteiro para ponteiro para tratar lista vazia e não vazia do mesmo jeito.
 */
void inserirHistorico(NoHistorico*& cabeca, int codigoLivro, TipoAcao tipo) {
    NoHistorico* novo = new NoHistorico;
    novo->codigoLivro = codigoLivro;
    novo->tipo = tipo;
    novo->prox = nullptr;
    NoHistorico** p = &cabeca;
    while (*p != nullptr) {
        p = &(*p)->prox;
    }
    *p = novo;
}

/*
 * removerUltimoHistorico: remove o último registro da lista (usado no "desfazer").
 * Parâmetros: cabeca - início da lista (por referência).
 * Retorno: true se removeu, false se a lista estava vazia.
 */
bool removerUltimoHistorico(NoHistorico*& cabeca) {
    if (cabeca == nullptr) {
        return false;
    }
    NoHistorico** p = &cabeca;
    while ((*p)->prox != nullptr) {
        p = &(*p)->prox;
    }
    delete *p;
    *p = nullptr;
    return true;
}

/*
 * contarHistorico: conta os registros de forma RECURSIVA.
 * Parâmetros: no - nó atual (começa pela cabeça).
 * Retorno: quantidade de nós a partir de 'no'.
 * Caso base: nó nulo vale 0. Passo: 1 + contagem do restante.
 */
int contarHistorico(const NoHistorico* no) {
    if (no == nullptr) {
        return 0;
    }
    return 1 + contarHistorico(no->prox);
}

/*
 * imprimirHistorico: percorre a lista e mostra cada registro.
 * Parâmetros: cabeca - início da lista (somente leitura).
 * Retorno: nenhum.
 */
void imprimirHistorico(const NoHistorico* cabeca) {
    if (cabeca == nullptr) {
        cout << "(historico vazio)" << endl;
        return;
    }
    for (const NoHistorico* atual = cabeca; atual != nullptr; atual = atual->prox) {
        cout << (atual->tipo == ACAO_EMPRESTIMO ? "Emprestimo" : "Devolucao")
             << " do livro " << atual->codigoLivro << endl;
    }
}

/*
 * liberarHistorico: apaga todos os nós da lista.
 * Parâmetros: cabeca - início da lista; termina valendo nullptr.
 * Retorno: nenhum.
 */
void liberarHistorico(NoHistorico*& cabeca) {
    while (cabeca != nullptr) {
        NoHistorico* proximo = cabeca->prox;
        delete cabeca;
        cabeca = proximo;
    }
}
