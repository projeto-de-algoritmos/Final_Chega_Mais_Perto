
#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include <cfloat>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <bits/stdc++.h>
#include "mergeSort.h"

class Menor{
    private:

    public:
        struct suporte{
            float x;
            float y;
        };
        std::vector<Menor::suporte> calculaMinimo(sf::Vector2f jogador, std::vector<sf::Vector2f> inimigos, int tamanho);
};