#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <string>

using namespace std;

class OrdenadorHeapSort {
public:
    // Metodo publico que se debe llamar para ordenar el vector completo.
    void ordenar(vector<string>& datos);

private:
    // Convierte todo el vector en un max-heap valido.
    void construirHeap(vector<string>& datos);

    // Revisa el nodo que está en "indiceRaiz" y, si alguno de sus hijos es mayor que él, los intercambia y sigue bajando (heapify)
    // "tamanoHeap" indica hasta que posicion del vector se considera parte del heap
    void ajustarHeap(vector<string>& datos, int tamanoHeap, int indiceRaiz);
};

#endif
