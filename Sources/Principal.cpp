#include "../Headers/Jogo.h"
#include "../Headers/Jogador.h"
#include "../Headers/menor.h"
#include "../Headers/Menu.h"
#include <SFML/Audio.hpp>

int main(){   

    sf::Music musica;
    if(!musica.openFromFile("../Musica/Minecraft.ogg")){
        std::cout << "Erro ao abrir a música\n";
    }
    musica.play();
    Menu menu;
    int opcaoMenu;
    int dificuldade = 0;
    opcaoMenu = menu.fazMenu();
    switch (opcaoMenu){
        case 1:
            break;
        case 2:
            dificuldade = menu.fazOpcoes();
            break;
        case 3:
            return 0;
        default:
            return 0;
    }

    Jogo jogo;
    
    int venceu = 5;

    Jogador jogador;

    jogador.dificuldade = dificuldade;

    jogador.fase = 0;

    Menor menor;

    jogador.iniciaSeguro();

    int contador = 0;
    

    while(jogo.running()){
        jogo.update();

        /// Escuta o teclado e move o jogador
        jogador.Movimenta(jogo.direcao);

        /// Se o jogador ou os adversários saírem do campo, ele voltam
        jogador.confereBordas();      

        /// Confere se o jogador encostou em algum inimigo ou se ele ganhou
        venceu = jogador.morreu();
        if(venceu == 1){ //jogador realmente venceu
            jogador.fase += 1;
            jogo.proximaFase(jogador.fase);
            if(dificuldade == 0) // Modo fácil
                jogo.fps += 0.5;
            else   
                jogo.fps += 1.5;
            jogo.setFrtL(jogo.fps);
            jogador.iniciaSeguro();
            //break;
        }else if(venceu == 0){//jogador perdeu tudo
            bool escolhaFim = jogo.perdeuTudo(jogador.fase);
            if(escolhaFim == true){
                jogo.~Jogo();
                opcaoMenu = menu.fazMenu();
                switch (opcaoMenu){
                    case 1:
                        venceu = 5;
                        jogador.fase = 0;
                        jogo.fps = 4;
                        jogo.setFrtL(jogo.fps);
                        jogo.voltaMenu();
                        contador = 0;
                        jogador.iniciaSeguro();
                        break;
                    case 2:
                        dificuldade = menu.fazOpcoes();
                        jogador.dificuldade = dificuldade;
                        venceu = 5;
                        jogador.fase = 0;
                        jogo.fps = 4;
                        jogo.setFrtL(jogo.fps);
                        jogo.voltaMenu();
                        contador = 0;
                        jogador.iniciaSeguro();
                        break;
                    case 3:
                        return 0;
                    default:
                        return 0;
                }
            }
            else{
                break;
            }
        }
        
        if(contador < 4){ // Espera 3 movimentos do jogador para poder movimentar o inimigo
            ++contador;
        }else{
            jogador.movimentaInimigo();
            contador = 0;
        }
        jogo.desenhaInimigo(jogador.retornaInimigo()); /// Desenha o Inimigo

        jogo.desenhaJogador(jogador.fazPersonagem()); // Desenha o Jogador

        jogo.render();
    }
    if(venceu == 1){
        std::cout << "Você venceu\n"; 
    }
    else if(venceu == 0){
        std::cout << "Você perdeu\n";
    }else if(venceu == 5){
        std::cout << "Falhou lkkkkk \n";
    }
    return 0;
}