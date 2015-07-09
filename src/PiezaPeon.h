#ifndef PROYECTODAMAS_PIEZAPEON_H
#define PROYECTODAMAS_PIEZAPEON_H

#include "Pieza.h"

class PiezaPeon : public Pieza
{
public:
    PiezaPeon (Jugador *duenio, JuegoController *parent, int posicion);
    ~PiezaPeon();

    std::pair<std::vector<int>, std::vector<int>> encuentraTodasLasJugadas();
};

#endif //PROYECTODAMAS_PIEZAPEON_H
