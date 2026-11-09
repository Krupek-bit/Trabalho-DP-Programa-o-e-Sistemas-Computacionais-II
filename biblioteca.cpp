#include <iostream>
#include <cstdio>
#include "biblioteca.h"
#include "busca_ordenacao.h"
using namespace std;

/*
 * iniciarBiblioteca: deixa todas as estruturas vazias.
 * Parâmetros: b - biblioteca (por referência).
 * Retorno: nenhum.
 */
void iniciarBiblioteca(Biblioteca& b) {
    b.catalogo = nullptr;
    b.usuarios = nullptr;
    iniciarPilha(b.desfazer);
}

/*
 * liberarBiblioteca: libera toda a memória alocada com new.
 * Parâmetros: b - biblioteca.
 * Retorno: nenhum.
 */
void liberarBiblioteca(Biblioteca& b) {
    liberarArvore(b.catalogo);
    liberarUsuarios(b.usuarios);
    liberarPilha(b.desfazer);
}

/*
 * cadastrarLivro: cria o livro e o insere na ABB do catálogo.
 * Parâmetros: b - biblioteca; codigo, titulo, autor, ano - dados do livro.
 * Retorno: true se cadastrou, false se o código já existia.
 */
bool cadastrarLivro(Biblioteca& b, int codigo, const char* titulo, const char* autor, int ano) {
    bool inserido = false;
    Livro livro = criarLivro(codigo, titulo, autor, ano);
    b.catalogo = inserirLivro(b.catalogo, livro, inserido);
    return inserido;
}

/*
 * cadastrarUsuario: adiciona um usuário à lista encadeada.
 * Parâmetros: b - biblioteca; id - identificador único; nome - nome.
 * Retorno: true se cadastrou, false se o id já existia.
 */
bool cadastrarUsuario(Biblioteca& b, int id, const char* nome) {
    return adicionarUsuario(b.usuarios, id, nome) != nullptr;
}

/*
 * registrarEmprestimo: aplica o empréstimo (estado do livro, histórico e pilha).
 * Parâmetros: b - biblioteca; livro - livro emprestado; usuario - quem pegou.
 * Retorno: nenhum.
 */
static void registrarEmprestimo(Biblioteca& b, Livro& livro, Usuario& usuario) {
    livro.disponivel = false;
    livro.idUsuarioAtual = usuario.id;
    inserirHistorico(usuario.historico, livro.codigo, ACAO_EMPRESTIMO);
    Acao acao = { ACAO_EMPRESTIMO, livro.codigo, usuario.id };
    empilhar(b.desfazer, acao);
}

/*
 * podeEmprestar: confere disponibilidade e prioridade da fila de reservas.
 * Se o usuário é o primeiro da fila, ele é removido dela (a reserva é cumprida).
 * Parâmetros: livro - livro desejado; idUsuario - quem quer emprestar.
 * Retorno: true se o empréstimo é permitido.
 */
static bool podeEmprestar(Livro& livro, int idUsuario) {
    if (!livro.disponivel) {
        cout << "Livro indisponivel. Use a opcao de reserva." << endl;
        return false;
    }
    if (filaVazia(livro.reservas)) {
        return true;
    }
    if (livro.reservas.inicio->idUsuario != idUsuario) {
        cout << "Ha reservas na frente. Proximo da fila: usuario "
             << livro.reservas.inicio->idUsuario << endl;
        return false;
    }
    int atendido;
    desenfileirar(livro.reservas, atendido);   // reserva cumprida
    return true;
}

/*
 * emprestarLivro: empresta um livro a um usuário, respeitando a fila de reservas.
 * Parâmetros: b - biblioteca; codigo - livro; idUsuario - usuário.
 * Retorno: true se o empréstimo foi feito.
 */
bool emprestarLivro(Biblioteca& b, int codigo, int idUsuario) {
    NoABB* no = buscarLivro(b.catalogo, codigo);
    NoUsuario* usuario = buscarUsuario(b.usuarios, idUsuario);
    if (no == nullptr || usuario == nullptr) {
        cout << "Livro ou usuario nao encontrado." << endl;
        return false;
    }
    if (!podeEmprestar(no->livro, idUsuario)) {
        return false;
    }
    registrarEmprestimo(b, no->livro, usuario->usuario);
    cout << "Emprestimo realizado: " << no->livro.titulo << endl;
    return true;
}

