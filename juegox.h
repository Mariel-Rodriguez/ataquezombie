//
// Created by guada on 22/11/2021.
//

#ifndef INFORMATICA2_JUEGOX_H
#define INFORMATICA2_JUEGOX_H
#endif //INFORMATICA2_JUEGOX_H

#include <iostream>
#include "SFML\Graphics.hpp"
#include "enemigo.h"
#include <cstdlib>

using namespace std;

class juegox {
public:
    juegox(sf::Vector2f resolucion, sf::String titulo);

    [[noreturn]] void gameloop();

    void cargar_graficos();

    void procesar_eventos();
    void chequear_enemigos();

private:
    sf::RenderWindow *ventana1;

    sf::Texture txt_fondo;
    sf::Sprite spr_fondo;

    sf::Texture txt_mira;
    sf::Sprite spr_mira;


    sf::Event *evento1;

    enemigo *monsters[4];

    sf::Clock *reloj1;
    sf::Time *tiempo1;
    float tiempo2;

    bool game_over;
    bool slots_monsters[4];
    int fps;


};
