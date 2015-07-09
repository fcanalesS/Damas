#include <iostream>
#include <queue>
#include <string>

#include "Consola.h"
#include "JuegoController.h"
#include "excepciones.h"

using namespace std;

void Consola::parseCmdln(int argc, char *argv[], int &modoJuego, int &modoRender, string &llamararchivo,
                         string &networkaddress, string &networkport, string &nick, string &nick2)
{
    bool modoJuegoSet = false, modoRenderSet = false, archivoCargado = false;
    string ip = "0.0.0.0", port = "0";

    //Mueve los comandos ingresados a una cola, menos el primero
    queue<string> comandosParsed;
    for (int i=1; i<argc; i++)
        comandosParsed.push(string(argv[i]));

    while(!comandosParsed.empty())
    {
        string comando = getSigteComando(comandosParsed);

        //Comando --versus-local
        if (comando == "--versus-local")
        {
            if (modoJuegoSet) throw ConsolaParseExcepcionesErrores ("Error al configurar el modo de juego");
            else if (archivoCargado) throw ConsolaParseExcepcionesErrores("No se puede configurar un modo de juego, cuando se esta cargando un archivo");
            else
            {
                modoJuego = JuegoController::MODE_VSLOC;
                modoJuegoSet = true;
            }
        }

        //Comando --versus-ai
        else if (comando == "--versus-ai")
        {
            if (modoJuegoSet) throw ConsolaParseExcepcionesErrores ("Error al configurar el modo de juego");
            else if (archivoCargado) throw ConsolaParseExcepcionesErrores("No se puede configurar un modo de juego, cuando se esta cargando un archivo");
            else
            {
                modoJuego = JuegoController::MODE_VSAI;
                modoJuegoSet = true;
            }
        }

        else if (comando == "--versus-network")
        {
            if (modoJuegoSet) throw ConsolaParseExcepcionesErrores ("Error al configurar el modo de juego");
            else if (archivoCargado) throw ConsolaParseExcepcionesErrores("No se puede configurar un modo de juego, cuando se esta cargando un archivo");
            else
            {
                modoJuego = JuegoController::MODE_VSNET;
                modoJuegoSet = true;
            }
        }

        else if (comando == "--load")
        {
            if ( modoJuegoSet ) throw ConsolaParseExcepcionesErrores( "Error al cargar el archivo" );
            else
            {
                llamararchivo = getSigteComando( comandosParsed);
                archivoCargado = true;

                if ( llamararchivo == "" ) throw ConsolaParseExcepcionesErrores( "Se debe especificar un nombre" );
            }
        }
        else if (comando == "--unicode")
        {
            if (modoRenderSet) throw ConsolaParseExcepcionesErrores("Error al configurar el renderizado del juego");
            else
            {
                modoRender = 1;
                modoRenderSet = true;
            }
        }

        else if  (comando == "--compatible")
        {
            if (modoRenderSet) throw ConsolaParseExcepcionesErrores("Error al configurar el renderizado del juego");
            else
            {
                modoRender = 2;
                modoRenderSet = true;
            }
        }

        else if (comando == "--host")
        {
            if (modoJuegoSet && modoJuego == JuegoController::MODE_VSNET)
                ip = "Hosteando Juego";
            else
                throw ConsolaParseExcepcionesErrores("El modo de juego tiene que ser '--versus-network' para configurar la ip");
        }

        else if (comando == "--ip")
        {
            if (modoJuegoSet && modoJuego == JuegoController::MODE_VSNET)
            {
                ip = getSigteComando(comandosParsed);
                if (ip == "")
                    throw ConsolaParseExcepcionesErrores("Se debe configurar la ip para este modo de juego");
            }
            else
                throw ConsolaParseExcepcionesErrores("El modo de juego tiene que ser '--versus-network' para configurar la ip");
        }

        else if (comando == "--port")
        {
            if (modoJuegoSet && modoJuego == JuegoController::MODE_VSNET)
            {
                port = getSigteComando(comandosParsed);
                if (port == "")
                    throw ConsolaParseExcepcionesErrores("Se debe configurar un puerto de red para este modo");
            }
            else
                throw ConsolaParseExcepcionesErrores("El modo de juego tiene que ser '--versus-network' para configurar la ip");
        }

        else if (comando == "--nick")
        {
            nick = getSigteComando(comandosParsed);
            if (nick == "") throw ConsolaParseExcepcionesErrores("Debe especificar un nickname valido");
        }

        else if (comando == "--nick2")
        {
            nick2 = getSigteComando(comandosParsed);
            if (nick2 == "") throw ConsolaParseExcepcionesErrores("Debe especificar un nickname valido");
        }
        else
            throw ConsolaParseExcepcionesErrores("El comando '" + comando + "' no es valido");
    }

    if (modoJuegoSet && modoJuego == JuegoController::MODE_VSNET && ( ip == "0.0.0.0" || ip == "" || port == "0" ))
        throw ConsolaParseExcepcionesErrores("Se debe configurar una direccion ip y puerto de red validos para jugar en red");

    networkaddress = ip;
    networkport = port;
}

string Consola::getSigteComando(queue<string> &comandos)
{
    if (!comandos.empty())
    {
        string comando = comandos.front();
        comandos.pop();
        return comando;
    }
    else
        return "";
}

int Consola::traduceCoordenadas(string posicion)
{
    int col = -1, row = -1;

    if (posicion[0] >= 65 && posicion[0] <= 72) col = posicion[0] - 65;
    if (posicion[0] >= 97 && posicion[0] <= 104) col = posicion[0] - 97;
    if (posicion[1] >= 49 && posicion[1] <= 54) row = posicion[1] - 49;

    return (col == -1 || row == -1 ? -1 : row * 8 + col);
}

wstring Consola::traduceCoordenadasW(int posicion)
{
    stringstream ss;
    int col = posicion %8, row = posicion/8;
    ss << (char)(65+col) << (row+1);
    string resultado = ss.str();
    return wstring(resultado.begin(), resultado.end());
}