#include <iostream>
#include <cstdlib>

#include "AIJugador.h"

using namespace std;

AIJugador::AIJugador(JuegoController *parent) : Jugador( parent )
{

}

AIJugador::~AIJugador()
{

}

pair<int, int> AIJugador::EsperarPorEntrada()
{
    /**
     * "Inteligencia" muy básica de la AI, elige al azar
     * un movimiento de los totales posibles.
     */

    //Una espera, para simular que está "pensando"
    parent->delay(2);

    int idx = rand() % (parent->posiblesMovimientos.size() -1);
    return parent->posiblesMovimientos.at(this).at(idx);
}

void AIJugador::InformarJugada(int desde, int hacia) { }


