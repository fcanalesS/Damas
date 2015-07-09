#include <sstream>
#include <ctime>
#include <stdlib.h>
#include <typeinfo>

#include "GrabarArchivo.h"
#include "JugadorLocal.h"
#include "AIJugador.h"
#include "PiezaRey.h"
#include "PiezaPeon.h"
#include "AIJugador.h"

using namespace std;

#define GRABARJUEGO_VERSION 7
#define SPR ';'

string GrabarArchivo::crear(JuegoController *juegoController)
{
    stringstream ss;

    ss << "_DAMAS_VER" << GRABARJUEGO_VERSION << "SAVEGAMEFILE";

    ss << endl << time(0);

    ss << endl << typeid( juegoController ).name() << SPR << 31 << SPR << 31
    << SPR << juegoController->modoDeJuego << SPR << juegoController->ticks
    << SPR << ( juegoController->secuenciaDeSalto ? 1 : 0 )
    << SPR << ( juegoController->enTurno == juegoController->segundoPlayer ? 2 : 1 );

    //Tablero de juego
    ss << endl << typeid( Pieza ).name();
    for ( int i = 0; i < 64; i++ )
    {
        if ( juegoController->getPieza( i ) == nullptr )
        {
            ss << SPR << 0 << SPR << 0;
        }
        else
        {
            ss << SPR << ( juegoController->getPieza( i )->duenio == juegoController->segundoPlayer ? 2 : 1 )
            << SPR << juegoController->getPieza( i )->tipo;
        }
    }

    //Determina el tipo de jugador
    int p1type = 0, p2type = 0;
    if ( dynamic_cast< JugadorLocal* >( juegoController->primerPlayer ) != nullptr )   p1type = 1;
    else if ( dynamic_cast< AIJugador* >( juegoController->primerPlayer ) != nullptr ) p1type = 2;
    if ( dynamic_cast< JugadorLocal* >( juegoController->segundoPlayer ) != nullptr )   p2type = 1;
    else if ( dynamic_cast< AIJugador* >( juegoController->segundoPlayer ) != nullptr ) p2type = 2;

    //Jugador 1
    ss << endl << typeid( juegoController->primerPlayer ).name() << SPR << juegoController->primerPlayer->color
    << SPR << juegoController->primerPlayer->nombre << SPR << p1type;

    //Jugador 2
    ss << endl << typeid( juegoController->segundoPlayer ).name() << SPR << juegoController->primerPlayer->color
    << SPR << juegoController->segundoPlayer->nombre << SPR << p2type;

    return ss.str();
}

bool GrabarArchivo::llamar(std::istream &infoGrabada, JuegoController *juegoController)
{
    string head, timestamp, gameVars, field, player1, player2;

    while ( ! infoGrabada.eof() )
    {
        getline( infoGrabada, head );
        getline( infoGrabada, timestamp );
        getline( infoGrabada, gameVars );
        getline( infoGrabada, field );
        getline( infoGrabada, player1 );
        getline( infoGrabada, player2 );
    }

    //Revisa si el archivo no está corrupto
    if ( head.length() > 30 || field.length() < 96 ) return false;

    vector<string> params;

    // Crea al primer player
    params.clear();
    parseParams( player1, params );
    if ( params.size() != 4 ) return false;
    if ( params[ 3 ] == "1" )
        juegoController->primerPlayer = new JugadorLocal( juegoController );
    else if ( params[ 3 ] == "2" )
        juegoController->primerPlayer = new AIJugador( juegoController );
    else return false;
    juegoController->primerPlayer->color = params[ 1 ][ 0 ];
    juegoController->primerPlayer->nombre = params[ 2 ];

    // Crea al segundo player
    params.clear();
    parseParams( player2, params );
    if ( params.size() != 4 ) return false;
    if ( params[ 3 ] == "1" )
        juegoController->segundoPlayer = new JugadorLocal( juegoController );
    else if ( params[ 3 ] == "2" )
        juegoController->segundoPlayer = new AIJugador( juegoController );
    else return false;
    juegoController->segundoPlayer->color = params[ 1 ][ 0 ];
    juegoController->segundoPlayer->nombre = params[ 2 ];

    //Carga las variables en la variabler juegoController
    params.clear();
    parseParams( gameVars, params );
    if ( params.size() != 7 || params[ 2 ] != "31" ) return false;
    juegoController->modoDeJuego = atoi( params[ 3 ].c_str() );
    juegoController->ticks = atoi( params[ 4 ].c_str() );
    juegoController->secuenciaDeSalto = params[ 5 ] == "1";
    juegoController->enTurno = params[ 6 ] == "2" ? juegoController->segundoPlayer : juegoController->primerPlayer;

    //Llena el tablero
    params.clear();
    parseParams( field, params );
    if ( params.size() != 129 ) return false;
    for ( int i = 1; i < 129; i += 2 )
    {
        if ( params[ i ] != "0" )
        {
            Jugador *duenio = params[ i ] == "2" ? juegoController->segundoPlayer : juegoController->primerPlayer;

            if ( params[ i + 1 ] == "2" )
                juegoController->setPieza( i / 2, new PiezaRey( duenio, juegoController, i / 2 ) );
            else
                juegoController->setPieza( i / 2, new PiezaPeon( duenio, juegoController, i / 2 ) );
        }
    }
    return true;
}

void GrabarArchivo::parseParams(string paramString, vector<string> &params)
{
    stringstream ss;
    ss.str( paramString );

    while ( ! ss.eof() )
    {
        string param;
        getline( ss, param, SPR );
        params.push_back( param );
    }
}