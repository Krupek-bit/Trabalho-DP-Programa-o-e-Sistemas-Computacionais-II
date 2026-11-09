#ifndef FILA_H
#define FILA_H

// Fila (FIFO) de ids de usuários que reservaram um livro.
struct NoFila {
    int idUsuario;
    NoFila* prox;
};

struct Fila {
    NoFila* inicio;
    NoFila* fim;
    int tamanho;
};

void iniciarFila(Fila& f);
void enfileirar(Fila& f, int idUsuario);
bool desenfileirar(Fila& f, int& idUsuario);
bool filaVazia(const Fila& f);
bool filaContem(const Fila& f, int idUsuario);
void imprimirFila(const Fila& f);
void liberarFila(Fila& f);

#endif
