#include <fstream>

#include "UIRenderer.h"
#include "JuegoController.h"
#include "Consola.h"
#include "JugadorLocal.h"

using namespace std;

#define MARGEN_IZQ      6
#define DEBUG           true

UIRenderer::UIRenderer(JuegoController *parent, charType bpeon, charType npeon, charType brey,
                       charType nrey, charType nonepza, charType exseparador, charType inseparador,
                       charType espera, charType prompt, charType inputinvalido,
                       charType infoseparador, charType usericon)

    :                   BPEON_CHAR ( bpeon ),
                        NPEON_CHAR (npeon),
                        BREY_CHAR (brey),
                        NREY_CHAR (nrey),
                        NONE_PZA_CHAR (nonepza),
                        EX_SEPARADOR_CHAR (exseparador),
                        IN_SEPARADOR_CHAR (inseparador),
                        ESPERA_CHAR (espera),
                        PROMPT_CHAR (prompt),
                        INPUT_INVALIDO_CHAR (inputinvalido),
                        INFO_SEPARADOR_CHAR (infoseparador),
                        USERICON_CHAR(usericon),
                        parent(parent)
{
    initLineasLogo();
}

UIRenderer::UIRenderer(JuegoController *parent) :   BPEON_CHAR ('b'),
                                                    NPEON_CHAR ('n'),
                                                    BREY_CHAR ('B'),
                                                    NREY_CHAR ('N'),
                                                    NONE_PZA_CHAR ('!'),
                                                    EX_SEPARADOR_CHAR (L'\u2591'),
                                                    IN_SEPARADOR_CHAR (L'\u2591'),
                                                    ESPERA_CHAR ('.'),
                                                    PROMPT_CHAR ('>'),
                                                    INPUT_INVALIDO_CHAR ('!'),
                                                    INFO_SEPARADOR_CHAR ('|'),
                                                    USERICON_CHAR ('-'),
                                                    parent(parent)
{
    initLineasLogo();
    wcout << L"Cargado el rederizado" << endl;
}

UIRenderer::~UIRenderer() { delete[] lineasLogo; }

void UIRenderer::initLineasLogo() {
    //Dibuja el logo en la pantalla

    lineasLogo = new wstring[6]{
            L"__________________________________________",
            L"    _____    __     _   _    __       __  ",
            L"    /    )   / |    /  /|    / |    /    )",
            L"---/----/---/__|---/| /-|---/__|----\\-----",
            L"  /    /   /   |  / |/  |  /   |     \\    ",
            L"_/____/___/____|_/__/___|_/____|_(____/___",
    };
}

void UIRenderer::redibuja() const
{
    //Limpia la pantalla
    limpiaPantalla();

    //Dibuja la cabecera
    dibujaCabecera();

    //Agrega un espacio
    wcout << endl << endl;

    //Dibuja el tablero
    dibujaTablero();

    if (DEBUG)
    {
        wcout << endl << endl << wstring (MARGEN_IZQ, ' ') << L"=== Posibles movimientos: " <<wstring (27, '-') << endl;
        for (pair<int, int> m : parent->posiblesMovimientos[parent->enTurno])
            wcout << Consola::traduceCoordenadasW(m.first) << L"->" << Consola::traduceCoordenadasW(m.second) << L". ";
    }

    //Instrucciones para poder jugar
    if (parent->ticks < 1)
    {
        wcout << endl << endl << wstring (MARGEN_IZQ, ' ') << L"=== Como jugar: " << wstring(27, '-') << endl
        << wstring(MARGEN_IZQ, ' ') << "El formato de entrada es 'XX XX', donde XX corresponde a A0 - H8. Escriba q para salir";
    }

    //Aqui va el prompt donde se ingresa el movimiento
    wcout << endl << endl << wstring (MARGEN_IZQ, ' ');
    if (dynamic_cast<JugadorLocal*>(parent->enTurno) != nullptr) wcout << L"=== Su turno: "; else wcout << L"=== Espere por el otro jugador";
    wcout << wstring (32, '-')
        << endl << wstring (MARGEN_IZQ -1, ' ') << (parent->inputInvalido ? INPUT_INVALIDO_CHAR : L' ')
        << L' ' << PROMPT_CHAR << L' ';
}

void UIRenderer::dibujaCabecera() const
{
    for ( int i = 0; i < 6; i++ ) {
        wcout << wstring(MARGEN_IZQ, ' ');
        dibujaLineasLogo(i);

        wstring modo = L"Contra 2P";
        if (parent->modoDeJuego == JuegoController::MODE_VSAI) modo = L"1P VS AI";
        if (parent->modoDeJuego == JuegoController::MODE_VSNET) modo = L"2P VS NET";

        if ( i == 3 || i == 5 ) wcout << wstring( 4, ' ' ) << INFO_SEPARADOR_CHAR;
        if ( i == 4 ) wcout << wstring( 4, ' ' ) << INFO_SEPARADOR_CHAR << L"  " << modo;

        wcout << endl;
    }
}

