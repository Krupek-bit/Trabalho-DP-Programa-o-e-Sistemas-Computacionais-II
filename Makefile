CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

biblioteca: main.o biblioteca.o livro.o usuario.o fila.o pilha.o historico.o busca_ordenacao.o
	$(CXX) $(CXXFLAGS) -o biblioteca $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o biblioteca
