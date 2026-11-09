#include <iostream>
#include <cstring>
#include "usuario.h"
using namespace std;

/*
 * adicionarUsuario: cadastra um usuário no FINAL da lista encadeada.
 * Parâmetros: lista - início da lista (por referência); id - identificador único;
 *             nome - nome do usuário.
 * Retorno: ponteiro para o novo nó, ou nullptr se o id já existe.
 */
NoUsuario* adicionarUsuario(NoUsuario*& lista, int id, const char* nome) {
    if (buscarUsuario(lista, id) != nullptr) {
        return nullptr;
    }
    NoUsuario* novo = new NoUsuario;
    novo->usuario.id = id;
    strncpy(novo->usuario.nome, nome, sizeof(novo->usuario.nome) - 1);
    novo->usuario.nome[sizeof(novo->usuario.nome) - 1] = '\0';
    novo->usuario.historico = nullptr;
    novo->prox = nullptr;
    NoUsuario** p = &lista;
    while (*p != nullptr) {
        p = &(*p)->prox;
    }
    *p = novo;
    return novo;
}

/*
 * buscarUsuario: busca sequencial por id na lista.
 * Parâmetros: lista - início da lista; id - id procurado.
 * Retorno: ponteiro para o nó ou nullptr se não existir.
 */
NoUsuario* buscarUsuario(NoUsuario* lista, int id) {
    for (NoUsuario* atual = lista; atual != nullptr; atual = atual->prox) {
        if (atual->usuario.id == id) {
            return atual;
        }
    }
    return nullptr;
}

/*
 * imprimirUsuarios: lista os usuários cadastrados.
 * Parâmetros: lista - início da lista (somente leitura).
 * Retorno: nenhum.
 */
void imprimirUsuarios(const NoUsuario* lista) {
    if (lista == nullptr) {
        cout << "(nenhum usuario cadastrado)" << endl;
        return;
    }
    for (const NoUsuario* atual = lista; atual != nullptr; atual = atual->prox) {
        cout << "[" << atual->usuario.id << "] " << atual->usuario.nome << endl;
    }
}

/*
 * liberarUsuarios: libera cada usuário e o histórico de cada um.
 * Parâmetros: lista - início da lista; termina valendo nullptr.
 * Retorno: nenhum.
 */
void liberarUsuarios(NoUsuario*& lista) {
    while (lista != nullptr) {
        NoUsuario* proximo = lista->prox;
        liberarHistorico(lista->usuario.historico);
        delete lista;
        lista = proximo;
    }
}
