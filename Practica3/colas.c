#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int info;
    struct Nodo* siguiente;
};

struct Nodo *crearNodo(int i);
void insertar(struct Nodo **inicio, struct Nodo **Ultimo, int i);
int dequeue(struct Nodo **inicio, struct Nodo **Ultimo);
int obtenerFront(struct Nodo *inicio);
int estaVacia(struct Nodo *inicio);
int tamano(struct Nodo *inicio);
void vaciarCola(struct Nodo **inicio, struct Nodo **Ultimo);
void imprimir(struct Nodo *inicio);

int main() {
    struct Nodo *inicio = NULL;
    struct Nodo *Ultimo = NULL;

    insertar(&inicio, &Ultimo, 1);
    insertar(&inicio, &Ultimo, 2);
    insertar(&inicio, &Ultimo, 3);

    printf("Cola después de insertar 3 elementos:\n");
    imprimir(inicio);
    printf("\n");

    int valor = dequeue(&inicio, &Ultimo);
    printf("Valor eliminado del frente: %d\n", valor);

    printf("Cola después de eliminar un elemento:\n");
    imprimir(inicio);
    printf("\n");

    int frente = obtenerFront(inicio);
    printf("Elemento en el frente de la cola: %d\n", frente);

    printf("Tamaño de la cola: %d\n", tamano(inicio));

    vaciarCola(&inicio, &Ultimo);
    printf("Cola después de vaciarla:\n");
    imprimir(inicio);

    return 0;
}

struct Nodo *crearNodo(int i) {
    struct Nodo* nuevo_nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevo_nodo->info = i;
    nuevo_nodo->siguiente = NULL;
    return nuevo_nodo;
}

void insertar(struct Nodo **inicio, struct Nodo **Ultimo, int i) {
    struct Nodo *nodo = crearNodo(i);
    if (*inicio == NULL) {
        *inicio = nodo;
        *Ultimo = nodo;
    } else {
        (*Ultimo)->siguiente = nodo;
        *Ultimo = nodo;
    }
}

int dequeue(struct Nodo **inicio, struct Nodo **Ultimo) {
    if (estaVacia(*inicio)) {
        printf("La cola está vacía, no se puede eliminar ningún dato\n");
        return -1; // Indica que la cola estaba vacía
    }
    struct Nodo *temp = *inicio;
    int valor = temp->info;
    *inicio = (*inicio)->siguiente;
    if (*inicio == NULL) {
        *Ultimo = NULL;
    }
    free(temp);
    return valor;
}

int obtenerFront(struct Nodo *inicio) {
    if (estaVacia(inicio)) {
        printf("La cola está vacía\n");
        return -1; // Indica que la cola está vacía
    }
    return inicio->info;
}

int estaVacia(struct Nodo *inicio) {
    return inicio == NULL;
}

int tamano(struct Nodo *inicio) {
    int tamaño = 0;
    while (inicio != NULL) {
        tamaño++;
        inicio = inicio->siguiente;
    }
    return tamaño;
}

void vaciarCola(struct Nodo **inicio, struct Nodo **Ultimo) {
    while (!estaVacia(*inicio)) {
        dequeue(inicio, Ultimo);
    }
}

void imprimir(struct Nodo *inicio) {
    if (estaVacia(inicio)) {
        printf("La cola está vacía\n");
        return;
    }
    struct Nodo *temp = inicio;
    while (temp != NULL) {
        printf("%d\n", temp->info);
        temp = temp->siguiente;
    }
}
