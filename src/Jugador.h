#ifndef PROYECTODAMAS_JUGADOR_H
#define PROYECTODAMAS_JUGADOR_H

#include <string>
#include "Pieza.h"
#include "JuegoController.h"

class Pieza;
class JuegoController;

using namespace std;

class Jugador
{
public:
    //nombre del jugador
    std::string nombre;
    //color del jugador
    char color;

    Jugador(JuegoController * parent);
    virtual ~Jugador();

    //Espera por la jugada del usuario
    virtual std::pair<int, int> EsperarPorEntrada() = 0;

    virtual void InformarJugada (int desde, int hacia) = 0;

protected:
    JuegoController * parent;
};

#endif //PROYECTODAMAS_JUGADOR_H
