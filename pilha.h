#ifndef PILHA_H
#define PILHA_H
#include "tipos.h"

// Pilha (LIFO) com as ações realizadas, usada para "desfazer".
struct Acao {
    TipoAcao tipo;
    int codigoLivro;
    int idUsuario;
};

struct NoPilha {
    Acao acao;
    NoPilha* prox;
};

struct Pilha {
    NoPilha* topo;
    int tamanho;
};

void iniciarPilha(Pilha& p);
void empilhar(Pilha& p, const Acao& acao);
bool desempilhar(Pilha& p, Acao& acao);
bool pilhaVazia(const Pilha& p);
void liberarPilha(Pilha& p);

#endif
