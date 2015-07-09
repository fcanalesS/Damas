#ifndef PROYECTODAMAS_PIEZAREY_H
#define PROYECTODAMAS_PIEZAREY_H

#include "Pieza.h"

class PiezaRey : public Pieza
{
public:
    PiezaRey (Jugador *duenio, JuegoController *parent, int posicion);
    ~PiezaRey();

    //Encuentra todos los posibles movimientos con esta pieza
    std::pair<std::vector<int>, std::vector<int>> encuentraTodasLasJugadas();

    //Realiza una búsqueda en diagonal y retorna los posibles movimientos que pueden hacerse
    std::pair<std::vector<int>, std::vector<int>> busquedaDiagonal(int dirx, int diry);
};

#endif //PROYECTODAMAS_PIEZAREY_H
