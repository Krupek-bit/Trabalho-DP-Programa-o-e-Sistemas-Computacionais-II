#include <iostream>
#include "biblioteca.h"
using namespace std;

const int LIMITE_BUFFER = 10000;

/*
 * lerInteiro: mostra uma mensagem e lê um inteiro, repetindo até ser válido.
 * Parâmetros: mensagem - texto exibido.
 * Retorno: o inteiro lido.
 */
int lerInteiro(const char* mensagem) {
    int valor;
    cout << mensagem;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(LIMITE_BUFFER, '\n');
        cout << "Valor invalido. " << mensagem;
    }
    cin.ignore(LIMITE_BUFFER, '\n');
    return valor;
}

/*
 * lerTexto: mostra uma mensagem e lê uma linha de texto.
 * Parâmetros: mensagem - texto exibido; destino - vetor que recebe o texto;
 *             tamanho - capacidade do vetor.
 * Retorno: nenhum.
 */
void lerTexto(const char* mensagem, char* destino, int tamanho) {
    cout << mensagem;
    cin.getline(destino, tamanho);
}

/*
 * exibirMenu: imprime as opções do sistema.
 * Parâmetros: nenhum. Retorno: nenhum.
 */
void exibirMenu() {
    cout << "\n===== SISTEMA DE BIBLIOTECA =====" << endl;
    cout << "1  - Cadastrar livro" << endl;
    cout << "2  - Cadastrar usuario" << endl;
    cout << "3  - Emprestar livro" << endl;
    cout << "4  - Devolver livro" << endl;
    cout << "5  - Reservar livro (fila)" << endl;
    cout << "6  - Listar catalogo por codigo (ABB in-ordem)" << endl;
    cout << "7  - Listar catalogo por titulo (Insertion Sort)" << endl;
    cout << "8  - Historico de um usuario" << endl;
    cout << "9  - Desfazer ultima acao (pilha)" << endl;
    cout << "10 - Comparar busca sequencial x binaria" << endl;
    cout << "11 - Ver fila de reservas de um livro" << endl;
    cout << "12 - Carregar dados de exemplo" << endl;
    cout << "0  - Sair" << endl;
}

/*
 * acaoCadastrarLivro: lê os dados e cadastra um livro.
 * Parâmetros: b - biblioteca. Retorno: nenhum.
 */
void acaoCadastrarLivro(Biblioteca& b) {
    char titulo[60];
    char autor[40];
    int codigo = lerInteiro("Codigo: ");
    lerTexto("Titulo: ", titulo, sizeof(titulo));
    lerTexto("Autor: ", autor, sizeof(autor));
    int ano = lerInteiro("Ano: ");
    if (cadastrarLivro(b, codigo, titulo, autor, ano)) {
        cout << "Livro cadastrado." << endl;
    } else {
        cout << "Ja existe livro com esse codigo." << endl;
    }
}

/*
 * acaoCadastrarUsuario: lê os dados e cadastra um usuário.
 * Parâmetros: b - biblioteca. Retorno: nenhum.
 */
void acaoCadastrarUsuario(Biblioteca& b) {
    char nome[50];
    int id = lerInteiro("Id do usuario: ");
    lerTexto("Nome: ", nome, sizeof(nome));
    if (cadastrarUsuario(b, id, nome)) {
        cout << "Usuario cadastrado." << endl;
    } else {
        cout << "Ja existe usuario com esse id." << endl;
    }
}

/*
 * acaoComparar: pede um título e roda a comparação de buscas.
 * Parâmetros: b - biblioteca. Retorno: nenhum.
 */
void acaoComparar(Biblioteca& b) {
    char titulo[60];
    lerTexto("Titulo exato (ex.: Livro Teste 0099): ", titulo, sizeof(titulo));
    compararBuscas(b, titulo);
}

/*
 * lerLivroEUsuario: lê o código de um livro e o id de um usuário, NESSA ordem.
 * (Feito em função própria porque a ordem de avaliação dos argumentos de uma
 * chamada em C++ não é garantida.)
 * Parâmetros: codigo e idUsuario - recebem os valores lidos (por referência).
 * Retorno: nenhum.
 */
void lerLivroEUsuario(int& codigo, int& idUsuario) {
    codigo = lerInteiro("Codigo do livro: ");
    idUsuario = lerInteiro("Id do usuario: ");
}

/*
 * acaoEmprestar: lê livro e usuário e faz o empréstimo.
 * Parâmetros: b - biblioteca. Retorno: nenhum.
 */
void acaoEmprestar(Biblioteca& b) {
    int codigo, idUsuario;
    lerLivroEUsuario(codigo, idUsuario);
    emprestarLivro(b, codigo, idUsuario);
}

/*
 * acaoReservar: lê livro e usuário e faz a reserva.
 * Parâmetros: b - biblioteca. Retorno: nenhum.
 */
void acaoReservar(Biblioteca& b) {
    int codigo, idUsuario;
    lerLivroEUsuario(codigo, idUsuario);
    reservarLivro(b, codigo, idUsuario);
}

/*
 * executarOpcao: chama a função correspondente à opção escolhida.
 * Parâmetros: b - biblioteca; opcao - número digitado no menu.
 * Retorno: nenhum.
 */
void executarOpcao(Biblioteca& b, int opcao) {
    switch (opcao) {
        case 1: acaoCadastrarLivro(b); break;
        case 2: acaoCadastrarUsuario(b); break;
        case 3: acaoEmprestar(b); break;
        case 4: devolverLivro(b, lerInteiro("Codigo do livro: ")); break;
        case 5: acaoReservar(b); break;
        case 6: percorrerEmOrdem(b.catalogo); break;
        case 7: listarPorTitulo(b); break;
        case 8: mostrarHistorico(b, lerInteiro("Id do usuario: ")); break;
        case 9: desfazerUltimaAcao(b); break;
        case 10: acaoComparar(b); break;
        case 11: mostrarReservas(b, lerInteiro("Codigo do livro: ")); break;
        case 12: carregarDadosExemplo(b, lerInteiro("Quantos livros de teste (ate 1000)? ")); break;
        default: cout << "Opcao invalida." << endl;
    }
}

int main() {
    Biblioteca biblioteca;
    iniciarBiblioteca(biblioteca);
    int opcao = -1;
    while (opcao != 0) {
        exibirMenu();
        opcao = lerInteiro("Opcao: ");
        if (opcao != 0) {
            executarOpcao(biblioteca, opcao);
        }
    }
    liberarBiblioteca(biblioteca);
    cout << "Ate logo!" << endl;
    return 0;
}
