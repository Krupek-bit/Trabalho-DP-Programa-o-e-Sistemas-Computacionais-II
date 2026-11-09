#include "pilha.h"

/*
 * iniciarPilha: deixa a pilha vazia.
 * Parâmetros: p - pilha (por referência).
 * Retorno: nenhum.
 */
void iniciarPilha(Pilha& p) {
    p.topo = nullptr;
    p.tamanho = 0;
}

/*
 * empilhar: coloca uma ação no TOPO da pilha (LIFO).
 * Parâmetros: p - pilha; acao - ação a registrar (cópia feita no nó).
 * Retorno: nenhum.
 * Complexidade: O(1).
 */
void empilhar(Pilha& p, const Acao& acao) {
    NoPilha* novo = new NoPilha;
    novo->acao = acao;
    novo->prox = p.topo;
    p.topo = novo;
    p.tamanho++;
}

/*
 * desempilhar: remove a ação do topo (a mais recente).
 * Parâmetros: p - pilha; acao - recebe a ação removida.
 * Retorno: true se removeu, false se a pilha estava vazia.
 */
bool desempilhar(Pilha& p, Acao& acao) {
    if (p.topo == nullptr) {
        return false;
    }
    NoPilha* removido = p.topo;
    acao = removido->acao;
    p.topo = removido->prox;
    delete removido;
    removido = nullptr;
    p.tamanho--;
    return true;
}

/*
 * pilhaVazia: informa se não há ações para desfazer.
 * Parâmetros: p - pilha (somente leitura).
 * Retorno: true se vazia.
 */
bool pilhaVazia(const Pilha& p) {
    return p.topo == nullptr;
}

/*
 * liberarPilha: libera todos os nós restantes.
 * Parâmetros: p - pilha a esvaziar.
 * Retorno: nenhum.
 */
void liberarPilha(Pilha& p) {
    Acao descartada;
    while (desempilhar(p, descartada)) {
        // cada desempilhar faz o delete do nó
    }
}