void UIRenderer::dibujaLineasLogo(int linea) const
{
    if ( linea >= 0 && linea < 6 )
        wcout << lineasLogo[ linea ];
}

void UIRenderer::limpiaPantalla() const
{
    wcout << wstring( 60, '\n' );
}

void UIRenderer::muestraSplashScreen() const
{
    fstream splashscreen;
    splashscreen.open("checkers-splash.txt");
    string linea;

    if (!splashscreen.fail())
    {
        while(!splashscreen.eof())
        {
            getline(splashscreen, linea);
            wcout << endl << wstring(linea.begin(), linea.end());
        }
    }
}

void UIRenderer::dibujaTablero() const
{
    wcout << wstring(MARGEN_IZQ + 2, ' ');
    for ( int i = 0; i < 8; i++ )
    {
        wcout << " " << (wchar_t)( 65 + i ) << " ";
    } wcout << endl;

    for ( int i = 0; i < 8; i++ )
    {
        wcout << wstring( MARGEN_IZQ, ' '  ) << i+1 << L" ";
        dibujaLineasTablero( i );
        wcout << wstring( 5, ' ' );
        dibujaLineasInfo( i );
        wcout << endl;
    }
}

void UIRenderer::dibujaLineasTablero(int linea) const
{
    for ( int i = linea * 8; i < linea * 8 + 8; i++ )
    {
        Pieza * pieza = parent->getPieza(i);

        if ( linea % 2 == 0 ? i % 2 == 0 : i % 2 != 0 )
            wcout << EX_SEPARADOR_CHAR << IN_SEPARADOR_CHAR<< EX_SEPARADOR_CHAR;

        else
        if ( pieza == nullptr )
            wcout << L"   ";
        else
        {
            charType piezaChar = NONE_PZA_CHAR;

            if ( pieza->duenio->color == 'n' )
                piezaChar = (pieza->tipo == pieza->TYPE_REY? NREY_CHAR : NPEON_CHAR);
            else if ( pieza->duenio->color == 'b' )
                piezaChar = (pieza->tipo == pieza->TYPE_REY ? BREY_CHAR : BPEON_CHAR);

            wcout << " " << piezaChar << " ";
        }

    }
}

void UIRenderer::dibujaLineasInfo(int linea) const
{
    wcout << INFO_SEPARADOR_CHAR << ' ';

    if ( linea == 1 ) wcout << wstring(parent->enTurno->nombre.begin(), parent->enTurno->nombre.end() ) << L" en turno.";
    if ( linea == 3 ) wcout << (wchar_t)( parent->enTurno == parent->primerPlayer ? ESPERA_CHAR : ' ' ) << ' ' <<
                     USERICON_CHAR << L"   " << wstring( parent->primerPlayer->nombre.begin(), parent->primerPlayer->nombre.end() );
    if ( linea == 4 ) wcout << L"       vs ";
    if ( linea == 5 ) wcout << (wchar_t)( parent->enTurno == parent->segundoPlayer ? ESPERA_CHAR : ' ' ) << ' ' <<
                     USERICON_CHAR << L"   " << wstring( parent->segundoPlayer->nombre.begin(), parent->segundoPlayer->nombre.end() );
}

void UIRenderer::dibujaPantallaGameOver() const
{
    //Limpia la pantalla
    limpiaPantalla();
    //Dibuja la cabecera
    dibujaCabecera();
    wcout << endl << endl;

    //Escribe el resultado
    if (parent->ganador == nullptr)
    {
        //Entonces es un empate
        wcout << "Empate!!!";
    }
    else
        wcout << wstring(parent->ganador->nombre.begin(), parent->ganador->nombre.end()) << L" Ganador!" << endl;
}

void UIRenderer::dibujaPantallaDeConexion(std::string port) const
{
    wcout << endl <<
    wstring( 6, ' ' ) << L"/" << endl;
    wcout << wstring( 6, ' ' ) << L"|" << wstring( 3, ' ' ) << L"Esperando para que el cliente se conecte..." << endl;
    wcout << wstring( 6, ' ' ) << L"|" << wstring( 3, ' ' ) << L"" << endl;
    wcout << wstring( 6, ' ' ) << L"|" << wstring( 3, ' ' ) << L"Para ejecutar como cliente usar:" << endl;
    wcout << wstring( 6, ' ' ) << L"|" << wstring( 7, ' ' ) << L"./checkers --versus-network --ip [suIP] --port " << wstring( port.begin(), port.end() ) << endl;
    wcout << wstring( 6, ' ' ) << L"\\" << endl << endl;
}