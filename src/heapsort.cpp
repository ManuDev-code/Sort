#include "heapsort.h"

void OrdenadorHeapSort::ordenar(vector<string>& datos) {
    int n = (int)datos.size();

    if (n < 2) {
        return; // Con 0 o 1 elementos no hay nada que ordenar.
    }

    // Paso 1: convertimos el vector desordenado en un max-heap.
    construirHeap(datos);

    // Paso 2: vamos sacando la palabra más grande (que siempre está en
    // la posicion 0, la raiz) y la vamos ubicando en su posicion final,
    // desde el final del vector hacia el inicio.
    for (int finHeap = n - 1; finHeap > 0; finHeap--) {
        // Intercambiamos la raiz (la más grande de lo que queda del heap)
        // con el último elemento del pedazo que todavia es heap.
        string temporal = datos[0];
        datos[0] = datos[finHeap];
        datos[finHeap] = temporal;

        // Como cambiamos la raiz, el heap probablemente quedo mal
        // acomodado. Lo arreglamos, pero ahora el heap es un elemento
        // más pequeno (por eso pasamos "finHeap" y no "n").
        ajustarHeap(datos, finHeap, 0);
    }
}

void OrdenadorHeapSort::construirHeap(vector<string>& datos) {
    int n = (int)datos.size();

    // Empezamos desde el último nodo que tiene hijos (o sea el último
    // "padre" del arbol) y vamos hacia atras hasta la raiz, ajustando
    // cada nodo. Los nodos que no tienen hijos (las hojas) ya son,
    // por sí solos, un heap válido, por eso no hace falta revisarlos.
    int ultimoPadre = n / 2 - 1;

    for (int i = ultimoPadre; i >= 0; i--) {
        ajustarHeap(datos, n, i);
    }
}

void OrdenadorHeapSort::ajustarHeap(vector<string>& datos, int tamanoHeap, int indiceRaiz) {
    // Suponemos, de entrada, que el nodo raiz actual es el más grande.
    int indiceMasGrande = indiceRaiz;
    int hijoIzquierdo = 2 * indiceRaiz + 1;
    int hijoDerecho = 2 * indiceRaiz + 2;

    // Si el hijo izquierdo existe (está dentro del heap) y es mayor
    // que lo que tenemos como "el más grande hasta ahora", lo actualizamos.
    if (hijoIzquierdo < tamanoHeap && datos[hijoIzquierdo] > datos[indiceMasGrande]) {
        indiceMasGrande = hijoIzquierdo;
    }

    // Hacemos la misma comparacion con el hijo derecho.
    if (hijoDerecho < tamanoHeap && datos[hijoDerecho] > datos[indiceMasGrande]) {
        indiceMasGrande = hijoDerecho;
    }

    // Si el más grande no es la raiz, quiere decir que la propiedad del
    // heap se estaba rompiendo en este nodo. Hacemos el intercambio...
    if (indiceMasGrande != indiceRaiz) {
        string temporal = datos[indiceRaiz];
        datos[indiceRaiz] = datos[indiceMasGrande];
        datos[indiceMasGrande] = temporal;

        // Seguimos bajando por el arbol, porque al mover ese
        // elemento hacia abajo puede que se rompa el heap más abajo.
        ajustarHeap(datos, tamanoHeap, indiceMasGrande);
    }
}
