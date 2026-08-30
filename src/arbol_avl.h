#ifndef ARBOL_AVL_H
#define ARBOL_AVL_H

#include <vector>
#include <string>

using namespace std;

// -----------------------------------------------------------------------
// Estructura NodoAVL
//
// Cada nodo del arbol guarda una palabra, un puntero a su hijo izquierdo,
// un puntero a su hijo derecho, y su "altura" (que es la cantidad de
// niveles que hay desde ese nodo hasta la hoja mas lejana de su rama).
// Guardamos la altura en cada nodo para no tener que recalcularla
// recorriendo el arbol cada vez que la necesitamos: eso es lo que hace
// que las operaciones del AVL sean rapidas.
// -----------------------------------------------------------------------
struct NodoAVL {
    string palabra;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    // Constructor: cuando se crea un nodo nuevo, todavia no tiene hijos
    // (por eso izquierdo y derecho se inicializan en nullptr) y su
    // altura es 1 porque el mismo cuenta como un nivel.
    NodoAVL(const string& p) : palabra(p), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

// -----------------------------------------------------------------------
// Clase ArbolAVL
//
// Un AVL es un arbol binario de busqueda que se "auto-balancea": cada
// vez que insertamos una palabra, el arbol revisa si alguna rama quedo
// mucho mas alta que la otra y, si eso pasa, hace una "rotacion" para
// volver a dejarlo balanceado. Gracias a eso, el arbol nunca se vuelve
// una fila larga hacia un solo lado (lo que si le puede pasar a un
// arbol binario de busqueda normal), y las operaciones se mantienen
// en O(log n) en vez de degradarse a O(n).
//
// Para saber si un nodo esta balanceado usamos el "factor de balance":
//   factorDeBalance = altura(hijoIzquierdo) - altura(hijoDerecho)
// Si ese numero queda entre -1 y 1, el nodo esta balanceado.
// Si queda en 2 o en -2, hay que rotar.
// -----------------------------------------------------------------------
class ArbolAVL {
public:
    ArbolAVL();

    // El destructor libera toda la memoria de los nodos que se crearon
    // con "new", para que el programa no deje memoria "regada" (leaks).
    ~ArbolAVL();

    // Inserta una palabra nueva en el arbol, balanceando si hace falta.
    void insertar(const string& palabra);

    // Recorre el arbol "in-order" (izquierda, raiz, derecha), que en un
    // arbol binario de busqueda siempre entrega los elementos ordenados
    // de menor a mayor, y devuelve el resultado en un vector.
    vector<string> obtenerListaOrdenada();

    // Cuenta cuantos nodos tiene el arbol en total. Lo usamos despues
    // para estimar cuanta memoria esta usando el arbol.
    int contarNodos();

private:
    NodoAVL* raiz;

    // --- Funciones auxiliares, todas recursivas ---

    NodoAVL* insertarRecursivo(NodoAVL* nodo, const string& palabra);

    // Libera recursivamente toda la memoria del subarbol que cuelga de "nodo".
    void liberarMemoria(NodoAVL* nodo);

    // Devuelve la altura de un nodo. Si el nodo es nullptr, la altura es 0.
    int obtenerAltura(NodoAVL* nodo);

    // factorDeBalance = altura(izquierdo) - altura(derecho)
    int obtenerFactorBalance(NodoAVL* nodo);

    // Actualiza el campo "altura" de un nodo a partir de la altura de sus hijos.
    void actualizarAltura(NodoAVL* nodo);

    // Las 2 rotaciones basicas del AVL. Las otras 2 combinaciones
    // (izquierda-derecha y derecha-izquierda) se arman combinando estas dos.
    NodoAVL* rotarDerecha(NodoAVL* nodo);
    NodoAVL* rotarIzquierda(NodoAVL* nodo);

    void recorridoInOrdenRecursivo(NodoAVL* nodo, vector<string>& resultado);

    void contarNodosRecursivo(NodoAVL* nodo, int& contador);
};

#endif
