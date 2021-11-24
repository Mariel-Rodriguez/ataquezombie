//
// Created by Mariel on 23/11/2021.
//

#ifndef INFORMATICA2_JUEGO_H
#define INFORMATICA2_JUEGO_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <ctime>
#include <sstream>

using namespace sf;
using namespace std;

class Juego {

private:

    //Generales
    RenderWindow * ventana1;
    Event event;
    VideoMode videoMode;
    Event *evento;

    //Funciones para valores por defecto para abrir la ventana
    void inicializarVariables();
    void iniciarVentana();
    void inicializarFont();
    void inicializarTexto();
    void inicializarFondo();
    void inicializarMira();
    void inicializarZombies1();
    void inicializarZombies2();
    void inicializarZombies3();

    //Para los frames y ande en cualquier pc
    int fps;

    //Resources utilizados
    Font font;

    //Texto
    Text uiText;


    //Logica de juego
    bool finDelJuego;
    unsigned puntos;
    int vida;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemigos;
    bool mouseHeld;

    //Objetos de juego
    vector<Sprite> spr_enemigos;

    Texture txt_fondo;
    Sprite spr_fondo;
    Texture txt_zombie1;
    Sprite spr_zombie1;
    Texture txt_zombie2;
    Sprite spr_zombie2;
    Texture txt_zombie3;
    Sprite spr_zombie3;

    Texture txt_mira;
    Sprite spr_mira;


    //Posiciones del mouse
    Vector2i mousePosWindow;
    Vector2f mousePosView;


public:
    //Constructor
    Juego();

    //Accesores
    const bool running() const;
    const bool getFinDeJuego() const;

    //Funciones activas
    void spawnEnemigos();

    void pollEvents();
    void updateMousePos();
    void procesarMovimiento();

    void updateTexto();
    void updateEnemigos();
    void update();

    void renderTexto(RenderTarget &target);
    void render();
    void renderEnemigos(RenderTarget &target);


};

#endif //INFORMATICA2_JUEGO_H
