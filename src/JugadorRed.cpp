#include <sstream>

#include "JugadorRed.h"

using namespace std;

JugadorRed::JugadorRed(JuegoController *parent) : Jugador(parent)
{

}

JugadorRed::~JugadorRed()
{

}

pair<int, int> JugadorRed::EsperarPorEntrada()
{
    string receivedInput;
    int desde, hacia, ticks, netgameid;

    //Recibe input de la red
    parent->net->recibe( receivedInput );

    //Parsea la data entrante
    parseDataEntrante( receivedInput, desde, hacia, ticks, netgameid );

    //Revisa si el netgameid es correcto
    if ( netgameid != parent->netGameID )
        return make_pair( -6, -6 );

    //Revisa si hay datos sincronizados
    if ( ticks != parent->ticks )
        return make_pair( -6, -6 );

    return desde > 0 && hacia > 0 ? make_pair( 63 - desde, 63 - hacia ) : make_pair( desde, hacia );
}

void JugadorRed::parseDataEntrante(string &recv, int &desde, int &hacia, int &numtick, int &netgameid)
{
    stringstream ss;
    string fromstr, tostr, tickstr, ngstr;

    ss.str( recv );

    getline( ss, fromstr, ';' );
    getline( ss, tostr, ';' );
    getline( ss, tickstr, ';' );
    getline( ss, ngstr, ';' );

    desde = stoi( fromstr );
    hacia = stoi( tostr );
    numtick = stoi( tickstr );
    netgameid = stoi( ngstr );
}

void JugadorRed::InformarJugada(int desde, int hacia)
{
    parent->net->enviarMensaje( to_string( desde ) + ";" + to_string( hacia ) + ";" +
                              to_string( parent->ticks ) + ";" + to_string( parent->netGameID ) );
}