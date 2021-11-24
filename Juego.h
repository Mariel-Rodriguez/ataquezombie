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
using namespace sf;
using namespace std;

class Juego {

private:

    RenderWindow * ventana1;
    Event event;
    VideoMode videoMode;

    //Funciones para valores por defecto para abrir la ventana
    void inicializarVariables();
    void iniciarVentana();
    void inicializarEnemigos();
    void inicializarFondo();
    void inicializarZombies1();
    void inicializarZombies2();
    void inicializarZombies3();
    //Para los frames y ande en cualquier pc
    int fps;


    //Logica de juego
    int puntos;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemigos;

    //Objetos de juego
    vector<Texture> txt_enemigos;
    vector<Sprite> spr_enemigos;
    vector<RectangleShape> enemies;

    RectangleShape enemigo;

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


public:
    //Constructor
    Juego();

    //Accesores
    const bool running() const;

    //Funciones activas
    void spawnEnemigos();

    void pollEvents();
    void updateMousePos();

    void updateEnemigos();
    void update();

    void render();
    void renderEnemigos();


};

#endif //INFORMATICA2_JUEGO_H
