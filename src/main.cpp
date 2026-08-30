// =========================================================================
// Este programa compara tres formas distintas de ordenar un mismo conjunto
// de 100.000 palabras:
//   1. QuickSort sobre un vector dinamico (std::vector).
//   2. HeapSort usando un heap binario (también sobre un vector).
//   3. Insertando las palabras en un Arbol AVL y recorriendolo en in-order.
// =========================================================================

#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <cmath>

#include "utilidades.h"
#include "quicksort.h"
#include "heapsort.h"
#include "arbol_avl.h"

using namespace std;
using namespace std::chrono;

// ---------- Variables globales del programa ----------
vector<string> datasetOriginal;     // El dataset tal cual se leyo del archivo, nunca se modifica.
bool datasetCargado = false;        // Bandera para saber si ya se cargo el dataset.

vector<EstadisticasEjecucion> resultados; // Aqui se van guardando las estadisticas de cada corrida.

// Guardamos tambien el resultado ordenado de cada algoritmo, por si el
// usuario quiere guardarlos en archivos .txt desde el menu.
vector<string> resultadoQuickSort;
vector<string> resultadoHeapSort;
vector<string> resultadoArbolAVL;
bool hayResultadoQuickSort = false;
bool hayResultadoHeapSort = false;
bool hayResultadoArbolAVL = false;

// -------------------------------------------------------------------
// Funciones para estimar la memoria usada por cada estrategia.
// -------------------------------------------------------------------

// Memoria aproximada que ocupa un vector<string> con todas sus palabras.
// Sumamos el tamaño "fijo" del objeto string mas el tamaño del contenido
// de cada palabra
long calcularMemoriaVector(const vector<string>& datos) {
    long memoria = 0;
    for (size_t i = 0; i < datos.size(); i++) {
        memoria += sizeof(string);           // El "cascaron" del objeto string.
        memoria += (long)datos[i].size() + 1; // El contenido de la palabra (+1 del caracter nulo).
    }
    return memoria;
}

// Memoria adicional que gasta la recursion de un algoritmo tipo
// "divide y venceras" (QuickSort, o el heapify recursivo de HeapSort).
// Aproximamos la profundidad maxima de la pila de llamadas como log2(n),
// y le asignamos un tamaño estimado a cada "marco" de la pila (los
// parametros y variables locales que guarda cada llamada recursiva).
long calcularMemoriaRecursion(int n) {
    if (n < 2) return 0;
    double profundidadEstimada = log2((double)n);
    long tamanoAproximadoPorLlamada = 64; // bytes estimados por cada llamada en la pila.
    return (long)(profundidadEstimada * tamanoAproximadoPorLlamada);
}

// Memoria aproximada del Arbol AVL: cada nodo tiene 2 punteros y un
// entero además del string, entonces gasta más memoria por elemento
// que el enfoque de vector.
long calcularMemoriaArbol(int cantidadNodos, const vector<string>& listaOrdenada) {
    long memoria = 0;
    memoria += (long)cantidadNodos * sizeof(NodoAVL); // Cascaron de cada nodo (punteros + altura + string).
    for (size_t i = 0; i < listaOrdenada.size(); i++) {
        memoria += (long)listaOrdenada[i].size() + 1; // Contenido de cada palabra.
    }
    return memoria;
}

// -------------------------------------------------------------------
// Cada una de estas funciones corresponde a una opcion del menu.
// -------------------------------------------------------------------

