#include "UIRendererUnicode.h"

using namespace std;

UIRendererUnicode::UIRendererUnicode(JuegoController *parent) :
    UIRenderer (
            parent,
            L'\u26C2', // peon blanco
            L'\u26C0', // peon negro
            L'\u26C3', // rey blanco
            L'\u26C1', // rey negro
            'E',       // ninguna pieza seleccionada o para marcar un error
            L'\u2591', // separador extenro
            L'\u2591', // separador interno
            L'\u25F7', // en espera
            L'\u25BB', // prompt
            L'\u26CC', // entrada invalida
            L'\u2503', // separador del infobox
            L'\u26C4'  // usericoncon
    ){ }

UIRendererUnicode::~UIRendererUnicode() { }