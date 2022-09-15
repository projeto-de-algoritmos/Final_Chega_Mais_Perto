all: compilar linkar

compilar:
	g++ -I -c ../Sources/Principal.cpp -c ../Sources/Jogo.cpp -c ../Sources/Jogador.cpp -c ../Sources/menor.cpp -c ../Sources/Menu.cpp -lsfml-graphics -lsfml-window -lsfml-system

linkar:
	g++ Principal.o Jogo.o Jogador.o menor.o Menu.o -o Jogo_Binario -w -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio && rm *.o

