//
// Created by Mariel on 23/11/2021.
//
#include "Juego.h"


//Funciones privadas
void Juego::inicializarVariables() {
    this->ventana1 = nullptr;

   //Logica de juego
    this->puntos = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemigos = 8;
    this->mouseHeld = false;
    this->vida = 10;
    this->finDelJuego= false;

}

void Juego::iniciarVentana() {

    fps = 60;

    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->ventana1 = new RenderWindow(this->videoMode ,"ZombieLand-Info-2-Proyect",Style::Titlebar | Style::Close);

    this->ventana1->setFramerateLimit(fps);

}

void Juego::inicializarZombies1() {

    this->txt_zombie1.loadFromFile("./Imagenes/zombie1.png");
    this->spr_zombie1.setTexture(txt_zombie1);
    this->spr_zombie1.setScale(0.2f,0.2f); //Esa f significa que son valores floats
}
void Juego::inicializarZombies2() {

    this->txt_zombie2.loadFromFile("./Imagenes/zombie2.png");
    this->spr_zombie2.setTexture(txt_zombie2);
    this->spr_zombie2.setPosition(150.f,150.f);
    this->spr_zombie2.setScale(0.1f,0.1f);
}
void Juego::inicializarZombies3() {

    this->txt_zombie3.loadFromFile("./Imagenes/zombie3.png");
    this->spr_zombie3.setTexture(txt_zombie3);
    this->spr_zombie3.setPosition(400.f,150.f);
    this->spr_zombie3.setScale(0.1f,0.1f);
}

void Juego::spawnEnemigos() {
    //Aca va a spawnear zombies enemigos con diferentes tamaños y los añade al vector
    this->spr_zombie1.setPosition(
            static_cast<float>(rand() % static_cast<int>(this->ventana1->getSize().x - this->spr_zombie1.getGlobalBounds().width)),
            0.f
    );

    if(this->spr_zombie2.getPosition() != this->spr_zombie1.getPosition() && this->spr_zombie2.getPosition() != this->spr_zombie3.getPosition()){
        this->spr_zombie2.setPosition(
                static_cast<float>(rand() % static_cast<int>(this->ventana1->getSize().x - this->spr_zombie2.getGlobalBounds().width)),
                2.f
        );

    }else{
        this->spr_zombie2.setPosition(
                static_cast<float>(rand() % static_cast<int>(this->ventana1->getSize().x - this->spr_zombie2.getGlobalBounds().width)),
                0.f
        );
    }

    if(this->spr_zombie3.getPosition() != this->spr_zombie1.getPosition() && this->spr_zombie3.getPosition() != this->spr_zombie2.getPosition()){
        this->spr_zombie3.setPosition(
                static_cast<float>(rand() % static_cast<int>(this->ventana1->getSize().x - this->spr_zombie3.getGlobalBounds().width)),
                4.f
        );
    }else{
        this->spr_zombie3.setPosition(
                static_cast<float>(rand() % static_cast<int>(this->ventana1->getSize().x - this->spr_zombie3.getGlobalBounds().width)),
                0.f
        );
    }


    //Spawnea el enemigo
    this->spr_enemigos.push_back(this->spr_zombie1);
    this->spr_enemigos.push_back(this->spr_zombie2);
    this->spr_enemigos.push_back(this->spr_zombie3);

    //Remover el enemigo al borde bajo de la pantalla
}

void Juego::inicializarFondo() {
    this->txt_fondo.loadFromFile("./Imagenes/bosque.png");
    this->spr_fondo.setTexture(txt_fondo);
}

void Juego::inicializarEnemigos() {


}





//Constructor
Juego::Juego() {

    this->inicializarVariables();
    this->iniciarVentana();
    this->inicializarFondo();
    this->inicializarZombies1();
    this->inicializarZombies2();
    this->inicializarZombies3();

}

//Accesores
const bool Juego::running() const {
    return this->ventana1->isOpen();
}

const bool Juego::getFinDeJuego() const {
    return this->finDelJuego;
}


void Juego::pollEvents() {
    while(this->ventana1->pollEvent(this->event)){
        switch (this->event.type) {
            case Event::Closed:
                this->ventana1->close();
                break;
            case Event::KeyPressed:
                if(this->event.key.code==sf::Keyboard::Escape){
                    this->ventana1->close();
                    break;
                }
        }
    }
}

void Juego::updateMousePos() {

    //Actualizar la posicion del mouse
    //Posicion relativa del mouse con respecto a la pantalla
    //cout << "Posicion del mouse: "<< Mouse::getPosition().x << Mouse::getPosition().y <<"\n";

    //Posicion relativa del mouse con respecto a la ventana

    this->mousePosWindow = Mouse::getPosition(*this->ventana1);
    this->mousePosView = this->ventana1->mapPixelToCoords(mousePosWindow);
}

void Juego::updateEnemigos() {



    //Actualizando el tiempo para el spawn de enemigos
    if(spr_enemigos.size() < this->maxEnemigos){

        if(this->enemySpawnTimer >= this->enemySpawnTimerMax){
            //spawnea enemigos y resetea el tiempo
            this->spawnEnemigos();
            this->enemySpawnTimer = 0.f;
        }else{
            this->enemySpawnTimer += 1.f;
        }

    }

    //Remover los enemigos al borde de la pantalla

    //Moviendo y actualizando el estado de los enemigos
    for (int i= 0 ; i < this->spr_enemigos.size() ; i++) {

        bool deleted = false;

        this->spr_enemigos[i].move(0.f , 3.f);

        if(this->spr_enemigos[i].getPosition().y > this->ventana1->getSize().y){
            this->spr_enemigos.erase(this->spr_enemigos.begin() + i);
            this->vida -= 1;
            cout<<"Vida: "<<this->vida <<"\n";
        }
    }


    //Checkeo si existe un click y mata a los enemigos en caso haya

    if(Mouse::isButtonPressed(Mouse::Left)){

        if(this->mouseHeld == false){
        this->mouseHeld = true;
        bool deleted = false;

            for(int i=0; i<this->spr_enemigos.size() && deleted==false; i++){

                if(this->spr_enemigos[i].getGlobalBounds().contains(this->mousePosView)){

                    //Borrar el enemigo
                    deleted = true;
                    this->spr_enemigos.erase(this->spr_enemigos.begin() + i);

                    //Obtener puntos
                    this->puntos += 1;
                    cout<<"Puntos: "<<this->puntos <<"\n";
                }



            }
         }else{
            this->mouseHeld = false;
        }

    }

}

void Juego::update() {
    this->pollEvents();

    if(this->finDelJuego == false){
        this->updateMousePos();

        this->updateEnemigos();
    }

    //Condicion de fin de juego
    if(this->vida<=0){
        this->finDelJuego = true;
    }


}

void Juego::renderEnemigos() {
    //Renderizando los enemigos
    for (auto &e : this->spr_enemigos) {
        this->ventana1->draw(e);
    }
}


void Juego::render() {

    /*
        @return void
        -Limpiar la pantalla de frames viejos
        -Renderizar los objetos
        -Display los frames

     */

    this->ventana1->clear();

    //Dibujar los objetos del juego
    this->ventana1->draw(this->spr_fondo);
    //this->ventana1->draw(this->spr_zombie1);
    //this->ventana1->draw(this->spr_zombie2);
    //this->ventana1->draw(this->spr_zombie3);
    this->renderEnemigos();

    this->ventana1->display();
}



