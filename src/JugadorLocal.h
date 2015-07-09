#ifndef PROYECTODAMAS_JUGADORLOCAL_H
#define PROYECTODAMAS_JUGADORLOCAL_H

#include "Jugador.h"

class JugadorLocal : public Jugador
{
public:
    JugadorLocal (JuegoController *parent);
    ~JugadorLocal();

    //Espera por la jugada del usuario
    std::pair<int, int> EsperarPorEntrada();

    //Espera por la jugada del usuario
    void InformarJugada(int desde, int hacia);
};

#endif //PROYECTODAMAS_JUGADORLOCAL_H
