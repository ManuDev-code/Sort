#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <vector>
#include <string>

using namespace std;

// -----------------------------------------------------------------------
// Esta estructura guarda los datos que nos interesan de cada algoritmo
// despues de ejecutarlo: cuanto tiempo tardo, cuanta memoria aproximada
// uso y si el resultado quedo bien ordenado o no.
// La usamos al final del programa para armar la tabla comparativa.
// -----------------------------------------------------------------------
struct EstadisticasEjecucion {
    string nombreAlgoritmo;
    double tiempoEnMilisegundos;
    long memoriaEnBytes;
    bool quedoOrdenado;
};

// Lee el archivo de palabras (una palabra por linea) y las guarda en un vector.
// Si el archivo no se puede abrir, devuelve un vector vacio y avisa por consola.
vector<string> leerPalabrasDesdeArchivo(const string& nombreArchivo);

// Recorre el vector de palabras y revisa que cada palabra sea menor o igual
// (en orden alfabetico) que la siguiente. Si encuentra un desorden devuelve false.
bool verificarOrdenAlfabetico(const vector<string>& datos);

// Imprime las primeras "cantidad" palabras y las ultimas "cantidad" palabras
// del vector. Sirve para revisar rapidamente en consola que el orden se ve bien,
// sin tener que imprimir las 100.000 palabras completas.
void mostrarMuestra(const vector<string>& datos, int cantidad);

// Guarda el vector de palabras ya ordenado en un archivo de texto,
// una palabra por linea. Sirve como evidencia para la sustentacion.
void guardarResultadoEnArchivo(const vector<string>& datos, const string& nombreArchivo);

// Imprime en consola una linea separadora, solo para que la salida
// del programa se vea mas ordenada y sea mas facil de leer.
void imprimirSeparador();

// Recibe todas las estadisticas que se han ido guardando durante la
// ejecucion del programa y las muestra en forma de tabla comparativa,
// junto con la complejidad Big O teorica de cada algoritmo.
void mostrarTablaComparativa(const vector<EstadisticasEjecucion>& resultados);

#endif