void ejecutarOpcionQuickSort() {
    if (!datasetCargado) {
        cout << "Primero debes cargar el dataset (opcion 1)." << endl;
        return;
    }

    cout << "Ejecutando QuickSort sobre " << datasetOriginal.size() << " palabras..." << endl;

    // Trabajamos sobre una copia para no modificar datasetOriginal.
    vector<string> copiaDatos = datasetOriginal;

    OrdenadorQuickSort ordenador;

    auto tiempoInicio = high_resolution_clock::now();
    ordenador.ordenar(copiaDatos);
    auto tiempoFin = high_resolution_clock::now();

    double milisegundos = duration<double, std::milli>(tiempoFin - tiempoInicio).count();

    bool quedoBienOrdenado = verificarOrdenAlfabetico(copiaDatos);

    long memoriaVector = calcularMemoriaVector(copiaDatos);
    long memoriaRecursion = calcularMemoriaRecursion((int)copiaDatos.size());

    EstadisticasEjecucion estadistica;
    estadistica.nombreAlgoritmo = "QuickSort";
    estadistica.tiempoEnMilisegundos = milisegundos;
    estadistica.memoriaEnBytes = memoriaVector + memoriaRecursion;
    estadistica.quedoOrdenado = quedoBienOrdenado;
    resultados.push_back(estadistica);

    resultadoQuickSort = copiaDatos;
    hayResultadoQuickSort = true;

    cout << "QuickSort termino en " << milisegundos << " ms. ";
    cout << (quedoBienOrdenado ? "El resultado quedo bien ordenado." : "OJO: el resultado NO quedo ordenado.") << endl;
    mostrarMuestra(copiaDatos, 5);
}

void ejecutarOpcionHeapSort() {
    if (!datasetCargado) {
        cout << "Primero debes cargar el dataset (opcion 1)." << endl;
        return;
    }

    cout << "Ejecutando HeapSort sobre " << datasetOriginal.size() << " palabras..." << endl;

    vector<string> copiaDatos = datasetOriginal;

    OrdenadorHeapSort ordenador;

    auto tiempoInicio = high_resolution_clock::now();
    ordenador.ordenar(copiaDatos);
    auto tiempoFin = high_resolution_clock::now();

    double milisegundos = duration<double, std::milli>(tiempoFin - tiempoInicio).count();

    bool quedoBienOrdenado = verificarOrdenAlfabetico(copiaDatos);

    long memoriaVector = calcularMemoriaVector(copiaDatos);
    // La recursion de ajustarHeap tambien baja como maximo log2(n) niveles.
    long memoriaRecursion = calcularMemoriaRecursion((int)copiaDatos.size());

    EstadisticasEjecucion estadistica;
    estadistica.nombreAlgoritmo = "HeapSort";
    estadistica.tiempoEnMilisegundos = milisegundos;
    estadistica.memoriaEnBytes = memoriaVector + memoriaRecursion;
    estadistica.quedoOrdenado = quedoBienOrdenado;
    resultados.push_back(estadistica);

    resultadoHeapSort = copiaDatos;
    hayResultadoHeapSort = true;

    cout << "HeapSort termino en " << milisegundos << " ms. ";
    cout << (quedoBienOrdenado ? "El resultado quedo bien ordenado." : "OJO: el resultado NO quedo ordenado.") << endl;
    mostrarMuestra(copiaDatos, 5);
}

void ejecutarOpcionArbolAVL() {
    if (!datasetCargado) {
        cout << "Primero debes cargar el dataset (opcion 1)." << endl;
        return;
    }

    cout << "Ejecutando insercion en Arbol AVL con " << datasetOriginal.size() << " palabras..." << endl;
    cout << "(Esta operacion puede tardar un poco mas que las otras dos,";
    cout << " es normal porque cada insercion revisa y balancea el arbol)" << endl;

    ArbolAVL arbol;

    auto tiempoInicio = high_resolution_clock::now();

    // Insertamos cada palabra del dataset original, una por una.
    for (size_t i = 0; i < datasetOriginal.size(); i++) {
        arbol.insertar(datasetOriginal[i]);
    }

    // Una vez insertadas todas, hacemos el recorrido in-order para
    // obtener la lista final ordenada.
    vector<string> resultadoOrdenado = arbol.obtenerListaOrdenada();

    auto tiempoFin = high_resolution_clock::now();

    double milisegundos = duration<double, std::milli>(tiempoFin - tiempoInicio).count();

    bool quedoBienOrdenado = verificarOrdenAlfabetico(resultadoOrdenado);

    int cantidadNodos = arbol.contarNodos();
    long memoriaArbol = calcularMemoriaArbol(cantidadNodos, resultadoOrdenado);

    EstadisticasEjecucion estadistica;
    estadistica.nombreAlgoritmo = "Arbol AVL";
    estadistica.tiempoEnMilisegundos = milisegundos;
    estadistica.memoriaEnBytes = memoriaArbol;
    estadistica.quedoOrdenado = quedoBienOrdenado;
    resultados.push_back(estadistica);

    resultadoArbolAVL = resultadoOrdenado;
    hayResultadoArbolAVL = true;

    cout << "Arbol AVL termino en " << milisegundos << " ms. Nodos insertados: " << cantidadNodos << ". ";
    cout << (quedoBienOrdenado ? "El resultado quedo bien ordenado." : "OJO: el resultado NO quedo ordenado.") << endl;

    if (cantidadNodos != (int)datasetOriginal.size()) {
        cout << "Nota: se insertaron " << cantidadNodos << " nodos de "
             << datasetOriginal.size() << " palabras porque el AVL no permite"
             << " palabras duplicadas (si el dataset tenia repetidas, se ignoraron)." << endl;
    }

    mostrarMuestra(resultadoOrdenado, 5);

    // El destructor de "arbol" se encarga de liberar toda la memoria
    // de los nodos automaticamente cuando la funcion termina.
}

