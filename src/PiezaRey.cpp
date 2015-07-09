#include "PiezaRey.h"

using namespace std;

PiezaRey::PiezaRey(Jugador *duenio, JuegoController *parent, int posicion) :
    Pieza(duenio, parent, posicion, TYPE_REY)
{

}

PiezaRey::~PiezaRey()
{

}

pair <vector<int>, vector<int>> PiezaRey::encuentraTodasLasJugadas()
{
    pair< vector<int>, vector<int> > mnsaltos;

    //Movimientos izquierda arriba
    pair<vector<int>, vector<int>> encuentra = busquedaDiagonal( -1, -1 );
    for ( int j : encuentra.first ) mnsaltos.first.push_back( j );
    for ( int j : encuentra.second ) mnsaltos.second.push_back( j );

    //Movimientos derecha arriba
    encuentra = busquedaDiagonal( 1, -1 );
    for ( int j : encuentra.first ) mnsaltos.first.push_back( j );
    for ( int j : encuentra.second ) mnsaltos.second.push_back( j );

    //Movimientos izquierda abajo
    encuentra = busquedaDiagonal( -1, 1 );
    for ( int j : encuentra.first ) mnsaltos.first.push_back( j );
    for ( int j : encuentra.second ) mnsaltos.second.push_back( j );

    //Movimientos derecha abajo
    encuentra = busquedaDiagonal( 1, 1 );
    for ( int j : encuentra.first ) mnsaltos.first.push_back( j );
    for ( int j : encuentra.second ) mnsaltos.second.push_back( j );

    return mnsaltos;
}

pair<vector<int>, vector<int>> PiezaRey::busquedaDiagonal(int dirx, int diry)
{
    char color = duenio->color;
    vector<int> m, j;
    int x = 0, y = 0;
    bool saltandosobre = false;

    while ( ! parent->fueraDelTablerRelativo( posicion, x, y ) )
    {
        if ( x == 0 && y == 0 ) { x += dirx; y += diry; continue; }
        Pieza *pieza = parent->getPiezaRelativa( posicion, x, y );

        if ( pieza != nullptr )
        {

            //Permite el salto sobre alguna pieza enemiga
            if ( pieza->duenio->color != color )
            {
                if ( saltandosobre ) break;
                saltandosobre = true;
            }

                //Impide saltar sobre las piezas propias
            else
                break;
        }
        else
        {
            //Permite el movimiento o salto sobre una casilla vacia
            if ( saltandosobre )
            {
                j.push_back( posicion + x + y*8 );
                //Pero solo una vez
                break;
            }
            else
                m.push_back( posicion + x + y*8 );

            saltandosobre = false;
        }

        x += dirx; y += diry;
    }

    return make_pair( m, j );
}