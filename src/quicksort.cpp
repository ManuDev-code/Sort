#include "quicksort.h"

void OrdenadorQuickSort::ordenar(vector<string>& datos) {
    // Si el vector esta vacio no hay nada que ordenar.
    if (datos.empty()) {
        return;
    }

    // Llamamos a la funcion recursiva pidiendole que ordene
    // desde la primera posicion (0) hasta la última (size - 1).
    quickSortRecursivo(datos, 0, (int)datos.size() - 1);
}

void OrdenadorQuickSort::quickSortRecursivo(vector<string>& datos, int inicio, int fin) {
    // Caso base: si "inicio" ya no es menor que "fin", significa que
    // el pedazo tiene 0 o 1 elementos, y un pedazo asi ya está ordenado.
    if (inicio >= fin) {
        return;
    }

    // Particionamos el pedazo actual y obtenemos donde quedo el pivote.
    int posicionPivote = particionar(datos, inicio, fin);

    // Ordenamos por separado la parte izquierda del pivote...
    quickSortRecursivo(datos, inicio, posicionPivote - 1);

    // ...y la parte derecha del pivote.
    quickSortRecursivo(datos, posicionPivote + 1, fin);
}

int OrdenadorQuickSort::particionar(vector<string>& datos, int inicio, int fin) {
    // Escogemos como pivote la palabra que esta en la ultima posicion
    // del pedazo que estamos ordenando.
    string pivote = datos[fin];

    // "i" va a marcar el límite hasta donde tenemos, hasta el momento,
    // solamente palabras menores que el pivote. Empieza un puesto antes
    // del inicio porque todavia no hemos encontrado ninguna.
    int i = inicio - 1;

    // Recorremos desde "inicio" hasta un puesto antes del pivote (fin - 1).
    for (int j = inicio; j < fin; j++) {
        // Si la palabra actual es menor que el pivote, la mandamos
        // hacia la zona de "menores" (que esta a la izquierda).
        if (datos[j] < pivote) {
            i++;
            // Intercambiamos datos[i] con datos[j].
            string temporal = datos[i];
            datos[i] = datos[j];
            datos[j] = temporal;
        }
    }

    // Al terminar el for, todo lo que esta entre inicio e i es menor
    // que el pivote. Ahora colocamos el pivote justo despues de esa zona,
    // es decir, en la posicion i + 1.
    string temporal = datos[i + 1];
    datos[i + 1] = datos[fin];
    datos[fin] = temporal;

    // Devolvemos la posicion final del pivote.
    return i + 1;
}
