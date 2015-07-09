#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <typeinfo>
#include <algorithm>
#include <fstream>

#include "JuegoController.h"
#include "UIRenderer.h"
#include "excepciones.h"
#include "PiezaPeon.h"
#include "JugadorLocal.h"
#include "AIJugador.h"
#include "ConexionEnRed.h"
#include "JugadorRed.h"
#include "PiezaRey.h"
#include "GrabarArchivo.h"

using namespace std;

int JuegoController::instancias = 0;

JuegoController::JuegoController()
{
    if (++instancias > 1) throw ExcepcionInstanciacion();

    //Inicializa las variables
    modoDeJuego = MODE_NOTSET;
    ticks = 0;
    juegoHaTerminado = false;
    secuenciaDeSalto = false;
    inputInvalido = false;
    tableroRotado= false;
    enTurno = nullptr;
    ganador = nullptr;
    renderer = nullptr;
    primerPlayer = nullptr;
    segundoPlayer = nullptr;
    net = nullptr;
    netGameID = -1;

    // Initialize field
    tablero = new Pieza*[64];
    for ( int i = 0; i < 64; i++ ) tablero[i] = nullptr;
}

JuegoController::~JuegoController()
{
    if ( primerPlayer != nullptr ) delete primerPlayer;
    if ( segundoPlayer != nullptr ) delete segundoPlayer;

    for ( int i = 0; i < 64; i++ )
        if ( tablero[i] != nullptr ) delete tablero[i];
    delete[] tablero;

    if ( modoDeJuego == MODE_VSNET ) delete net;

    if ( renderer != nullptr ) delete renderer;
}

void JuegoController::tick()
{
    bool saltoDisponible = false;

    //Encuentra todas las jugadas posibles y las secuencias de salto disponibles(si hubieren)
    posiblesMovimientos.clear();
    encuentraPosiblesMovimientos(primerPlayer, primerPlayer == enTurno ? &saltoDisponible : nullptr);
    encuentraPosiblesMovimientos(segundoPlayer, segundoPlayer == enTurno ? &saltoDisponible : nullptr);

    //Revisa las condiciones del juego en un instante
    if (numPosiblesMovimientos(primerPlayer) == 0)
    {
        //Puede ser un empate
        if (numPosiblesMovimientos(segundoPlayer) == 0)
        {
            gameOver(nullptr);
            return;
        }

        gameOver(segundoPlayer);
        return;
    }
    else if (numPosiblesMovimientos(segundoPlayer) == 0)
    {
        gameOver(primerPlayer);
        return;
    }

    //Espera por algun movimiento del jugador y revisa si está correcto
    pair<int, int> inputDelTurno = make_pair(INTMAX_MIN, INTMAX_MIN);
    do
    {
        //Si se ingresa un movimiento invalido, se redibuja
        if (inputDelTurno.first != INTMAX_MIN) renderer->redibuja();

        //Se espera por ua jugada o comando
        inputDelTurno = enTurno->EsperarPorEntrada();

        if (inputDelTurno == pair<int,int>(-2, -2))
        {
            if ( dynamic_cast<JugadorLocal*>(enTurno) == nullptr ) wcout << L"El oponente se ha rendido." << endl;
            wcout << L"Saliendo del juego..." << endl;
            juegoHaTerminado = true;
            ( primerPlayer == enTurno ? segundoPlayer : primerPlayer )->InformarJugada( inputDelTurno.first, inputDelTurno.second );
            break;
        }

        if ( inputDelTurno == pair<int,int>( -4, -4 ) )
        {
            wcout << L"Grabando juego..." << endl;
            guardarJuego();
        }

        if ( inputDelTurno == pair<int,int>( -6, -6 ) )
        {
            cerr << "Movimiento fallido, puede haber un error en la conexion.\n"
                    "Saliendo." << endl;
            juegoHaTerminado = true;
            break;
        }

        inputInvalido = true;

    }while(!esTurnoValido(inputDelTurno));

    inputInvalido = false;

    if (juegoHaTerminado) return;

    // Informa al otro jugador del movimiento realizado por el oponente, solo para partidas en red
    ( primerPlayer == enTurno ? segundoPlayer : primerPlayer )->InformarJugada( inputDelTurno.first, inputDelTurno.second );

    //Controla las piezas y las conversiones a reyes de ambos lados del tabler
    getPieza( inputDelTurno.first)->moverHacia( inputDelTurno.second );
    descartaEntreMedio( inputDelTurno.first, inputDelTurno.second );
    convertirHaRey();

    //Detecta secuencia de salto o pasa del turno
    if ( ! ( saltoDisponible && ( secuenciaDeSalto = esSecuenciaDeSalto( ) ) ) ) finDeTurno( );

    ticks++;

    renderer->redibuja( );
}

