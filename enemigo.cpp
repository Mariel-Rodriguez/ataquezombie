//
// Created by guada on 22/11/2021.
//

#include "enemigo.h"
#include "SFML\Graphics.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

enemigo::enemigo(sf::Vector2f posicion) {
    int numero_enemigo;
    numero_enemigo = rand() % 3 + 1;

    string path;
    path = "z" + to_string(numero_enemigo) + ".png";
    txt_monster.loadFromFile(path);
    spr_monster.setTexture(txt_monster);

    spr_monster.setPosition(posicion);

    reloj1 = new sf::Clock;
    *tiempo1 = reloj1->getElapsedTime();


}

sf::Sprite enemigo::get_sprite() {
    return spr_monster;
}

float enemigo::get_seconds() {
    *tiempo1 = reloj1->getElapsedTime();
    return tiempo1->asSeconds();
}