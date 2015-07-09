#include <chrono>

#include "ConexionEnRed.h"

using namespace std;

ConexionEnRed::ConexionEnRed(int tipoConexion, char *address, char *port) :
    tipoConexion(tipoConexion), address(address), port(port)
{
    tipoConexion = CONEXION_NONE;
    socketnum = -1;
}

ConexionEnRed::ConexionEnRed(int tipoConexion, const char *address, const char *port) : tipoConexion (tipoConexion)
{
    this->address = (char *) address;
    this->port = (char *) port;
}

bool ConexionEnRed::haceConexion()
{
    if (tipoConexion == CONEXION_SERVIDOR) {
        int listensock = preparaServerSocket(address);

        if (listensock == -1) {
            cerr << "No se pudo crear la conexion. Error #" << errno << endl;
            return false;
        }

        struct sockaddr addr;
        socklen_t addrLen = sizeof(addrLen);

        cout << "Esperando por la conexion del cliente..." << endl;

        if ((socketnum = accept(listensock, &addr, &addrLen)) == -1) {
            cerr << "Conexion con el cliente fallida!" << errno;
            return false;
        }

        return true;
    }
    else
    {
        socketnum = preparaClienteSocket(address);

        if (socketnum == -1) {
            cerr << "No se pudo crear la conexion. Error #" << errno << endl;
            return false;
        }

        return true;
    }
}

int ConexionEnRed::preparaServerSocket(const char *listenAddr)
{
    struct addrinfo * ai;

    if ( getaddrinfo ( listenAddr, port, NULL, &ai ) != 0 ) return -1;

    int sock = socket ( ai->ai_family, SOCK_STREAM, 0 );

    if ( sock == -1 )
    {
        freeaddrinfo ( ai );
        return -1;
    }

    if ( bind ( sock, ai->ai_addr, ai->ai_addrlen ) != 0 )
    {
        close ( sock );
        freeaddrinfo ( ai );
        return -1;
    }

    if ( listen ( sock, 10 ) != 0 )
    {
        close ( sock );
        freeaddrinfo ( ai );
        return -1;
    }
    freeaddrinfo ( ai );
    return sock;
}

int ConexionEnRed::preparaClienteSocket(const char *listenAddr)
{
    struct addrinfo * ai;

    if ( getaddrinfo ( listenAddr, port, NULL, &ai ) != 0 ) return -1;

    int sock = socket ( ai->ai_family, SOCK_STREAM, 0 );
    if ( sock == -1 )
    {
        freeaddrinfo ( ai );
        return -1;
    }

    if ( connect ( sock, ai->ai_addr, ai->ai_addrlen ) != 0 )
    {
        close ( sock );
        freeaddrinfo ( ai );
        return -1;
    }
    freeaddrinfo ( ai );
    return sock;
}

bool ConexionEnRed::recibe(string &recibido)
{
    char buffer[256];

    int len = recv( socketnum, buffer, sizeof( buffer ) - 1, 0);

    if ( len <= 0 ) return false;

    buffer[ len ] = '\0';
    recibido = string( buffer );

    return true;
}

bool ConexionEnRed::enviarMensaje(string mensaje)
{
    return send( socketnum, mensaje.c_str(), strlen( mensaje.c_str() ), 0 ) != 1;
}

void ConexionEnRed::sendHandShake()
{
    if ( ! enviarMensaje( "CHECKERS_HANDSHAKE" ) ) cerr << errno << endl;
}

void ConexionEnRed::esperaPorHandShake()
{
    string recibido;

    while ( recibido != "CHECKERS_HANDSHAKE" )
    {
        recibe( recibido );
    }
}

ConexionEnRed::~ConexionEnRed() { close(socketnum); }