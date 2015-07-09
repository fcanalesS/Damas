#include "UIRendererCompatible.h"

using namespace std;

UIRendererCompatible::~UIRendererCompatible() { }

UIRendererCompatible::UIRendererCompatible(JuegoController *parent) :
    UIRenderer(
            parent,
            'b', // peon blanco
            'n', // peon negro
            'B', // rey blanco
            'n', // rey negro
            '!', // ninguna pieza seleccionada o para marcar un error
            '#', // separador extenro
            '#', // separador interno
            '.', // en espera
            '>', // prompt
            '!', // entrada invalida
            '|', // separador del infobox
            '-' // usericon
    ) { }