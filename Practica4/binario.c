#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// estructura de un nodo del arbol
struct Nodo {
    int dato;
    struct Nodo* izquierdo;
    struct Nodo* derecho;
};

// funcion para crear un nuevo nodo
struct Nodo* crearNodo(int dato) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->izquierdo = NULL;
    nuevoNodo->derecho = NULL;
    return nuevoNodo;
}

// funcion para insertar un nodo en el arbol
void insertar(struct Nodo** arbol, int dato) {
    if (*arbol == NULL) {
        *arbol = crearNodo(dato);
        return;
    }
    if (dato > (*arbol)->dato) {
        insertar(&((*arbol)->derecho), dato);
    } else {
        insertar(&((*arbol)->izquierdo), dato);
    }
}

// funcion para buscar un nodo específico en el arbol
struct Nodo* buscar(struct Nodo* arbol, int dato) {
    if (arbol == NULL || arbol->dato == dato) {
        return arbol;
    }
    if (dato > arbol->dato) {
        return buscar(arbol->derecho, dato);
    } else {
        return buscar(arbol->izquierdo, dato);
    }
}

// funcion para encontrar el nodo con el valor minimo en un subarbol
struct Nodo* encontrarMin(struct Nodo* arbol) {
    while (arbol->izquierdo != NULL) {
        arbol = arbol->izquierdo;
    }
    return arbol;
}

// funcion para eliminar un nodo específico del arbol
struct Nodo* eliminarNodo(struct Nodo* arbol, int dato) {
    if (arbol == NULL) {
        return arbol;
    }
    if (dato < arbol->dato) {
        arbol->izquierdo = eliminarNodo(arbol->izquierdo, dato);
    } else if (dato > arbol->dato) {
        arbol->derecho = eliminarNodo(arbol->derecho, dato);
    } else {
        if (arbol->izquierdo == NULL) {
            struct Nodo* temp = arbol->derecho;
            free(arbol);
            return temp;
        } else if (arbol->derecho == NULL) {
            struct Nodo* temp = arbol->izquierdo;
            free(arbol);
            return temp;
        }
        struct Nodo* temp = encontrarMin(arbol->derecho);
        arbol->dato = temp->dato;
        arbol->derecho = eliminarNodo(arbol->derecho, temp->dato);
    }
    return arbol;
}

// funcion para realizar un recorrido en preorden
void preorden(struct Nodo* arbol) {
    if (arbol != NULL) {
        printf("%d ", arbol->dato);
        preorden(arbol->izquierdo);
        preorden(arbol->derecho);
    }
}

// funcion para realizar un recorrido en inorden
void inorden(struct Nodo* arbol) {
    if (arbol != NULL) {
        inorden(arbol->izquierdo);
        printf("%d ", arbol->dato);
        inorden(arbol->derecho);
    }
}

// funcion para realizar un recorrido en postorden
void postorden(struct Nodo* arbol) {
    if (arbol != NULL) {
        postorden(arbol->izquierdo);
        postorden(arbol->derecho);
        printf("%d ", arbol->dato);
    }
}

// funcion para contar el numero de nodos en el arbol
int contarNodos(struct Nodo* arbol) {
    if (arbol == NULL) {
        return 0;
    }
    return 1 + contarNodos(arbol->izquierdo) + contarNodos(arbol->derecho);
}

// funcion para calcular la profundidad del arbol
int profundidad(struct Nodo* arbol) {
    if (arbol == NULL) {
        return 0;
    }
    int profIzq = profundidad(arbol->izquierdo);
    int profDer = profundidad(arbol->derecho);
    return (profIzq > profDer ? profIzq : profDer) + 1;
}

// funcion para verificar si el arbol es completo
int esCompleto(struct Nodo* arbol, int indice, int numNodos) {
    if (arbol == NULL) {
        return 1;
    }
    if (indice >= numNodos) {
        return 0;
    }
    return esCompleto(arbol->izquierdo, 2 * indice + 1, numNodos) &&
           esCompleto(arbol->derecho, 2 * indice + 2, numNodos);
}

// funcion para verificar si el arbol esta balanceado
int esBalanceado(struct Nodo* arbol) {
    if (arbol == NULL) {
        return 1;
    }
    int profIzq = profundidad(arbol->izquierdo);
    int profDer = profundidad(arbol->derecho);
    if (abs(profIzq - profDer) <= 1 && esBalanceado(arbol->izquierdo) && esBalanceado(arbol->derecho)) {
        return 1;
    }
    return 0;
}

// funcion para modificar el valor de un nodo en el arbol
void modificarNodo(struct Nodo* arbol, int datoAntiguo, int datoNuevo) {
    struct Nodo* nodo = buscar(arbol, datoAntiguo);
    if (nodo != NULL) {
        nodo->dato = datoNuevo;
    }
}

int main() {
    struct Nodo* arbol = NULL;
    int datos[] = {8, 3, 1, 20, 5, 10, 7, 4};
    int n = sizeof(datos) / sizeof(datos[0]);

    // inserta nodos
    for (int i = 0; i < n; i++) {
        insertar(&arbol, datos[i]);
    }

    // recorridos del arbol
    printf("recorrido Preorden:\n");
    preorden(arbol);
    printf("\n");

    printf("recorrido Inorden:\n");
    inorden(arbol);
    printf("\n");

    printf("recorrido Postorden:\n");
    postorden(arbol);
    printf("\n");

    // Obtencion de informacion del arbol
    printf("Numero de nodos: %d\n", contarNodos(arbol));
    printf("Profundidad del árbol: %d\n", profundidad(arbol));
    printf("Arbol completo: %s\n", esCompleto(arbol, 0, contarNodos(arbol)) ? "Sí" : "No");
    printf("Arbol balanceado: %s\n", esBalanceado(arbol) ? "Sí" : "No");

    // busqueda de un nodo especifico
    int datoBuscar = 5;
    struct Nodo* nodoEncontrado = buscar(arbol, datoBuscar);
    if (nodoEncontrado != NULL) {
        printf("Nodo con valor %d encontrado.\n", datoBuscar);
    } else {
        printf("Nodo con valor %d no encontrado.\n", datoBuscar);
    }

    // eliminacion de un nodo especifico
    int datoEliminar = 3;
    arbol = eliminarNodo(arbol, datoEliminar);
    printf("Árbol después de eliminar el nodo con valor %d:\n", datoEliminar);
    inorden(arbol);
    printf("\n");

    // modificacion de un nodo
    int datoAntiguo = 10;
    int datoNuevo = 15;
    modificarNodo(arbol, datoAntiguo, datoNuevo);
    printf("Árbol después de modificar el nodo con valor %d a %d:\n", datoAntiguo, datoNuevo);
    inorden(arbol);
    printf("\n");

    return 0;
}
