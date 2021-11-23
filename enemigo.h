//
// Created by guada on 22/11/2021.
//

#include <cstdlib>
#include <iostream>
#include "SFML\Graphics.hpp"

using namespace std;

class enemigo {
public:
    enemigo(sf::Vector2f posicion);

    sf::Sprite get_sprite();

    float get_seconds();

private:
    sf::Texture txt_monster;
    sf::Sprite spr_monster;

    sf::Clock *reloj1;
    sf::Time *tiempo1;
};