void guardarTodosLosResultados() {
    if (!hayResultadoQuickSort && !hayResultadoHeapSort && !hayResultadoArbolAVL) {
        cout << "Todavia no has ejecutado ningun algoritmo, no hay nada que guardar." << endl;
        return;
    }

    if (hayResultadoQuickSort) {
        guardarResultadoEnArchivo(resultadoQuickSort, "resultados/quicksort_ordenado.txt");
    }
    if (hayResultadoHeapSort) {
        guardarResultadoEnArchivo(resultadoHeapSort, "resultados/heapsort_ordenado.txt");
    }
    if (hayResultadoArbolAVL) {
        guardarResultadoEnArchivo(resultadoArbolAVL, "resultados/avl_ordenado.txt");
    }
}

void mostrarMenu() {
    imprimirSeparador();
    cout << "PRACTICA I - ORDENAMIENTO DE DATASET GRANDE" << endl;
    imprimirSeparador();
    cout << "1. Cargar el dataset (data/dataset.txt)" << endl;
    cout << "2. Ejecutar QuickSort" << endl;
    cout << "3. Ejecutar HeapSort" << endl;
    cout << "4. Ejecutar Arbol AVL" << endl;
    cout << "5. Ver tabla comparativa de resultados" << endl;
    cout << "6. Guardar los resultados ordenados en archivos .txt" << endl;
    cout << "7. Ver una muestra del dataset original (sin ordenar)" << endl;
    cout << "0. Salir" << endl;
    imprimirSeparador();
    cout << "Elige una opcion: ";
}

int main() {
    int opcion = -1;

    cout << "Bienvenido al programa de la Practica I." << endl;
    cout << "Recuerda: primero debes cargar el dataset con la opcion 1." << endl;

    while (opcion != 0) {
        mostrarMenu();
        cin >> opcion;

        // Si el usuario escribe algo que no es un numero, cin queda en
        // un estado de error.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida, por favor escribe un numero." << endl;
            continue;
        }

        switch (opcion) {
            case 1:
                datasetOriginal = leerPalabrasDesdeArchivo("data/dataset.txt");
                datasetCargado = !datasetOriginal.empty();
                break;
            case 2:
                ejecutarOpcionQuickSort();
                break;
            case 3:
                ejecutarOpcionHeapSort();
                break;
            case 4:
                ejecutarOpcionArbolAVL();
                break;
            case 5:
                mostrarTablaComparativa(resultados);
                break;
            case 6:
                guardarTodosLosResultados();
                break;
            case 7:
                if (datasetCargado) {
                    mostrarMuestra(datasetOriginal, 5);
                } else {
                    cout << "Primero debes cargar el dataset (opcion 1)." << endl;
                }
                break;
            case 0:
                cout << "Hasta luego!" << endl;
                break;
            default:
                cout << "Esa opcion no existe, intenta de nuevo." << endl;
        }
    }

    return 0;
}
