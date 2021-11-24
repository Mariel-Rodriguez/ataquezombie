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
    this->maxEnemigos = 6;
    this->mouseHeld = false;
    this->vida = 10;
    this->finDelJuego= false;

}

void Juego::iniciarVentana() {

    fps = 60;

    this->videoMode.height = 768;
    this->videoMode.width = 1024;
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

void Juego::inicializarMira(){
    this->txt_mira.loadFromFile("./Imagenes/mira1.png");
    this->spr_mira.setTexture(txt_mira);
    this->spr_mira.setScale(0.15f,0.15f);
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

    //Randomizar el tamaño de los enemigos
    int tamanio = rand() % 3;

    switch (tamanio) {
        case 0:
            this->spr_zombie1.setScale(0.2f,0.2f);
            this->spr_zombie2.setScale(0.2f,0.2f);
            this->spr_zombie3.setScale(0.3f,0.3f);
            break;
        case 1:
            this->spr_zombie1.setScale(0.2f,0.2f);
            this->spr_zombie2.setScale(0.1f,0.1f);
            this->spr_zombie3.setScale(0.35f,0.35f);
            break;
        case 2:
            this->spr_zombie1.setScale(0.3f,0.3f);
            this->spr_zombie2.setScale(0.15f,0.15f);
            this->spr_zombie3.setScale(0.1f,0.1f);
            break;
        case 3:
            this->spr_zombie1.setScale(0.23f,0.23f);
            this->spr_zombie2.setScale(0.25f,0.25f);
            this->spr_zombie3.setScale(0.4f,0.4f);
            break;
        default:
            this->spr_zombie1.setScale(0.2f,0.2f);
            this->spr_zombie2.setScale(0.1f,0.1f);
            this->spr_zombie3.setScale(0.1f,0.1f);
            break;
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

void Juego::inicializarFont(){
    if(this->font.loadFromFile("./Fonts/Dosis-Light.ttf")){
     cout<<"ERROR::JUEGO::INICIALIZACION_FONTS:Fallo al intentar cargar el font"<<"\n";
    }
}

void Juego::inicializarTexto() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(Color::White);
    this->uiText.setString("NADA");
}





//Constructor
Juego::Juego() {

    this->inicializarVariables();
    this->iniciarVentana();
    this->inicializarFondo();
    this->inicializarFont();
    this->inicializarTexto();
    this->inicializarMira();
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
            case Event::MouseMoved:
                spr_mira.setPosition((Vector2f)Mouse::getPosition(*ventana1));
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

    //Ocultar el mouse y hacerlo mira
    ventana1->setMouseCursorVisible(false);
    evento = new Event;

}

void Juego::updateTexto() {

    stringstream ss;

    ss<<"Puntos: "<<this->puntos <<"\n"
      <<"Vida: " << this->vida << "\n";

    this->uiText.setString(ss.str());
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


                    //Obtener puntos
                    this->puntos += 1;
                    cout<<"Puntos: "<<this->puntos <<"\n";


                    //Borrar el enemigo
                    deleted = true;
                    this->spr_enemigos.erase(this->spr_enemigos.begin() + i);
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

        this->updateTexto();

        this->updateEnemigos();
    }

    //Condicion de fin de juego
    if(this->vida<=0){
        this->finDelJuego = true;
    }


}

void Juego::renderTexto(RenderTarget &target){
    target.draw(this->uiText);
}

void Juego::renderEnemigos(RenderTarget &target) {
    //Renderizando los enemigos
    for (auto &e : this->spr_enemigos) {
        target.draw(e);
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
    this->ventana1->draw(this->spr_mira);
    this->renderEnemigos(*this->ventana1);

    this->renderTexto(*this->ventana1);

    this->ventana1->display();
}



