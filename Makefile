# Makefile de la Practica I
#
# Comandos disponibles:
#   make          -> compila el programa
#   make ejecutar -> compila (si hace falta) y ejecuta el programa
#   make limpiar  -> borra los archivos compilados

COMPILADOR = g++
BANDERAS = -std=c++17 -O2 -Wall
CARPETA_SRC = src
CARPETA_BIN = bin

FUENTES = $(CARPETA_SRC)/main.cpp \
          $(CARPETA_SRC)/utilidades.cpp \
          $(CARPETA_SRC)/quicksort.cpp \
          $(CARPETA_SRC)/heapsort.cpp \
          $(CARPETA_SRC)/arbol_avl.cpp

EJECUTABLE = $(CARPETA_BIN)/programa

$(EJECUTABLE): $(FUENTES)
	mkdir -p $(CARPETA_BIN)
	$(COMPILADOR) $(BANDERAS) $(FUENTES) -o $(EJECUTABLE)

ejecutar: $(EJECUTABLE)
	./$(EJECUTABLE)

limpiar:
	rm -rf $(CARPETA_BIN)

.PHONY: ejecutar limpiar
