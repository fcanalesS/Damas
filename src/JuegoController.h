#ifndef PROYECTODAMAS_JUEGOCONTROLLER_H
#define PROYECTODAMAS_JUEGOCONTROLLER_H

#include "UIRenderer.h"
#include "Pieza.h"
#include "ConexionEnRed.h"

#include <map>
#include <iostream>

class UIRenderer;
class Pieza;
class Jugador;

//Clase que orquesta el juego en sí, se encarga de toda la lógica
class JuegoController
{
public:
    //Constantes para los modos de juego
    static const int    MODE_NOTSET = -1, //Cuando no se ocupa ningun modo de juego
                        MODE_VSLOC  = 0, //Versus un jugador local
                        MODE_VSAI   = 1, //Versus la "inteligencia" artificial
                        MODE_VSNET  = 2; //Versus un jugador configurado en red

    //Número de instancias
    static int instancias;

    //Modo de juego
    int modoDeJuego;

    //Tiempos transcurridos
    int ticks;

    //Indica si el juego terminó
    bool juegoHaTerminado;

    //Indica si hay una secuencia de salto
    bool secuenciaDeSalto;

    //Indica si los datos ingresados son inválidos
    bool inputInvalido;

    //Indica si el tabler es rotado
    bool tableroRotado;

    //Jugador en turno
    Jugador * enTurno;

    //Ganador del juego
    Jugador * ganador;

    //Modo de renderizado
    UIRenderer * renderer;

    //Todas los posibles movimientos de ambos jugadores
    std::map<Jugador*, std::vector<std::pair<int,int>>> posiblesMovimientos;

    //Primer Player
    Jugador * primerPlayer;

    //Segundo Player
    Jugador * segundoPlayer;

    //Conexion en red
    ConexionEnRed * net;

    //Game ID
    int netGameID;

    JuegoController();

    ~JuegoController();

    //Juego en local
    void preparaNuevoJuego(std::string nick, std::string nick2);

    //Funcion para llamar un previamente guardado
    bool llamarJuego (std::istream & llamarInfo);

    //Prepara un juego en red
    void preparaJuegoEnRed (std::string & address, std::string & port, std::string nick, std::string nick2 );

    /**
     * Este método revisa quién ganó, pone en espera para recibir datos del usuario,
     * manipula el tablero y re-dibuja la pantalla
     */
    void tick();

    void delay(int s);

    Pieza *getPieza(int index) const;
    void setPieza (int index, Pieza * pieza);

    Pieza *getPiezaRelativa (int desde, int byx, int byy) const;
    void setPiezaRelativa (int desde, int byx, int byy, Pieza * pieza) const;

    //Obtiene la cantidad de posibles movimientos de un jugador
    int numPosiblesMovimientos(Jugador *jugador) const;

    //Revisa si la posición, está o no fuera del tabler
    bool fueraDelTablerRelativo (int desde, int byx, int byy) const;

    //Encuentra todas los posibles movimientos de un jugador
    void encuentraPosiblesMovimientos(Jugador *jugador, bool *esSalto = nullptr);

private:
    //Pregunta si el turno es válido
    bool esTurnoValido(std::pair<int, int> turno) const;

    //Descarta las piezas de entremedio, para las diagonales
    void descartaEntreMedio(int desde, int hacia);

    //Pregunta si es una secuencia de salto
    bool esSecuenciaDeSalto();

    //Finaliza el turno
    void finDeTurno();

    //Convierte los peones en Rey
    void convertirHaRey();

    //Termina el juego
    void gameOver(Jugador * ganador);

    //Graba la partida en un archivo
    void guardarJuego();

    //Llena el tablero con los peones
    void llenarTablerConPeones();

    //Recibe los datos para la inicialización de las partidas en red
    void parseRedInitData(std::string & recibido, char & color, std::string & nick, int & netgameid);

    //Tablero
    Pieza ** tablero;
};

#endif //PROYECTODAMAS_JUEGOCONTROLLER_H