void JuegoController::delay( int s )
{
    time_t start = time( nullptr );
    while ( time( nullptr ) - s < start )
    { }
}

void JuegoController::preparaNuevoJuego(string nick, string nick2)
{
    wcout << L"Preparando nuevo Juego.";

    juegoHaTerminado = false;

    // Crea Jugadores
    if ( modoDeJuego == MODE_VSLOC )
    {
        primerPlayer= new JugadorLocal( this );
        segundoPlayer = new JugadorLocal( this );
    }
    else if ( modoDeJuego == MODE_VSAI )
    {
        primerPlayer = new JugadorLocal( this );
        segundoPlayer = new AIJugador( this );
    }
    else throw runtime_error( "Modo de juego equivocado" );

    primerPlayer->color = 'b';
    segundoPlayer->color = 'n';

    //Configura los nombres de los jugadores
    primerPlayer->nombre = nick;
    segundoPlayer->nombre = nick2;
    if ( modoDeJuego == MODE_VSAI ) segundoPlayer->nombre = "Jugador AI";

    //Llena el tablero
    llenarTablerConPeones( );

    //Primer turno para el primer jugador
    enTurno = primerPlayer;
}

void JuegoController::preparaJuegoEnRed(string &address, string &port, string nick,
                                        string nick2)
{
    wcout << L"Preparando juego en red..." << endl;

    bool esServer = address == "hostinggame";
    if ( esServer ) address = "0.0.0.0";

    juegoHaTerminado = false;
    tableroRotado = !esServer;

    // Crea la conexión
    ConexionEnRed *net = new ConexionEnRed(
            esServer ? 2 : 1,
            address.c_str(),
            port.c_str()
    );

    this->net = net;

    //Instrucciones para la conexion en red
    if ( esServer ) renderer->dibujaPantallaDeConexion( port );

    //Hace la conexion entre los dos jugadores
    if ( ! net->haceConexion() ) throw ExcepcionCreandoJuegoFallido( "No se pudo crear la conexion" );
    wcout << L"Conexion establecida" << endl;

    // 2x Handshake
    if ( esServer )
    {
        delay( 2 );
        net->sendHandShake();
        net->esperaPorHandShake();
        net->sendHandShake();
        net->esperaPorHandShake();
    }
    else
    {
        net->esperaPorHandShake();
        net->sendHandShake();
        net->esperaPorHandShake();
        net->sendHandShake();
    }
    wcout << L"Conexion exitosa!\nIntercambiando informacion..." << endl;

    //Intercambia informacion entre cliente y servidor
    if ( esServer )
    {
        delay( 1 );

        //Crea al primer jugador
        primerPlayer = new JugadorLocal( this );
        primerPlayer->color = 'b';
        primerPlayer->nombre = nick;

        // Crea la id
        netGameID = rand() % 65535;

        net->enviarMensaje( "b;" + primerPlayer->nombre + ";7;" + to_string( netGameID ) );

        string recibido, rnick; char color; int otraNetGameID;

        // Datos del cliente
        net->recibe( recibido );

        // Parsea la data recibida
        parseRedInitData( recibido, color, rnick, otraNetGameID);

        if ( netGameID != otraNetGameID)
            throw ExcepcionCreandoJuegoFallido( "netGameID invalido" );

        // Crea al segundo jugador
        segundoPlayer = new JugadorRed( this );
        primerPlayer->color = color;
        primerPlayer->nombre = rnick;
    }

    else
    {
        string recibido, rnick;
        char color;

        //Espera la data del servidor
        net->recibe( recibido );

        //Parsea la data recibida
        parseRedInitData( recibido, color, rnick, netGameID );

        primerPlayer = new JugadorRed( this );
        primerPlayer->color = color;
        primerPlayer->nombre = rnick;

        segundoPlayer = new JugadorLocal( this );
        segundoPlayer->color = color == 'b' ? 'n' : 'b';
        segundoPlayer->nombre = nick;

        net->enviarMensaje( string( 1, segundoPlayer->color ) + ";" + segundoPlayer->nombre + ";7;" + to_string( netGameID ) );
    }

    llenarTablerConPeones();

    enTurno = primerPlayer;
}

