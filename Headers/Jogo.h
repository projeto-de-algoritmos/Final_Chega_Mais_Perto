#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib> /// Para função srand()
#include<ctime> /// Para função rand()

// Game Engine

class Jogo{
    private:
        sf::RenderWindow* window;
        sf::Event e;
        sf::VideoMode videomode;
        sf::ContextSettings settings;
        sf::Font font;

        void iniciarVariaveis();
        void iniciarWindow();
        

    public:
        //Variáveis
        float fps;
        int direcao;
        // Construtores / Desconstrutores
        Jogo();
        virtual ~Jogo();

        //Acessor
        const bool running() const;

        // Funções
        void desenhaInimigo(std::vector<sf::CircleShape> inimigo);
        void desenhaJogador(sf::CircleShape jogador);
        void setFrtL(int fps);
        void pollEvents();
        void update();
        void render();
        void proximaFase(int fase);
        bool perdeuTudo(int fase);
        void voltaMenu();
};

