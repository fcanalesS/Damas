#include <iostream>
#include <cstdlib>

#include "JugadorLocal.h"
#include "Consola.h"
#include "PiezaPeon.h"
#include "PiezaRey.h"

using namespace std;

JugadorLocal::JugadorLocal(JuegoController *parent) : Jugador(parent) { }

JugadorLocal::~JugadorLocal() { }

pair<int, int> JugadorLocal::EsperarPorEntrada()
{
    string desde = "", hacia="";
    cin >> desde;

    //Este es el comando para salir del juego en cualquier momento
    if (desde == "q" || desde == "quit") return make_pair( -2, -2);

    //Este es el comando que ejecuta una jugada aleatoria
    if (desde == "random" || desde == "r" || desde == "rand")
    {
        int idx = rand() % (parent->posiblesMovimientos.size() - 1);
        return parent->posiblesMovimientos.at(this).at(idx);
    }

    //Comando para grabar el juego
    if (desde == "save") return make_pair(-4, -4);

    cin >> hacia;

    if (desde.length() == 2 && hacia.length() == 2)
        return make_pair( Consola::traduceCoordenadas(desde), Consola::traduceCoordenadas(hacia));
    else
        return make_pair(-1, -1);
}

void JugadorLocal::InformarJugada(int desde, int hacia) { }