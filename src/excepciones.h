#ifndef PROYECTODAMAS_EXCEPCIONES_H
#define PROYECTODAMAS_EXCEPCIONES_H

#include <stdexcept>

//Errores con los comandos en la consola
class ConsolaParseExcepcionesErrores : public std::runtime_error
{
public:
    ConsolaParseExcepcionesErrores (const std::string &razon);
};

//Errores de instaciones
class ExcepcionInstanciacion : public std::exception
{
public:
    virtual const char* what() const throw();
};

class ExcepcionCreandoJuegoFallido : public std::runtime_error
{
public:
    ExcepcionCreandoJuegoFallido( const std::string &razon );
};


#endif //PROYECTODAMAS_EXCEPCIONES_H
