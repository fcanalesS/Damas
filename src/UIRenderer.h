#ifndef PROYECTODAMAS_UIRENDERER_H
#define PROYECTODAMAS_UIRENDERER_H

#include <string>

#include "JuegoController.h"

typedef wchar_t charType;

class JuegoController;

class UIRenderer
{
public:
    //Char para el Peón blanco
    const charType BPEON_CHAR;
    //Char para el Peón negro
    const charType NPEON_CHAR;
    //Char para el Rey blanco
    const charType BREY_CHAR;
    //Char para el Eey negro
    const charType NREY_CHAR;
    //Char para ninguna pieza
    const charType NONE_PZA_CHAR;
    //Char para el separador del tablero
    const charType EX_SEPARADOR_CHAR;
    //Char para el seaparador del tablero
    const charType IN_SEPARADOR_CHAR;
    //Char para el caracter en espera
    const charType ESPERA_CHAR;
    //Char para el prompt
    const charType PROMPT_CHAR;
    //Char para un caracter inválido
    const charType INPUT_INVALIDO_CHAR;
    //Char para separar la información
    const charType INFO_SEPARADOR_CHAR;
    //Char para el icono de usuario
    const charType USERICON_CHAR;

    UIRenderer (JuegoController *parent, charType bpeon, charType npeon, charType brey,
                charType nrey, charType nonepza, charType exseparador, charType inseparador,
                charType espera, charType prompt, charType inputinvalido, charType infoseparador, charType usericon);

    UIRenderer (JuegoController *parent);

    virtual ~UIRenderer();

    //Redibuja la pantalla
    void redibuja() const;

    //Limpia la pantalla
    void limpiaPantalla() const;

    //Muestra la splashScreen
    void muestraSplashScreen() const;

    //Muestra la pantalla de gameOver
    void dibujaPantallaGameOver() const;

    //Dibuja la pantalla de espera para las partidas en red, con las instrucciones pertinentes
    void dibujaPantallaDeConexion( std::string port) const;

    //Dibuja una cabecera
    virtual void dibujaCabecera() const;

    //Dibuja el tablero de juego
    virtual void dibujaTablero() const;

protected:
    JuegoController *parent;

    //Declarativa para las lineas del logo
    std::wstring * lineasLogo;

    //Dibuja las lineas del logo
    void dibujaLineasLogo(int linea) const;

    //Dibuja las lineas del tablero
    virtual void dibujaLineasTablero (int linea ) const;

    //Dibuja las lineas de la info
    virtual void dibujaLineasInfo(int linea) const;

    void initLineasLogo();
};

#endif //PROYECTODAMAS_UIRENDERER_H
