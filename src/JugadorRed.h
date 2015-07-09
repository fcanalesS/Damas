#ifndef PROYECTODAMAS_JUGADORRED_H
#define PROYECTODAMAS_JUGADORRED_H

#include "Jugador.h"

class JugadorRed : public Jugador
{
public:
    JugadorRed (JuegoController *parent);
    ~JugadorRed();

    //Espera por la jugada del usuario
    std::pair<int, int> EsperarPorEntrada();

    //Espera por la jugada del usuario
    void InformarJugada(int desde, int hacia);

private:
    void parseDataEntrante (std::string & recv, int &desde, int &hacia, int &numtick, int &netgameid);
};

#endif //PROYECTODAMAS_JUGADORRED_H
