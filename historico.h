#ifndef HISTORICO_H
#define HISTORICO_H
#include "tipos.h"

// Lista encadeada simples com o histórico de empréstimos/devoluções de um usuário.
struct NoHistorico {
    int codigoLivro;
    TipoAcao tipo;
    NoHistorico* prox;
};

void inserirHistorico(NoHistorico*& cabeca, int codigoLivro, TipoAcao tipo);
bool removerUltimoHistorico(NoHistorico*& cabeca);
int contarHistorico(const NoHistorico* no);
void imprimirHistorico(const NoHistorico* cabeca);
void liberarHistorico(NoHistorico*& cabeca);

#endif
