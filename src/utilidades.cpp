#include "utilidades.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

vector<string> leerPalabrasDesdeArchivo(const string& nombreArchivo) {
    vector<string> palabras;

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "ERROR: no se pudo abrir el archivo " << nombreArchivo << endl;
        // Devolvemos el vector vacio para que el programa no se caiga,
        // el que llama a esta funcion debe revisar si quedo vacio.
        return palabras;
    }

    // reserve() no es obligatorio, pero como sabemos que vamos a leer
    // muchas palabras (100.000), le avisamos al vector el tamano
    // aproximado para que no tenga que ir creciendo de a poquitos.
    palabras.reserve(100000);

    string palabraActual;
    while (getline(archivo, palabraActual)) {
        // Por si el archivo tiene una linea vacia al final, la ignoramos.
        if (!palabraActual.empty()) {
            palabras.push_back(palabraActual);
        }
    }

    archivo.close();

    cout << "Se leyeron " << palabras.size() << " palabras desde " << nombreArchivo << endl;

    return palabras;
}

bool verificarOrdenAlfabetico(const vector<string>& datos) {
    // Si el vector tiene 0 o 1 elementos, ya esta "ordenado" por definicion.
    if (datos.size() < 2) {
        return true;
    }

    for (size_t i = 0; i < datos.size() - 1; i++) {
        if (datos[i] > datos[i + 1]) {
            // Aqui encontramos dos palabras que estan en el orden incorrecto.
            cout << "Desorden encontrado en la posicion " << i
                 << ": \"" << datos[i] << "\" deberia ir despues de \""
                 << datos[i + 1] << "\"" << endl;
            return false;
        }
    }

    return true;
}

void mostrarMuestra(const vector<string>& datos, int cantidad) {
    if (datos.empty()) {
        cout << "(el vector esta vacio)" << endl;
        return;
    }

    cout << "Primeras " << cantidad << " palabras:" << endl;
    for (int i = 0; i < cantidad && i < (int)datos.size(); i++) {
        cout << "  " << i + 1 << ". " << datos[i] << endl;
    }

    cout << "Ultimas " << cantidad << " palabras:" << endl;
    int total = (int)datos.size();
    for (int i = total - cantidad; i < total; i++) {
        if (i >= 0) {
            cout << "  " << i + 1 << ". " << datos[i] << endl;
        }
    }
}

void guardarResultadoEnArchivo(const vector<string>& datos, const string& nombreArchivo) {
    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida.is_open()) {
        cout << "ERROR: no se pudo crear el archivo " << nombreArchivo << endl;
        return;
    }

    for (size_t i = 0; i < datos.size(); i++) {
        archivoSalida << datos[i] << "\n";
    }

    archivoSalida.close();
    cout << "Resultado guardado en " << nombreArchivo << endl;
}

void imprimirSeparador() {
    cout << "----------------------------------------------------------------" << endl;
}

void mostrarTablaComparativa(const vector<EstadisticasEjecucion>& resultados) {
    if (resultados.empty()) {
        cout << "Todavia no se ha ejecutado ningun algoritmo. Ejecuta primero" << endl;
        cout << "las opciones 2, 3 y 4 del menu para poder comparar." << endl;
        return;
    }

    imprimirSeparador();
    cout << "TABLA COMPARATIVA DE RESULTADOS" << endl;
    imprimirSeparador();

    cout << left << setw(18) << "Algoritmo"
         << setw(18) << "Tiempo (ms)"
         << setw(20) << "Memoria aprox (KB)"
         << setw(12) << "Ordenado?" << endl;

    for (size_t i = 0; i < resultados.size(); i++) {
        const EstadisticasEjecucion& r = resultados[i];
        cout << left << setw(18) << r.nombreAlgoritmo
             << setw(18) << fixed << setprecision(2) << r.tiempoEnMilisegundos
             << setw(20) << fixed << setprecision(2) << (r.memoriaEnBytes / 1024.0)
             << setw(12) << (r.quedoOrdenado ? "Si" : "NO")
             << endl;
    }

    imprimirSeparador();
    cout << "Complejidad teorica (Big O) de cada algoritmo:" << endl;
    cout << "  QuickSort (sobre vector) -> Promedio: O(n log n)  |  Peor caso: O(n^2)" << endl;
    cout << "  HeapSort (heap binario)  -> Siempre:  O(n log n)" << endl;
    cout << "  Arbol AVL + recorrido    -> Insertar: O(n log n) | Recorrido: O(n)" << endl;
    imprimirSeparador();
}
