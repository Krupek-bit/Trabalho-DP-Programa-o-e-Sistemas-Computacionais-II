#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include "livro.h"
#include "usuario.h"
#include "pilha.h"

// Reúne todas as estruturas do sistema.
struct Biblioteca {
    NoABB* catalogo;      // ABB de livros (chave: código)
    NoUsuario* usuarios;  // lista encadeada de usuários
    Pilha desfazer;       // pilha de ações (LIFO)
};

void iniciarBiblioteca(Biblioteca& b);
void liberarBiblioteca(Biblioteca& b);
bool cadastrarLivro(Biblioteca& b, int codigo, const char* titulo, const char* autor, int ano);
bool cadastrarUsuario(Biblioteca& b, int id, const char* nome);
bool emprestarLivro(Biblioteca& b, int codigo, int idUsuario);
bool devolverLivro(Biblioteca& b, int codigo);
bool reservarLivro(Biblioteca& b, int codigo, int idUsuario);
bool desfazerUltimaAcao(Biblioteca& b);
void mostrarReservas(Biblioteca& b, int codigo);
void mostrarHistorico(Biblioteca& b, int idUsuario);
void listarPorTitulo(Biblioteca& b);
void compararBuscas(Biblioteca& b, const char* titulo);
void carregarDadosExemplo(Biblioteca& b, int quantidade);

#endif
