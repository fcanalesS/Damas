#ifndef PROYECTODAMAS_GRABARARCHIVO_H
#define PROYECTODAMAS_GRABARARCHIVO_H

#include "JuegoController.h"

class GrabarArchivo
{
public:
    //Crea un nuevo archivo de grabado
    static std::string crear(JuegoController * juegoController);

    //Llama a un archivo previamente grabado
    static bool llamar(std::istream & infoGrabada, JuegoController * juegoController);

private:
    //Rescata los parametros de un archivo de grabado del juego
    static void parseParams (std::string paramString, std::vector<std::string> & params);
};

#endif //PROYECTODAMAS_GRABARARCHIVO_H
