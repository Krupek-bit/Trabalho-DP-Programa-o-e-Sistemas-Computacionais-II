# Sistema de Biblioteca em C++

Projeto Final de **Programação e Sistemas Computacionais II** — Centro Universitário Campo Real, Engenharia de Software, 2026/1 (prof. Giovane Galvão).

**Squad:** Gabriel Krupek e Gustavo Borges
**Tema escolhido:** Sistema de Biblioteca

## Descrição

Sistema de terminal para controlar o acervo de uma biblioteca: cadastro de livros e usuários, empréstimos, devoluções, fila de reservas por livro, histórico por usuário e desfazer da última ação. Tudo foi implementado manualmente, **sem STL** (sem `vector`, `queue`, `stack`, `string`), com `new`/`delete` e ponteiros.

## Como compilar e executar

```bash
make
./biblioteca
```

Ou, sem o `make`: `g++ -std=c++11 *.cpp -o biblioteca`

Dica para a demonstração: use a opção **12** (carregar dados de exemplo) e depois a **10** (comparar buscas).

## Estruturas de dados utilizadas

| Estrutura | Arquivo | Uso no sistema | Requisito |
|---|---|---|---|
| Árvore Binária de Busca | `livro.cpp` | Catálogo de livros, chave = código | R8, R3 |
| Lista encadeada | `historico.cpp`, `usuario.cpp` | Histórico de cada usuário e lista de usuários | R5 |
| Fila (FIFO) | `fila.cpp` | Reservas de cada livro | R7 |
| Pilha (LIFO) | `pilha.cpp` | Desfazer a última ação | R6 |
| Insertion Sort | `busca_ordenacao.cpp` | Listagem por título | R9 |
| Busca sequencial e binária | `busca_ordenacao.cpp` | Busca por título com contagem de comparações | R10 |

```
Biblioteca
 ├── catalogo  ──► ABB ──► NoABB { Livro { ..., Fila reservas } , esq, dir }
 ├── usuarios  ──► NoUsuario ──► NoUsuario ──► ...   (lista encadeada)
 │                   └── historico ──► NoHistorico ──► NoHistorico ──► ...
 └── desfazer  ──► topo ──► NoPilha ──► NoPilha ──► ...   (pilha)

Fila de reservas (dentro de cada Livro):
 inicio ──► NoFila ──► NoFila ──► NoFila ◄── fim
```

## Onde cada requisito aparece

| Req. | Onde |
|---|---|
| R1 Funções | Todo o código: uma responsabilidade por função (máx. 30 linhas); referência (`Biblioteca&`, `int&`) e parâmetro default em `percorrerEmOrdem(raiz, apenasDisponiveis = false)` |
| R2 Ponteiros | `Livro**` nos vetores de ordenação/busca, `NoX**` nas inserções ao fim das listas, `->` em todas as estruturas |
| R3 Recursividade | `inserirLivro`, `buscarLivro`, `percorrerEmOrdem`, `contarLivros`, `coletarLivros`, `liberarArvore`, `contarHistorico` |
| R4 Memória dinâmica | `new` em cada nó e `delete` correspondente, ponteiros liberados recebem `nullptr` |
| R5–R8 | Lista, pilha, fila e ABB (tabela acima) |
| R9 | `insertionSortPorTitulo` (O(n²), comentado no código) |
| R10 | `buscaSequencialPorTitulo` e `buscaBinariaPorTitulo`; opção 10 do menu mostra o número de comparações |

## Divisão de responsabilidades

| Integrante | Responsável por |
|---|---|
| Gabriel Krupek | `livro.*` (ABB), `busca_ordenacao.*`, `relatorio_tecnico.txt` |
| Gustavo Borges | `fila.*`, `pilha.*`, `historico.*`, `usuario.*`, `main.cpp` (menu) |
| Ambos | `biblioteca.*` (regras de negócio), README, revisão de vazamentos |

## Arquivos

```
main.cpp            menu e leitura de dados
biblioteca.h/.cpp   regras: empréstimo, devolução, reserva, desfazer
livro.h/.cpp        struct Livro e ABB
usuario.h/.cpp      usuários (lista encadeada)
historico.h/.cpp    histórico do usuário (lista encadeada)
fila.h/.cpp         fila de reservas
pilha.h/.cpp        pilha de desfazer
busca_ordenacao.*   Insertion Sort, busca sequencial e binária
tipos.h             enum TipoAcao
relatorio_tecnico.txt
```
