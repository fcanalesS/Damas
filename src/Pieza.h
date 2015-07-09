#ifndef PROYECTODAMAS_PIEZA_H
#define PROYECTODAMAS_PIEZA_H

#include <vector>
#include "Jugador.h"
#include "JuegoController.h"

class Jugador;
class JuegoController;

class Pieza
{
public:
    //Dueño de la pieza
    Jugador *duenio;
    JuegoController * parent;

    //Constantes para los tipos de piezas del juego
    static const int    TYPE_NONE = 0,
                        TYPE_PEON = 1,
                        TYPE_REY  = 2;

    //Tipo de pieza
    const int tipo;

    Pieza (Jugador *duenio, JuegoController *parent, int posicion, int tipo);
    virtual ~Pieza();

    //Mueve la pieza a otra posición en el tabler
    void moverHacia(int nuevaPosicion);

    //Encuentra todas las posibles jugadas con la pieza
    virtual std::pair<std::vector<int>, std::vector<int>> encuentraTodasLasJugadas() = 0;

protected:
    //Posición de la pieza en el tablero
    int posicion;
};
#endif //PROYECTODAMAS_PIEZA_H
