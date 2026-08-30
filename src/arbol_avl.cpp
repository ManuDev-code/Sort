#include "arbol_avl.h"

ArbolAVL::ArbolAVL() {
    raiz = nullptr;
}

ArbolAVL::~ArbolAVL() {
    liberarMemoria(raiz);
}

void ArbolAVL::liberarMemoria(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }
    liberarMemoria(nodo->izquierdo);
    liberarMemoria(nodo->derecho);
    delete nodo;
}

int ArbolAVL::obtenerAltura(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->altura;
}

int ArbolAVL::obtenerFactorBalance(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
}

void ArbolAVL::actualizarAltura(NodoAVL* nodo) {
    int alturaIzquierda = obtenerAltura(nodo->izquierdo);
    int alturaDerecha = obtenerAltura(nodo->derecho);

    // La altura del nodo es 1 (por el mismo) mas la altura de su rama
    // mas alta entre la izquierda y la derecha.
    if (alturaIzquierda > alturaDerecha) {
        nodo->altura = alturaIzquierda + 1;
    } else {
        nodo->altura = alturaDerecha + 1;
    }
}

NodoAVL* ArbolAVL::rotarDerecha(NodoAVL* nodo) {
    // Rotacion derecha: el hijo izquierdo "sube" y se vuelve la nueva
    // raiz de este pedazo del arbol. Se usa cuando la rama izquierda
    // esta demasiado cargada (factor de balance = 2).
    //
    //         nodo                    nuevaRaiz
    //         /                       /       (der)
    //   nuevaRaiz        ----->   hijoB       nodo
    //     /    (der)                          /
    //  hijoA  hijoB                        hijoA
    //
    NodoAVL* nuevaRaiz = nodo->izquierdo;
    NodoAVL* hijoB = nuevaRaiz->derecho;

    // Hacemos el giro:
    nuevaRaiz->derecho = nodo;
    nodo->izquierdo = hijoB;

    // Como las relaciones cambiaron, hay que recalcular las alturas.
    // Ojo con el orden: primero "nodo" (que ahora quedo mas abajo)
    // y despues "nuevaRaiz" (que depende de la altura de "nodo").
    actualizarAltura(nodo);
    actualizarAltura(nuevaRaiz);

    return nuevaRaiz;
}

NodoAVL* ArbolAVL::rotarIzquierda(NodoAVL* nodo) {
    // Rotacion izquierda: es la operacion simetrica a la anterior.
    // Se usa cuando la rama derecha esta demasiado cargada
    // (factor de balance = -2).
    NodoAVL* nuevaRaiz = nodo->derecho;
    NodoAVL* hijoB = nuevaRaiz->izquierdo;

    nuevaRaiz->izquierdo = nodo;
    nodo->derecho = hijoB;

    actualizarAltura(nodo);
    actualizarAltura(nuevaRaiz);

    return nuevaRaiz;
}

void ArbolAVL::insertar(const string& palabra) {
    raiz = insertarRecursivo(raiz, palabra);
}

NodoAVL* ArbolAVL::insertarRecursivo(NodoAVL* nodo, const string& palabra) {
    // Caso base: si llegamos a un espacio vacio, aqui es donde va
    // la palabra nueva. Creamos el nodo y lo devolvemos.
    if (nodo == nullptr) {
        return new NodoAVL(palabra);
    }

    // Si la palabra es menor, va en la rama izquierda; si es mayor,
    // va en la rama derecha (es un arbol binario de busqueda normal
    // en este paso). Si la palabra ya existe en el arbol, la ignoramos
    // (no insertamos duplicados) para no dejar el dataset con repetidos.
    if (palabra < nodo->palabra) {
        nodo->izquierdo = insertarRecursivo(nodo->izquierdo, palabra);
    } else if (palabra > nodo->palabra) {
        nodo->derecho = insertarRecursivo(nodo->derecho, palabra);
    } else {
        return nodo; // palabra duplicada, no se hace nada.
    }

    // Ya insertamos la palabra en algun lugar de este subarbol,
    // asi que primero actualizamos la altura de este nodo...
    actualizarAltura(nodo);

    // ...y ahora revisamos si con esa insercion el nodo quedo
    // desbalanceado, para corregirlo con una rotacion si hace falta.
    int balance = obtenerFactorBalance(nodo);

    // Caso izquierda-izquierda: la rama izquierda esta muy cargada
    // y el desbalance viene del hijo izquierdo del hijo izquierdo.
    if (balance > 1 && palabra < nodo->izquierdo->palabra) {
        return rotarDerecha(nodo);
    }

    // Caso derecha-derecha: es el caso simetrico al anterior.
    if (balance < -1 && palabra > nodo->derecho->palabra) {
        return rotarIzquierda(nodo);
    }

    // Caso izquierda-derecha: la rama izquierda esta cargada, pero el
    // desbalance en realidad viene del hijo DERECHO del hijo izquierdo.
    // Primero enderezamos esa rama con una rotacion izquierda...
    if (balance > 1 && palabra > nodo->izquierdo->palabra) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo); // ...y despues rotamos el nodo actual.
    }

    // Caso derecha-izquierda: caso simetrico al anterior.
    if (balance < -1 && palabra < nodo->derecho->palabra) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    // Si no caimos en ninguno de los 4 casos anteriores, el nodo
    // ya esta balanceado y no hay que hacer ninguna rotacion.
    return nodo;
}

vector<string> ArbolAVL::obtenerListaOrdenada() {
    vector<string> resultado;
    resultado.reserve(contarNodos());
    recorridoInOrdenRecursivo(raiz, resultado);
    return resultado;
}

void ArbolAVL::recorridoInOrdenRecursivo(NodoAVL* nodo, vector<string>& resultado) {
    if (nodo == nullptr) {
        return;
    }

    // Primero visitamos todo el subarbol izquierdo (palabras menores)...
    recorridoInOrdenRecursivo(nodo->izquierdo, resultado);

    // ...despues agregamos la palabra de este nodo...
    resultado.push_back(nodo->palabra);

    // ...y por ultimo visitamos todo el subarbol derecho (palabras mayores).
    // Como en un arbol binario de busqueda todo lo de la izquierda es
    // menor y todo lo de la derecha es mayor, este recorrido entrega
    // las palabras ya ordenadas alfabeticamente.
    recorridoInOrdenRecursivo(nodo->derecho, resultado);
}

int ArbolAVL::contarNodos() {
    int contador = 0;
    contarNodosRecursivo(raiz, contador);
    return contador;
}

void ArbolAVL::contarNodosRecursivo(NodoAVL* nodo, int& contador) {
    if (nodo == nullptr) {
        return;
    }
    contador++;
    contarNodosRecursivo(nodo->izquierdo, contador);
    contarNodosRecursivo(nodo->derecho, contador);
}
