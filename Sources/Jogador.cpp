#include "../Headers/Jogador.h"

void Jogador::iniciarVariaveis(){
    this->direcao = 4;
    this->jogador = sf::Vector2f(1, 1);
    this->personagem.setFillColor(sf::Color::Blue);
    this->personagem.setRadius(10);
    this->inimigo.clear();
    this->inimigo.resize(10);
    this->inimigo_pos.clear();
    this->inimigo_pos.resize(10);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distX(1,39);
    std::uniform_int_distribution<int> distY(1,29);
    for(int i = 0; i < this->inimigo.size(); i++){//talvez menor que 6
        this->inimigo[i].setFillColor(sf::Color::Red);
        this->inimigo[i].setRadius(10);
        this->inimigo_pos[i].x = distX(mt);
        this->inimigo_pos[i].y = distY(mt);
        this->inimigo[i].setPosition(sf::Vector2f(inimigo_pos[i].x*20, inimigo_pos[i].y*20));
    }
    this->inimigo[0].setFillColor(sf::Color::Green);
    if(this->dificuldade == 1){
        this->inimigo[1].setFillColor(sf::Color::Yellow);
    }
}


void Jogador::iniciaSeguro(){
    this->iniciarVariaveis();
}

void Jogador::Movimenta(int direcao){
    if(direcao == 1)
        jogador.y--;
    if(direcao == 2)
        jogador.y++;
    if(direcao == 4)
        jogador.x++;
    if(direcao == 3)
        jogador.x--;
}

sf::Vector2f Jogador::posicao(){
    return this->jogador;
}

std::vector<sf::Vector2f> Jogador::posicaoInimigo(){
    return this->inimigo_pos;
}

void Jogador::movimentaInimigo(){
    Grafo g(1200);
    int posicao = g.retornaPosicao(g, this->inimigo_pos[1].x, this->jogador.x);
    for(int i = 0; i < this->inimigo.size(); ++i){
        this->inimigo_pos[i].x = this->inimigo_pos[i].x + ((rand() % 3) + (-1));
        this->inimigo_pos[i].y = this->inimigo_pos[i].y + ((rand() % 3) + (-1));
        this->inimigo[i].setPosition(sf::Vector2f(this->inimigo_pos[i].x*20, this->inimigo_pos[i].y*20));
    }
    this->jogador.x > this->inimigo_pos[1].x ? this->inimigo_pos[1].x++ : this->inimigo_pos[1].x--;
    this->jogador.y > this->inimigo_pos[1].y ? this->inimigo_pos[1].y++ : this->inimigo_pos[1].y--;
    this->inimigo[1].setPosition(sf::Vector2f(this->inimigo_pos[1].x*20, this->inimigo_pos[1].y*20));
}

void Jogador::confereBordas(){
    //Confere o Jogador
    if(this->jogador.x <= 0)
        this->jogador.x = 39;
    if(this->jogador.x >= 40)
        this->jogador.x = 1;
    if(this->jogador.y <= 0)
        this->jogador.y = 29;
    if(this->jogador.y >= 30)
        this->jogador.y = 1;  
    //Confere o bot
    for(int i = 0; i < this->inimigo.size(); i++){
        if(this->inimigo_pos[i].x <= 0)
            this->inimigo_pos[i].x = rand() % 40;
        if(this->inimigo_pos[i].x >= 40)
            this->inimigo_pos[i].x = rand() % 40;
        if(this->inimigo_pos[i].y <= 0)
            this->inimigo_pos[i].y = rand() % 30;
        if(this->inimigo_pos[i].y >= 30)
            this->inimigo_pos[i].y = rand() % 30;
    } 
}

int Jogador::morreu(){
    std::vector<Menor::suporte> minimo = Menor::calculaMinimo(this->posicao(), this->posicaoInimigo(), 11);
    if((minimo[0].x == this->inimigo_pos[0].x && minimo[0].y == this->inimigo_pos[0].y && minimo[1].x == this->jogador.x && minimo[1].y == this->jogador.y) || (minimo[0].x == this->jogador.x && minimo[0].y == this->jogador.y && minimo[1].x == this->inimigo_pos[0].x && minimo[1].y == this->inimigo_pos[0].y)){
        return 1;
    }
    if(this->dificuldade == 1){
        if((minimo[0].x == this->inimigo_pos[1].x && minimo[0].y == this->inimigo_pos[1].y && minimo[1].x == this->jogador.x && minimo[1].y == this->jogador.y) || (minimo[0].x == this->jogador.x && minimo[0].y == this->jogador.y && minimo[1].x == this->inimigo_pos[1].x && minimo[1].y == this->inimigo_pos[1].y)){
        return 0;
    }
    }
    for(int i = 1; i < this->inimigo.size(); ++i){
        if(this->jogador.x == this->inimigo_pos[i].x && this->jogador.y == this->inimigo_pos[i].y)
            return 0;
    }
    return 2;
}

std::vector<sf::CircleShape> Jogador::retornaInimigo(){
    return this->inimigo;
}

sf::CircleShape Jogador::fazPersonagem(){
    this->personagem.setPosition(jogador.x*20, jogador.y*20);
    this->personagem.setFillColor(sf::Color(0,255, 255));
    return this->personagem;
}