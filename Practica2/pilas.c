#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int info;
    struct Nodo* siguiente;
};

struct Nodo *crearNodo(int i);
void apilar(struct Nodo **tope, int i);
int pop(struct Nodo **tope);
int estaVacia(struct Nodo *tope);
void vaciarPila(struct Nodo **tope);
int obtenerTamano(struct Nodo *tope);
void imprimir(struct Nodo *tope);

int main() {
    struct Nodo *tope = NULL;

    apilar(&tope, 1);
    apilar(&tope, 2);
    apilar(&tope, 3);

    printf("pila despues de apilar 3 elementos:\n");
    imprimir(tope);
    printf("\n");

    int valor = pop(&tope);
    printf("valor desapilado: %d\n", valor);

    printf("pila despues de pop de un elemento:\n");
    imprimir(tope);
    printf("\n");

    printf("tamano de la pila: %d\n", obtenerTamano(tope));

    vaciarPila(&tope);
    printf("Pila después de vaciarla:\n");
    imprimir(tope);

    return 0;
}

struct Nodo *crearNodo(int i) {
    struct Nodo* nuevo_nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevo_nodo->info = i;
    nuevo_nodo->siguiente = NULL;
    return nuevo_nodo;
}

void apilar(struct Nodo **tope, int i) {
    struct Nodo *nodo = crearNodo(i);
    nodo->siguiente = *tope;
    *tope = nodo;
}

int pop(struct Nodo **tope) {
    if (estaVacia(*tope)) {
        printf("La pila está vacía, no se puede pop ningún dato\n");
        return -1; // Indica que la pila estaba vacía
    }
    struct Nodo *temp = *tope;
    int valor = temp->info;
    *tope = (*tope)->siguiente;
    free(temp);
    return valor;
}

int estaVacia(struct Nodo *tope) {
    return tope == NULL;
}

void vaciarPila(struct Nodo **tope) {
    while (!estaVacia(*tope)) {
        pop(tope);
    }
}

int obtenerTamano(struct Nodo *tope) {
    int tamano = 0;
    while (tope != NULL) {
        tamano++;
        tope = tope->siguiente;
    }
    return tamano;
}

void imprimir(struct Nodo *tope) {
    struct Nodo *temp = tope;
    if (estaVacia(temp)) {
        printf("La pila está vacía\n");
        return;
    }
    while (temp != NULL) {
        printf("%d\n", temp->info);
        temp = temp->siguiente;
    }
}
