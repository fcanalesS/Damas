#include <stdexcept>

#include "Pieza.h"
#include "JuegoController.h"

using namespace std;

void Pieza::moverHacia(int nuevaPosicion)
{
    if (posicion == nuevaPosicion) throw runtime_error("Error. Moviendo la pieza a la misma posicion. No tiene sentido");

    parent->setPieza(posicion, nullptr);
    if (parent->getPieza(nuevaPosicion) == nullptr)
    {
        parent->setPieza(nuevaPosicion, this);
        posicion = nuevaPosicion;
    }
    else
        throw runtime_error("Error. Moviendo la pieza a un lugar ocupado actualmente");
}

Pieza::Pieza(Jugador *duenio, JuegoController *parent, int posicion, int tipo) :
    duenio(duenio), parent(parent), tipo(tipo), posicion(posicion)
{

}

Pieza::~Pieza() { }