/*
 * devolverLivro: registra a devolução e avisa quem é o próximo da fila.
 * Parâmetros: b - biblioteca; codigo - livro devolvido.
 * Retorno: true se a devolução foi feita.
 */
bool devolverLivro(Biblioteca& b, int codigo) {
    NoABB* no = buscarLivro(b.catalogo, codigo);
    if (no == nullptr || no->livro.disponivel) {
        cout << "Livro nao encontrado ou nao esta emprestado." << endl;
        return false;
    }
    Livro& livro = no->livro;
    NoUsuario* usuario = buscarUsuario(b.usuarios, livro.idUsuarioAtual);
    Acao acao = { ACAO_DEVOLUCAO, codigo, livro.idUsuarioAtual };
    if (usuario != nullptr) {
        inserirHistorico(usuario->usuario.historico, codigo, ACAO_DEVOLUCAO);
    }
    empilhar(b.desfazer, acao);
    livro.disponivel = true;
    livro.idUsuarioAtual = 0;
    cout << "Devolucao registrada: " << livro.titulo << endl;
    if (!filaVazia(livro.reservas)) {
        cout << "Livro reservado para o usuario " << livro.reservas.inicio->idUsuario << endl;
    }
    return true;
}

/*
 * reservarLivro: coloca o usuário no FINAL da fila de reservas do livro.
 * Parâmetros: b - biblioteca; codigo - livro; idUsuario - usuário.
 * Retorno: true se a reserva foi feita.
 */
bool reservarLivro(Biblioteca& b, int codigo, int idUsuario) {
    NoABB* no = buscarLivro(b.catalogo, codigo);
    if (no == nullptr || buscarUsuario(b.usuarios, idUsuario) == nullptr) {
        cout << "Livro ou usuario nao encontrado." << endl;
        return false;
    }
    Livro& livro = no->livro;
    if (livro.disponivel && filaVazia(livro.reservas)) {
        cout << "O livro esta disponivel: faca o emprestimo direto." << endl;
        return false;
    }
    if (livro.idUsuarioAtual == idUsuario || filaContem(livro.reservas, idUsuario)) {
        cout << "Usuario ja esta com o livro ou ja reservou." << endl;
        return false;
    }
    enfileirar(livro.reservas, idUsuario);
    cout << "Reserva feita. Posicao na fila: " << livro.reservas.tamanho << endl;
    return true;
}

/*
 * desfazerUltimaAcao: desempilha a última ação e reverte seus efeitos (LIFO).
 * Parâmetros: b - biblioteca.
 * Retorno: true se desfez alguma ação.
 * Observação: desfazer um empréstimo NÃO devolve o usuário à fila de reservas.
 */
bool desfazerUltimaAcao(Biblioteca& b) {
    Acao acao;
    if (!desempilhar(b.desfazer, acao)) {
        cout << "Nada para desfazer." << endl;
        return false;
    }
    NoABB* no = buscarLivro(b.catalogo, acao.codigoLivro);
    NoUsuario* usuario = buscarUsuario(b.usuarios, acao.idUsuario);
    if (no == nullptr || usuario == nullptr) {
        return false;
    }
    removerUltimoHistorico(usuario->usuario.historico);
    bool emprestimo = (acao.tipo == ACAO_EMPRESTIMO);
    no->livro.disponivel = emprestimo;              // desfaz empréstimo: volta a disponível
    no->livro.idUsuarioAtual = emprestimo ? 0 : acao.idUsuario;
    cout << "Desfeito: " << (emprestimo ? "emprestimo" : "devolucao")
         << " do livro " << acao.codigoLivro << endl;
    return true;
}

/*
 * mostrarReservas: imprime a fila de reservas de um livro.
 * Parâmetros: b - biblioteca; codigo - livro.
 * Retorno: nenhum.
 */
void mostrarReservas(Biblioteca& b, int codigo) {
    NoABB* no = buscarLivro(b.catalogo, codigo);
    if (no == nullptr) {
        cout << "Livro nao encontrado." << endl;
        return;
    }
    cout << "Fila de reservas de \"" << no->livro.titulo << "\":" << endl;
    imprimirFila(no->livro.reservas);
}

/*
 * mostrarHistorico: imprime a lista encadeada de histórico de um usuário.
 * Parâmetros: b - biblioteca; idUsuario - usuário.
 * Retorno: nenhum.
 */
