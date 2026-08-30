# Práctica I – Ordenamiento de un Dataset Grande (C++)

**Curso:** ST0245 - SI001 - Estructuras de Datos y Algoritmos
**Universidad:** EAFIT
**Profesor:** Alexander Narváez Berrío

## ¿Qué hace este proyecto?

Este programa ordena un dataset de **100.000 palabras en inglés** usando **tres
algoritmos distintos**, cada uno basado en una estructura de datos diferente,
y compara su tiempo de ejecución y su consumo de memoria:

| Algoritmo | Estructura de datos | Complejidad (Big O) |
|---|---|---|
| QuickSort | `std::vector` (arreglo dinámico) | Promedio O(n log n) / Peor caso O(n²) |
| HeapSort | Heap binario (max-heap sobre un vector) | Siempre O(n log n) |
| Árbol AVL | Árbol binario de búsqueda auto-balanceado | Inserción O(n log n) / Recorrido O(n) |

Los tres algoritmos están implementados **desde cero** (no se usa `std::sort`
ni ninguna librería de ordenamiento).

## Estructura del proyecto

```
Practice_I/
├── data/
│   └── dataset.txt          # 100.000 palabras (una por línea)
├── src/
│   ├── main.cpp              # Menú interactivo del programa
│   ├── utilidades.h/.cpp     # Leer archivo, verificar orden, tabla comparativa
│   ├── quicksort.h/.cpp      # Clase OrdenadorQuickSort
│   ├── heapsort.h/.cpp       # Clase OrdenadorHeapSort
│   └── arbol_avl.h/.cpp      # Clase ArbolAVL (nodo, inserción, rotaciones, in-order)
├── resultados/                # Aquí se guardan los .txt ordenados (opción 6 del menú)
├── Makefile
└── README.md
```

## Cómo compilar y ejecutar

Necesitas tener instalado `g++` con soporte para C++17.

```bash
make            # compila el proyecto (genera bin/programa)
make ejecutar    # compila (si hace falta) y ejecuta el programa
make limpiar     # borra los archivos compilados
```

También puedes compilar manualmente:

```bash
g++ -std=c++17 -O2 -Wall src/*.cpp -o bin/programa
./bin/programa
```

## Cómo se usa (menú)

El programa se maneja con un menú para poder **ejecutar cada algoritmo por
separado**, sin que se afecten entre sí (cada uno trabaja sobre una copia
del dataset original):

```
1. Cargar el dataset (data/dataset.txt)
2. Ejecutar QuickSort
3. Ejecutar HeapSort
4. Ejecutar Arbol AVL
5. Ver tabla comparativa de resultados
6. Guardar los resultados ordenados en archivos .txt
7. Ver una muestra del dataset original (sin ordenar)
0. Salir
```

**Siempre se debe empezar por la opción 1** para cargar el dataset. Después
de eso, las opciones 2, 3 y 4 se pueden ejecutar en cualquier orden y las
veces que se quiera.
