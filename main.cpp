#include <iostream>
#include "SFML\Graphics.hpp"
#include "juegox.h"
#include <cstdlib>


using namespace std;

int main(int argc, char *args[]) {
    srand(time(NULL));
    juegox partida1({800, 600}, "ATAQUE ZOMBIE");
    return 0;
}
