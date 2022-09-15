#include "../Headers/Menu.h"


void Menu::iniciaMenu(float width, float height)
{
	this->window = nullptr;
	std::string nomeJanela = "Par de pontos mais próximo";
	std::basic_string<sf::Uint32> nomeJanelaFinal;
	sf::Utf8::toUtf32(nomeJanela.begin(), nomeJanela.end(), std::back_inserter(nomeJanelaFinal));
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), nomeJanelaFinal);
	if (!font.loadFromFile("../Fontes/arial.ttf"))
	{
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Jogar");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	std::string str = "Opções";
	std::basic_string<sf::Uint32> out;
	sf::Utf8::toUtf32(str.begin(), str.end(), std::back_inserter(out));
	menu[1].setString(out);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Sair");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 3));

	selectedItemIndex = 0;
}


Menu::~Menu(){
}

void Menu::draw()
{
	for (int i = 0; i < 3; i++)
	{
		this->window->draw(menu[i]);
	}
}

void Menu::MoveUp(){
	if(selectedItemIndex == 0){
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = 2;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}else if(selectedItemIndex - 1 >= 0){
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if(selectedItemIndex == 2){
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = 0;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}else if (selectedItemIndex + 1 < 3)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::fazMenu(){

	//Menu menu;
	this->iniciaMenu(800, 600);
	while (this->window->isOpen())
	{
		sf::Event event;

		while (this->window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					this->MoveUp();
					break;

				case sf::Keyboard::Down:
					this->MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (this->GetPressedItem())
					{
					case 0:
						this->window->close();
						return 1;
					case 1:
						this->window->clear();
						return 2;
					case 2:
						window->close();
						return 3;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				this->window->close();

				break;

			}
		}

		this->window->clear();

		this->draw();

		this->window->display();
	}
	return 3;
}

int Menu::fazOpcoes(){
    if (!font.loadFromFile("../Fontes/arial.ttf"))
	{
		// handle error
	}
    sf::Text texto; 
    texto.setFont(font);
	texto.setFillColor(sf::Color::White);
	std::string suporte = "Escolha a dificuldade do jogo";
    std::basic_string<sf::Uint32> out;
	sf::Utf8::toUtf32(suporte.begin(), suporte.end(), std::back_inserter(out));
    texto.setString(out);
	texto.setPosition(sf::Vector2f(800 / 3 , 600 / (3 + 1) * 1));

	opcoes[0].setFont(font);
	opcoes[0].setFillColor(sf::Color::Red);
	std::string str2 = "Fácil";
	std::basic_string<sf::Uint32> out1;
	sf::Utf8::toUtf32(str2.begin(), str2.end(), std::back_inserter(out1));
	opcoes[0].setString(out1);
	opcoes[0].setPosition(sf::Vector2f(800 / 2, 600 / (3 + 1) * 2));

	opcoes[1].setFont(font);
	opcoes[1].setFillColor(sf::Color::White);
	std::string str1 = "Difícil";
	std::basic_string<sf::Uint32> out2;
	sf::Utf8::toUtf32(str1.begin(), str1.end(), std::back_inserter(out2));
	opcoes[1].setString(out2);
	opcoes[1].setPosition(sf::Vector2f(800 / 2, 600 / (3 + 1) * 3));

    this->window->clear();
	this->window->draw(texto);
	this->window->draw(opcoes[0]);
	this->window->draw(opcoes[1]);
    this->window->display();

	int contador = 0;
    while (this->window->isOpen()){
		sf::Event event;

		while (this->window->pollEvent(event)){
			if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::Up){
					opcoes[contador].setFillColor(sf::Color::White);
					contador--;
					if(contador < 0)
						contador = 1;
					opcoes[contador].setFillColor(sf::Color::Red);
                    //return;
                } else if(event.key.code == sf::Keyboard::Down){
					opcoes[contador].setFillColor(sf::Color::White);
					contador++;
					if(contador > 1)
						contador = 0;
					opcoes[contador].setFillColor(sf::Color::Red);
				} else if(event.key.code == sf::Keyboard::Return){
					this->window->close();
					return contador;
				}
            }else if(event.type == sf::Event::Closed){
                this->window->close();
            }
        }
		this->window->clear();
		this->window->draw(texto);
		this->window->draw(opcoes[0]);
		this->window->draw(opcoes[1]);

		this->window->display();
    }
	return 0;
}