#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TABLA 10

// estructura para representar un elemento en la tabla hash
struct Elemento {
    int clave;
    char valor[100];
    struct Elemento* siguiente;
};

// funcion hash utilizando la fórmula específica
int hash(int clave) {
    return clave + (7 + 10 + 11 + 34) % TAM_TABLA;
}

// funcion para crear un nuevo elemento
struct Elemento* crearElemento(int clave, const char* valor) {
    struct Elemento* nuevoElemento = (struct Elemento*)malloc(sizeof(struct Elemento));
    nuevoElemento->clave = clave;
    strcpy(nuevoElemento->valor, valor);
    nuevoElemento->siguiente = NULL;
    return nuevoElemento;
}

// funcion para insertar un nuevo elemento en la tabla hash
void insertar(struct Elemento* tabla[], int clave, const char* valor) {
    int indice = hash(clave);
    struct Elemento* nuevoElemento = crearElemento(clave, valor);
    nuevoElemento->siguiente = tabla[indice];
    tabla[indice] = nuevoElemento;
}

// funcion para buscar un elemento en la tabla hash
struct Elemento* buscar(struct Elemento* tabla[], int clave) {
    int indice = hash(clave);
    struct Elemento* temp = tabla[indice];
    while (temp != NULL) {
        if (temp->clave == clave) {
            return temp;
        }
        temp = temp->siguiente;
    }
    return NULL;
}

// funcion para eliminar un elemento de la tabla hash
void eliminar(struct Elemento* tabla[], int clave) {
    int indice = hash(clave);
    struct Elemento* temp = tabla[indice];
    struct Elemento* prev = NULL;

    while (temp != NULL && temp->clave != clave) {
        prev = temp;
        temp = temp->siguiente;
    }

    if (temp == NULL) {
        printf("Elemento con clave %d no encontrado.\n", clave);
        return;
    }

    if (prev == NULL) {
        tabla[indice] = temp->siguiente;
    } else {
        prev->siguiente = temp->siguiente;
    }

    free(temp);
    printf("Elemento con clave %d eliminado.\n", clave);
}

// funcion para actualizar un elemento en la tabla hash
void actualizar(struct Elemento* tabla[], int clave, const char* nuevoValor) {
    struct Elemento* elemento = buscar(tabla, clave);
    if (elemento != NULL) {
        strcpy(elemento->valor, nuevoValor);
        printf("Elemento con clave %d actualizado.\n", clave);
    } else {
        printf("Elemento con clave %d no encontrado.\n", clave);
    }
}

// funcion para listar todos los elementos en la tabla hash
void listar(struct Elemento* tabla[]) {
    for (int i = 0; i < TAM_TABLA; i++) {
        struct Elemento* temp = tabla[i];
        if (temp != NULL) {
            printf("Indice %d:\n", i);
        }
        while (temp != NULL) {
            printf("  Clave: %d, Valor: %s\n", temp->clave, temp->valor);
            temp = temp->siguiente;
        }
    }
}

int main() {
    struct Elemento* tabla[TAM_TABLA] = {NULL};

    // insertar elementos
    insertar(tabla, 1, "Valor1");
    insertar(tabla, 2, "Valor2");
    insertar(tabla, 3, "Valor3");
    insertar(tabla, 12, "Valor12");
    insertar(tabla, 22, "Valor22");

    // listar elementos
    printf("Elementos en la tabla hash:\n");
    listar(tabla);
    printf("\n");

    // buscar un elemento
    int claveBuscar = 12;
    struct Elemento* encontrado = buscar(tabla, claveBuscar);
    if (encontrado != NULL) {
        printf("Elemento encontrado - Clave: %d, Valor: %s\n", claveBuscar, encontrado->valor);
    } else {
        printf("Elemento con clave %d no encontrado.\n", claveBuscar);
    }
    printf("\n");

    // actualizar un elemento
    int claveActualizar = 2;
    actualizar(tabla, claveActualizar, "ValorActualizado2");
    printf("Elementos en la tabla hash despues de actualizar:\n");
    listar(tabla);
    printf("\n");

    // eliminar un elemento
    int claveEliminar = 3;
    eliminar(tabla, claveEliminar);
    printf("Elementos en la tabla hash despues de eliminar:\n");
    listar(tabla);
    printf("\n");

    return 0;
}
