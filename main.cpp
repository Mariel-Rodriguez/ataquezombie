#include <iostream>
#include <SFML/Graphics.hpp>
#include "Juego.h"

using namespace sf;

using namespace std;

int main(int argc, char *args[]) {

    //Inicializar el random
    srand(static_cast<unsigned >(time(NULL))); //El static cast unsigned es para no tener warnings

    //Creo el juego
    Juego juego;

    //Aca loopeo el juego (Se sale con escape)
    while (juego.running()) {
        //Update
        juego.update();
        //Render
        juego.render();

    }

    return 0;

}