bool JuegoController::llamarJuego( istream & llamarInfo )
{
    wcout << L"Cargando juego del archivo grabado..." << endl;

    juegoHaTerminado = false;

    return GrabarArchivo::llamar(llamarInfo, this);
}

void JuegoController::gameOver(Jugador *ganador)
{
    this->ganador = ganador;
    juegoHaTerminado = true;

    renderer->dibujaPantallaGameOver();
}

bool JuegoController::esTurnoValido(pair<int, int> turno) const
{
    return find( posiblesMovimientos.at(enTurno).begin(), posiblesMovimientos.at(enTurno).end(), turno) != posiblesMovimientos.at(enTurno).end();
}

void JuegoController::descartaEntreMedio(int desde, int hacia)
{
    int xdir = ( hacia % 8 > desde % 8 ? 1 : -1 ), ydir = ( hacia / 8 > desde / 8 ? 1 : -1 );

    //Va en diagonal pasando por la pieza enemiga
    for ( int x = desde % 8, y = desde / 8; x != hacia % 8 && y != hacia / 8; x += xdir, y += ydir )
    {
        Pieza *pieza = getPieza( x + y * 8 );
        if ( pieza != nullptr && pieza->duenio != enTurno)
        {
            delete pieza;
            setPieza( x + y * 8, nullptr );
        }
    }
}

bool JuegoController::esSecuenciaDeSalto()
{
    bool esSalto = false;

    encuentraPosiblesMovimientos(enTurno, &esSalto);

    return esSalto;
}

void JuegoController::finDeTurno()
{
    enTurno = enTurno == primerPlayer ? segundoPlayer : primerPlayer;
}

Pieza *JuegoController::getPieza(int index) const
{
    return ( index >= 0 && index < 64 ? tablero[ index ] : nullptr );
}

void JuegoController::setPieza(int index, Pieza *pieza)
{
    if ( index >= 0 && index <= 63 )
        this->tablero[ index ] = pieza;
    else
        throw runtime_error("Error, la ficha no existe en el tablero");
}

Pieza *JuegoController::getPiezaRelativa(int desde, int byx, int byy) const
{
    return getPieza( desde + byx + ( byy * 8 ) );
}

int JuegoController::numPosiblesMovimientos(Jugador *jugador) const
{
    return posiblesMovimientos.at(jugador).size();
}

void JuegoController::setPiezaRelativa(int desde, int byx, int byy, Pieza *pieza) const
{
    if ( desde + byx + ( byy * 8 ) > 0 && desde + byx + ( byy * 8 ) < 64 )
        this->tablero[ desde + byx + ( byy * 8 ) ] = pieza;
    else
        throw runtime_error("Error, la ficha no existe en el tablero");
}

