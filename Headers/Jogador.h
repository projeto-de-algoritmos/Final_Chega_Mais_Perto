
#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib> /// Para função srand()
#include<ctime> /// Para função rand()
#include <time.h>
#include "../Headers/menor.h"
#include <random>

class Jogador : public Menor{
    private:
    // Variáveis
        int direcao;
        sf::Vector2f jogador;
        sf::CircleShape personagem;
        std::vector<sf::CircleShape> inimigo;
        std::vector<sf::Vector2f> inimigo_pos;
    // Funções
        void iniciarVariaveis();
    public:
    // Variáveis
        int fase;
        int dificuldade;
    //Funções
        void Movimenta(int direcao);
        void iniciaSeguro();
        sf::Vector2f posicao(); 
        std::vector<sf::Vector2f> posicaoInimigo();
        void movimentaInimigo();
        void confereBordas();
        int morreu();
        std::vector<sf::CircleShape> retornaInimigo();
        int retornaTamanho();
        sf::CircleShape fazPersonagem();

};