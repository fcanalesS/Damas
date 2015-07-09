#ifndef PROYECTODAMAS_AIJUGADOR_H
#define PROYECTODAMAS_AIJUGADOR_H

#include "Jugador.h"

/**
 * Jugador con "Inteligencia" artificial
 */

class AIJugador : public Jugador
{
public:
    AIJugador(JuegoController * parent);
    ~AIJugador();

    /**
     * Espera por la jugada del usuario.
     * Retornando una jugada por su cuenta "inteligentemente".
     * Elijiendo aleatoriamente de todos los posibles movimientos
     */
    pair<int, int> EsperarPorEntrada( );

    /**
     * Informa al jugador de las jugadas del contrario,
     * esta función solo se usa un partidas de red.
     */

    void InformarJugada (int desde, int hacia);
};

#endif //PROYECTODAMAS_AIJUGADOR_H
