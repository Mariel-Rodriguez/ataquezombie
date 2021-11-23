//
// Created by guada on 22/11/2021.
//
#include <iostream>
#include "SFML\Graphics.hpp"
#include "juegox.h"
#include <cstdlib>

using namespace std;

juegox::juegox(sf::Vector2f resolucion, sf::String titulo) {
    game_over = false;
    fps = 60;

    ventana1 = new sf::RenderWindow(sf::VideoMode(resolucion.x, resolucion.y), titulo);
    ventana1->setFramerateLimit(fps);
    ventana1->setMouseCursorVisible(false);


    for (int i = 0; i < 4; i++) {
        slots_monsters[i] = false;
    }


    evento1 = new sf::Event;

    cargar_graficos();

    reloj1 = new sf::Clock;
    tiempo1 = new sf::Time;

    gameloop();

}

[[noreturn]] void juegox::gameloop() {

    while (!game_over) {
        *tiempo1 = reloj1->getElapsedTime();
        if (tiempo1->asSeconds() > 2 + tiempo2) {

            tiempo2 = tiempo1->asSeconds();
            int resultado;
            resultado = rand() % 100 + 1;
            if (resultado < 20) {
                //nada
            } else {
                bool espacio_disponible = false;
                for (int i = 0; i < 4; i++) {
                    if (!slots_monsters[i]) {
                        espacio_disponible = true;
                        break;
                    }
                }
                if (espacio_disponible) {
                    while (1) {
                        int resultado = rand() % 3 + 0;
                        if (!slots_monsters[resultado]) {
                            monsters[resultado] = new enemigo({(float) (200.0 * resultado), 300.0});
                            break;
                        }
                    }
                }
            }
        }
        chequear_enemigos();
        ventana1->clear();
        procesar_eventos();
        ventana1->draw(spr_fondo);

        for (int i = 0; i < 4; i++) {
            if (monsters[i] != NULL) {
                ventana1->draw(monsters[i]->get_sprite());
            }
        }

        ventana1->draw(spr_mira);
        ventana1->display();
    }
}

void juegox::cargar_graficos() {
    txt_fondo.loadFromFile("bosque.png");
    spr_fondo.setTexture(txt_fondo);
    spr_fondo.setScale((float) ventana1->getSize().x / txt_fondo.getSize().x,
                       (float) ventana1->getSize().y / txt_fondo.getSize().y);

    txt_mira.loadFromFile("mira.png");
    spr_mira.setTexture(txt_mira);
    spr_mira.setScale(0.4f, 0.4f);
    spr_mira.setOrigin(txt_mira.getSize().x / 2, txt_mira.getSize().y / 2);
}

void juegox::procesar_eventos() {
    while (ventana1->pollEvent(*evento1)) {
        switch (evento1->type) {
            case sf::Event::MouseMoved:
                spr_mira.setPosition((sf::Vector2f) sf::Mouse::getPosition(*ventana1));
                break;
            case sf::Event::Closed:
                exit(1);
                break;
            case sf::Event::MouseButtonPressed:
                sf::FloatRect recta(spr_mira.getPosition(), (sf::Vector2f) spr_mira.getTexture()->getSize());
                for (int i = 0; i < 4; i++) {
                    if (monsters[i]) {
                        if (monsters[i]->get_sprite().getGlobalBounds().intersects(recta)) {
                            monsters[i] = NULL;
                        }
                    }
                }
                break;
        }
    }
}

void juegox::chequear_enemigos() {
    for (int i = 0; i < 4; ++i) {
        if (monsters[i]) {
            if (monsters[i]->get_seconds()>5){
                monsters[i]=NULL;
            }
        }
    }
}