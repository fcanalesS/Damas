#include "PiezaPeon.h"

using namespace std;

PiezaPeon::PiezaPeon(Jugador *duenio, JuegoController *parent, int posicion) : Pieza (duenio, parent, posicion, TYPE_PEON)
{

}

PiezaPeon::~PiezaPeon()
{

}

pair<vector<int>, vector<int>> PiezaPeon::encuentraTodasLasJugadas()
{
    char color = duenio->color;
    vector<int> m, j;
    int ydir = parent->tableroRotado ? (color == 'b' ? 1 : -1 ) : (color == 'b' ? -1 : 1);

    //Movimientos a la izquierda
    if ( ! parent->fueraDelTablerRelativo( posicion, -1, ydir ) &&
            parent->getPiezaRelativa( posicion, -1, ydir ) == nullptr )
        m.push_back( posicion - 1 + ydir * 8 );

    //Movimientos a la derecha
    if ( ! parent->fueraDelTablerRelativo( posicion, 1, ydir ) &&
            parent->getPiezaRelativa( posicion, 1, ydir ) == nullptr )
        m.push_back( posicion + 1 + ydir * 8 );

    //Salto a la izquierda
    if ( ! parent->fueraDelTablerRelativo( posicion, -2, ydir * 2 ) )
    {
        Pieza *finpieza = parent->getPiezaRelativa( posicion, -2, ydir * 2 ),
                *medpieza = parent->getPiezaRelativa( posicion, -1, ydir  );

        if ( finpieza == nullptr && medpieza != nullptr && medpieza->duenio->color != color )
            j.push_back( posicion - 2 + ydir * 2 * 8 );
    }

    //Salto a la derecha
    if ( ! parent->fueraDelTablerRelativo( posicion, 2, ydir * 2 ) )
    {
        Pieza *finpieza = parent->getPiezaRelativa( posicion, 2, ydir * 2 ),
                *medpieza = parent->getPiezaRelativa( posicion, 1, ydir );

        if ( finpieza == nullptr && medpieza != nullptr && medpieza->duenio->color != color )
            j.push_back( posicion + 2 + ydir * 2 * 8 );
    }

    //Retorna el set de movimientos y saltos
    return make_pair( m, j );
}