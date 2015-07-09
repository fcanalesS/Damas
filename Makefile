NAME        = DAMAS
CC          = g++
CCFLAGS     = -std=c++0x -Wall -pedantic -Wno-long-long -O0 -ggdb
SOURCES     = AIJugador.cpp Consola.cpp excepciones.cpp JuegoController.cpp PiezaRey.cpp JugadorLocal.cpp PiezaPeon.cpp ConexionEnRed.cpp JugadorRed.cpp Pieza.cpp Jugador.cpp GrabarArchivo.cpp UIRenderer.cpp UIRendererCompatible.cpp UIRendererUnicode.cpp
OBJECTS     = $(SOURCES:.cpp=.o)

all: compile

compile: copysplash $(NAME)
	@echo Compilado correctamente!
	@echo "Ejecutar con ./DAMAS"

$(NAME): $(OBJECTS)
	@echo Linkeando y compilando ejecutable
	@$(CC) $(CCFLAGS) $^ src/main.cpp -o $@

%.o: src/%.cpp
	@echo "Construyendo objeto $< ..."
	@$(CC) $(CCFLAGS) -c $<

copysplash:
	@cp src/checkers-splash.txt ./checkers-splash.txt
	@echo "Copiado splash screen..."

clean:
	@rm -f $(OBJECTS) $(NAME) checkers-splash.txt
	@echo Directorio limpio.

jugar-local:
	@echo "Modo de juego 1 vs 1"
	@sleep 3
	@./DAMAS --versus-local

jugar-AI:
	@echo "Modo de juego 1 vs AI"
	@sleep 3
	@./DAMAS --versus-ai