void JuegoController::convertirHaRey()
{
    //Parte superior
    for ( int i = 0; i < 7; i++ )
    {
        if ( tablero[ i ] != nullptr )
        if ( tablero[ i ]->duenio == ( tableroRotado ? segundoPlayer : primerPlayer ) && tablero[ i ]->tipo == tablero[ i ]->TYPE_PEON )
        {
            delete tablero[ i ];
            tablero[ i ] = new PiezaRey( ( tableroRotado ? segundoPlayer : primerPlayer ), this, i );
        }
    }

    //Parte inferior
    for ( int i = 56; i < 63; i++ )
    {
        if ( tablero[ i ] != nullptr )
        if ( tablero[ i ]->duenio == ( tableroRotado ? primerPlayer : segundoPlayer ) )
        {
            delete tablero[ i ];
            tablero[ i ] = new PiezaRey( ( tableroRotado ? primerPlayer : segundoPlayer ), this, i );
        }
    }
}

bool JuegoController::fueraDelTablerRelativo(int desde, int byx, int byy) const
{
    return desde + byx + ( byy * 8 ) > 63 || desde + byx + ( byy * 8 ) < 0 ||
            desde + byx < 0 || desde + byx > 63 || (desde + byx) / 8 != desde / 8;
}

void JuegoController::encuentraPosiblesMovimientos(Jugador *jugador, bool *esSalto)
{
    vector<pair<int,int>> movimientos, saltos;

    //Busca sobre el tablero de juego
    for ( int i = 0; i < 64; i++ )
    {
        //Encuentra solo las piezas que pertenecen a tal jugador
        if ( getPieza( i ) != nullptr && getPieza( i )->duenio == jugador )
        {
            //Encuentra todos los movimientos o saltos
            pair< vector<int>, vector<int> > movnsaltos = getPieza( i )->encuentraTodasLasJugadas();

            //los copia
            for ( int m : movnsaltos.first ) movimientos.push_back( make_pair( i, m ) );
            for ( int j : movnsaltos.second ) saltos.push_back( make_pair( i, j ) );
        }
    }

    //Si encuentra secuencias de salto, cancela los movimientos simples
    posiblesMovimientos[ jugador ] = saltos.size() > 0 ? saltos : movimientos;
    if ( esSalto != nullptr ) *esSalto = saltos.size() > 0;
}

void JuegoController::guardarJuego()
{
    //Crea el archivo
    string save = GrabarArchivo::crear( this );
    ofstream file;

    //Abre el archivo
    time_t t; time( &t );
    char buf[128];
    strftime( buf, 128, "save-%Y%m%d%H%M%S.sav", gmtime( &t ) );
    file.open( buf );

    if ( ! file.fail() )
    {
        //Grabala info al archivo
        file << save;
        wcout << endl << L" > Juego guardado como '" << buf << L"'." << endl;
        delay( 3 );
    }
    else
    {
        cerr << "/!\\ ERROR! no tiene permisos de escritura. No se pudo grabar." << endl;
        delay( 5 );
    }

    file.close();
}

void JuegoController::llenarTablerConPeones()
{
    // Llena el tablero con las piezas para el primer player
    for ( int i = 40; i < 64; i += 2 )
    {
        if ( i == 48 ) i++;
        if ( i == 57 ) i--;
        tablero[ tableroRotado ? 63-i : i ] = new PiezaPeon( primerPlayer, this, tableroRotado ? 63-i : i );
        wcout << L"Agregando 1P pieza @ " << (tableroRotado ? 63-i : i) << endl;
    }

    // Llena el tablero con las piezas para el segundo player
    for ( int i = 1; i < 24; i += 2 )
    {
        if ( i == 16 ) i++;
        if ( i == 9 ) i--;
        tablero[ tableroRotado ? 63-i : i ] = new PiezaPeon( segundoPlayer, this, tableroRotado ? 63-i : i );
        wcout << L"Agregando 2P pieza @ " << (tableroRotado ? 63-i : i) << endl;
    }
}

void JuegoController::parseRedInitData(string &recibido, char &color, string &nick, int &netgameid)
{
    stringstream ss;
    ss.str( recibido );

    string colorstr, ngidstr;

    getline( ss, colorstr, ';' );
    getline( ss, nick, ';' );
    getline( ss, ngidstr, ';' );
    getline( ss, ngidstr, ';' );

    color = colorstr[0];
    netgameid = stoi( ngidstr );
}