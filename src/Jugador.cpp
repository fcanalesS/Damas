#include <iostream>

#include "JuegoController.h"

using namespace std;

Jugador::Jugador(JuegoController *parent) : parent(parent)
{
    color = 'n';
}

Jugador::~Jugador()
{

}
