#include "excepciones.h"

using namespace std;

ConsolaParseExcepcionesErrores::ConsolaParseExcepcionesErrores(const string &razon) : runtime_error( razon ) { }
const char* ExcepcionInstanciacion::what() const throw() { return "Error de iniciacion."; }
ExcepcionCreandoJuegoFallido::ExcepcionCreandoJuegoFallido(const string &razon) : runtime_error( razon ) { }
