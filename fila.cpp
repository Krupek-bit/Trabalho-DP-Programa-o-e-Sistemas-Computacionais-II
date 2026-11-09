#include <iostream>
#include "fila.h"
using namespace std;

/*
 * iniciarFila: deixa a fila vazia.
 * Parâmetros: f - fila a ser inicializada (por referência).
 * Retorno: nenhum.
 */
void iniciarFila(Fila& f) {
    f.inicio = nullptr;
    f.fim = nullptr;
    f.tamanho = 0;
}

/*
 * enfileirar: insere um usuário no FINAL da fila (FIFO).
 * Parâmetros: f - fila; idUsuario - id de quem reservou.
 * Retorno: nenhum.
 * Complexidade: O(1), pois mantemos o ponteiro 'fim'.
 */
void enfileirar(Fila& f, int idUsuario) {
    NoFila* novo = new NoFila;
    novo->idUsuario = idUsuario;
    novo->prox = nullptr;
    if (f.fim == nullptr) {
        f.inicio = novo;          // fila estava vazia
    } else {
        f.fim->prox = novo;       // liga o antigo último ao novo nó
    }
    f.fim = novo;
    f.tamanho++;
}

/*
 * desenfileirar: remove o usuário do INÍCIO da fila (o que reservou primeiro).
 * Parâmetros: f - fila; idUsuario - recebe o id removido (por referência).
 * Retorno: true se removeu, false se a fila estava vazia.
 */
bool desenfileirar(Fila& f, int& idUsuario) {
    if (f.inicio == nullptr) {
        return false;
    }
    NoFila* removido = f.inicio;
    idUsuario = removido->idUsuario;
    f.inicio = removido->prox;
    if (f.inicio == nullptr) {
        f.fim = nullptr;          // a fila ficou vazia
    }
    delete removido;
    removido = nullptr;
    f.tamanho--;
    return true;
}

/*
 * filaVazia: informa se a fila não tem elementos.
 * Parâmetros: f - fila (somente leitura).
 * Retorno: true se vazia.
 */
bool filaVazia(const Fila& f) {
    return f.inicio == nullptr;
}

/*
 * filaContem: verifica se um usuário já está na fila (travessia).
 * Parâmetros: f - fila; idUsuario - id procurado.
 * Retorno: true se o usuário está na fila.
 */
bool filaContem(const Fila& f, int idUsuario) {
    for (const NoFila* atual = f.inicio; atual != nullptr; atual = atual->prox) {
        if (atual->idUsuario == idUsuario) {
            return true;
        }
    }
    return false;
}

/*
 * imprimirFila: mostra os ids na ordem de atendimento.
 * Parâmetros: f - fila (somente leitura).
 * Retorno: nenhum.
 */
void imprimirFila(const Fila& f) {
    if (filaVazia(f)) {
        cout << "(sem reservas)" << endl;
        return;
    }
    int posicao = 1;
    for (const NoFila* atual = f.inicio; atual != nullptr; atual = atual->prox) {
        cout << posicao << "o: usuario " << atual->idUsuario << endl;
        posicao++;
    }
}

/*
 * liberarFila: libera todos os nós (cada new tem seu delete).
 * Parâmetros: f - fila a esvaziar.
 * Retorno: nenhum.
 */
void liberarFila(Fila& f) {
    int descartado;
    while (desenfileirar(f, descartado)) {
        // desenfileirar já faz delete de cada nó
    }
}