void mostrarHistorico(Biblioteca& b, int idUsuario) {
    NoUsuario* usuario = buscarUsuario(b.usuarios, idUsuario);
    if (usuario == nullptr) {
        cout << "Usuario nao encontrado." << endl;
        return;
    }
    cout << "Historico de " << usuario->usuario.nome << " ("
         << contarHistorico(usuario->usuario.historico) << " registros):" << endl;
    imprimirHistorico(usuario->usuario.historico);
}

/*
 * montarVetorLivros: aloca um vetor de Livro* com todos os livros do catálogo.
 * Parâmetros: b - biblioteca; n - recebe a quantidade de livros.
 * Retorno: vetor alocado com new[] (quem chama deve dar delete[]) ou nullptr se vazio.
 */
static Livro** montarVetorLivros(Biblioteca& b, int& n) {
    n = contarLivros(b.catalogo);
    if (n == 0) {
        return nullptr;
    }
    Livro** vetor = new Livro*[n];
    int posicao = 0;
    coletarLivros(b.catalogo, vetor, posicao);
    return vetor;
}

/*
 * listarPorTitulo: ordena os livros por título com Insertion Sort e os imprime.
 * Parâmetros: b - biblioteca.
 * Retorno: nenhum.
 */
void listarPorTitulo(Biblioteca& b) {
    int n = 0;
    Livro** vetor = montarVetorLivros(b, n);
    if (vetor == nullptr) {
        cout << "Catalogo vazio." << endl;
        return;
    }
    insertionSortPorTitulo(vetor, n);
    for (int i = 0; i < n; i++) {
        imprimirLivro(*vetor[i]);
    }
    delete[] vetor;
    vetor = nullptr;
}

/*
 * compararBuscas: demonstra busca sequencial x binária contando comparações.
 * Parâmetros: b - biblioteca; titulo - título procurado (exato).
 * Retorno: nenhum.
 */
void compararBuscas(Biblioteca& b, const char* titulo) {
    int n = 0;
    Livro** vetor = montarVetorLivros(b, n);
    if (vetor == nullptr) {
        cout << "Catalogo vazio." << endl;
        return;
    }
    insertionSortPorTitulo(vetor, n);      // a busca binária exige vetor ordenado
    long compSeq = 0;
    long compBin = 0;
    int idxSeq = buscaSequencialPorTitulo(vetor, n, titulo, compSeq);
    int idxBin = buscaBinariaPorTitulo(vetor, n, titulo, compBin);
    cout << "Livros no vetor: " << n << endl;
    cout << "Sequencial: " << (idxSeq >= 0 ? "achou" : "nao achou") << " em " << compSeq << " comparacoes" << endl;
    cout << "Binaria:    " << (idxBin >= 0 ? "achou" : "nao achou") << " em " << compBin << " comparacoes" << endl;
    delete[] vetor;
    vetor = nullptr;
}

/*
 * carregarDadosExemplo: cadastra 5 livros reais, 3 usuários e 'quantidade' livros
 * de teste (códigos embaralhados para a ABB não virar uma lista).
 * Parâmetros: b - biblioteca; quantidade - livros de teste (máximo 1000).
 * Retorno: nenhum.
 */
void carregarDadosExemplo(Biblioteca& b, int quantidade) {
    cadastrarLivro(b, 1, "Dom Casmurro", "Machado de Assis", 1899);
    cadastrarLivro(b, 2, "O Cortico", "Aluisio Azevedo", 1890);
    cadastrarLivro(b, 3, "Vidas Secas", "Graciliano Ramos", 1938);
    cadastrarLivro(b, 4, "Memorias Postumas de Bras Cubas", "Machado de Assis", 1881);
    cadastrarLivro(b, 5, "A Hora da Estrela", "Clarice Lispector", 1977);
    cadastrarUsuario(b, 1, "Ana");
    cadastrarUsuario(b, 2, "Bruno");
    cadastrarUsuario(b, 3, "Carla");
    if (quantidade > 1000) {
        quantidade = 1000;
    }
    for (int i = 1; i <= quantidade; i++) {
        char titulo[60];
        snprintf(titulo, sizeof(titulo), "Livro Teste %04d", i);
        cadastrarLivro(b, 1000 + (i * 37) % 1009, titulo, "Autor Teste", 1900 + i % 120);
    }
    cout << "Dados de exemplo carregados." << endl;
}
