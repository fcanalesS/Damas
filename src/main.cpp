#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdexcept>

#include "JuegoController.h"
#include "Jugador.h"
#include "Consola.h"
#include "UIRenderer.h"
#include "UIRendererCompatible.h"
#include "UIRendererUnicode.h"
#include "excepciones.h"

#define  SPLASH_SCREEN_T 4

using namespace std;

int main(int argc, char *argv[]) {

    int modojuego = JuegoController::MODE_VSLOC, modorender = 0;
    string loadarchivo = "", networkaddress, networkport, nick = "Jugador 1", nick2 = "Jugador 2";

    JuegoController juegoController;

    //Trata de parsear los comandos recibidos por la consola
    try {
        Consola::parseCmdln(argc, argv, modojuego, modorender, loadarchivo, networkaddress, networkport, nick, nick2);
    }
    catch (ConsolaParseExcepcionesErrores ex) {
        cerr << "Imposible ejecutar." << endl << "Error leyendo los comandos: " << ex.what() << endl;
        return 1;
    }

    //Activa el modo de juego recibido
    juegoController.modoDeJuego = modojuego;

    //Activa el modo de renderizado
    if ( modorender != 2 ) setlocale( LC_ALL, "" );
    if ( modorender == 1 )
        juegoController.renderer = new UIRendererUnicode( &juegoController );
    else if ( modorender == 2 )
        juegoController.renderer = new UIRendererCompatible( &juegoController );
    else
        juegoController.renderer = new UIRenderer( &juegoController );

    //Esto muestra el splash screen (pantalla de bienvenida)
    juegoController.renderer->limpiaPantalla();
    juegoController.renderer->muestraSplashScreen();
    juegoController.delay( SPLASH_SCREEN_T );
    juegoController.renderer->limpiaPantalla();

    //Aquí se crea un juego en red
    if ( modojuego == JuegoController::MODE_VSNET )
    {
        try
        {
            juegoController.preparaJuegoEnRed( networkaddress, networkport, nick, nick2 );
        }
        catch ( ExcepcionCreandoJuegoFallido ex )
        {
            cerr << "Error al crear la partida en red." << endl;
            return 2;
        }
    }

    //Carga un archivo grabado
    else if ( loadarchivo != "" )
    {
        wcout << L"Abriendo archivo '" << wstring( loadarchivo.begin(), loadarchivo.end() ) << L"' ..." << endl;
        ifstream file;
        file.open( loadarchivo );

        if ( file.fail() || ! juegoController.llamarJuego( file ) )
        {
            cerr <<
            "Error cargando el archivo. No tienes los permisos necesarios o el archivo esta corrupto" <<
            endl;
            return 2;
        }
    }

    //Crea un nuevo juego en partida local
    else
    {
        juegoController.preparaNuevoJuego( nick, nick2 );
    }

    wcout << L"Juego listo..." << endl;

    //Redibuja la pantalla
    juegoController.renderer->redibuja();

    while ( ! juegoController.juegoHaTerminado)
    {
        juegoController.tick();
    }

    juegoController.delay( 2 );

    return 0;

}