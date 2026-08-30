#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <string>

using namespace std;

class OrdenadorQuickSort {
public:
    // Metodo público que se debe llamar para ordenar el vector completo.
    // Ordena "datos" de menor a mayor (orden alfabetico), modificandolo
    // directamente (por eso se recibe por referencia con &).
    void ordenar(vector<string>& datos);

private:
    // Funcion recursiva que ordena solo el pedazo del vector que va
    // desde la posicion "inicio" hasta la posicion "fin" (ambas incluidas).
    void quickSortRecursivo(vector<string>& datos, int inicio, int fin);

    // Particiona el pedazo [inicio, fin] usando como pivote el elemento
    // que está en la posicion "fin". Devuelve la posicion final en la
    // que quedo ubicado el pivote una vez terminada la particion.
    int particionar(vector<string>& datos, int inicio, int fin);
};

#endif
