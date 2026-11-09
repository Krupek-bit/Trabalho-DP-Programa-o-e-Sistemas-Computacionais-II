#ifndef USUARIO_H
#define USUARIO_H
#include "historico.h"

struct Usuario {
    int id;
    char nome[50];
    NoHistorico* historico;   // lista encadeada de empréstimos/devoluções
};

// Lista encadeada de usuários cadastrados.
struct NoUsuario {
    Usuario usuario;
    NoUsuario* prox;
};

NoUsuario* adicionarUsuario(NoUsuario*& lista, int id, const char* nome);
NoUsuario* buscarUsuario(NoUsuario* lista, int id);
void imprimirUsuarios(const NoUsuario* lista);
void liberarUsuarios(NoUsuario*& lista);

#endif
