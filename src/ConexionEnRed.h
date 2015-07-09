#ifndef PROYECTODAMAS_CONEXIONENRED_H
#define PROYECTODAMAS_CONEXIONENRED_H

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cctype>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

class ConexionEnRed
{
public:
    //Constantes para indicar el tipo de conexión
    static const int    CONEXION_NONE = 0,
                        CONEXION_CLIENTE = 1,
                        CONEXION_SERVIDOR = 2;

    int preparaServerSocket(const char * listenAddr);
    int preparaClienteSocket (const char * listenAddr);

    ConexionEnRed(int tipoConexion, char * address, char * port);
    ConexionEnRed(int tipoConexion, const char * address, const char * port);

    ~ConexionEnRed();

    bool haceConexion();
    bool recibe(std::string & recibido);
    bool enviarMensaje(std::string mensaje);
    void sendHandShake();
    void esperaPorHandShake();
private:
    int tipoConexion;
    int socketnum;
    char * address;
    char * port;

};

#endif //PROYECTODAMAS_CONEXIONENRED_H
