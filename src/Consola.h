#ifndef PROYECTODAMAS_CONSOLA_H
#define PROYECTODAMAS_CONSOLA_H

#include <iostream>
#include <queue>
#include <sstream>

class Consola
{
public:
    static void parseCmdln( int argc, char *argv[], int &modoJuego, int &modoRender, std::string &llamararchivo,
                            std::string &networkaddress, std::string & networkport, std::string & nick, std::string & nick2 );

    //Obtiene el siguiente comando de la "cola de comandos"
    static std::string getSigteComando (std::queue<std::string> &comandos);

    //Traduce las coordenadas a formato string
    static int traduceCoordenadas(std::string posicion);

    //Traduce las coordenadas a formato wchar
    static std::wstring traduceCoordenadasW(int posicion);
};

#endif //PROYECTODAMAS_CONSOLA_H
