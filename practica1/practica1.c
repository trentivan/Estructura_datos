#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct datos {
    char matricula[50];
    char Apaterno[50];
    char Amaterno[50];
    char nombre[50];
    int carrera;
} Datos;

typedef struct Nodo {
    Datos datos;
    struct Nodo *siguiente;
} Nodo;

typedef struct Lista {
    Nodo *cabeza;
    int valor;
} Lista;

Nodo *crearNodo(Datos *datos);
void insertarAlFinal(Lista *lista, Datos *datos);
void insertarinicio(Lista *lista, Datos *datos);
void insertarEnPosicion(Lista *lista, Datos *datos, int posicion);
void borrarPorMatricula(Lista *lista, const char *matricula);
void imprimirLista(Lista *lista);
void imprimir(Nodo *nodo);

int main() {
    Datos datos;
    Lista lista;
    lista.cabeza = NULL;
    int posicion;

    if (lista.cabeza == NULL) {
        insertarinicio(&lista, &datos);
        printf("Insertado al inicio de la lista\n");
        imprimirLista(&lista);
    }

    insertarAlFinal(&lista, &datos);
    printf("\nInsertado al final de la lista\n");
    imprimirLista(&lista);

    printf("Dame la posición donde quieres insertar: ");
    scanf("%d", &posicion);

    insertarEnPosicion(&lista, &datos, posicion);
    printf("Insertado en la posición %d\n", posicion);
    imprimirLista(&lista);

    printf("Lista completa\n");
    imprimirLista(&lista);

    return 0;
}


Nodo *crearNodo(Datos *datos) 
{
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    fflush(stdin);
    printf("Dame tu matricula\n");
    gets(datos->matricula);
    strcpy(nodo->datos.matricula, datos->matricula);
    printf("Dame tu apellido paterno\n");
    gets(datos->Apaterno);
    strcpy(nodo->datos.Apaterno, datos->Apaterno);
    printf("Dame tu apellido materno\n");
    gets(datos->Amaterno);
    strcpy(nodo->datos.Amaterno, datos->Amaterno);
    printf("Dame tu nombre\n");
    gets(datos->nombre);
    strcpy(nodo->datos.nombre, datos->nombre);
    printf("Dame tu carrera\n");
    printf("0) ing. Computacion\n");
    printf("1) ing. Software\n");
    printf("2) contabilidad\n");
    scanf("%d", &datos->carrera);
    nodo->datos.carrera = datos->carrera;
    nodo->siguiente = NULL;
    return nodo;
}

void insertarinicio(Lista *lista, Datos *datos) 
{
    Nodo *nuevoNodo = crearNodo(datos);

    if (lista->cabeza == NULL) 
    {
        lista->cabeza = nuevoNodo;
    } else 
    {
        printf("La lista no está vacía. No se insertará en la primera posición.\n");
        free(nuevoNodo);  
    }
}

void insertarAlFinal(Lista *lista, Datos *datos) 
{
    Nodo *nuevoNodo = crearNodo(datos);

    if (lista->cabeza == NULL) 
    {
        lista->cabeza = nuevoNodo;
    } else 
    {
        Nodo *temp = lista->cabeza;
        while (temp->siguiente != NULL) 
        {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

void insertarEnPosicion(Lista *lista, Datos *datos, int posicion)
{
    Nodo *nuevoNodo = crearNodo(datos);

    if (posicion < 0) 
    {
        printf("La posición no puede ser negativa.\n");
        free(nuevoNodo);
        return;
    }

    if (posicion == 0 || lista->cabeza == NULL) 
    {
        nuevoNodo->siguiente = lista->cabeza;
        lista->cabeza = nuevoNodo;
    } else 
    {
        Nodo *temp = lista->cabeza;
        for (int i = 0; i < posicion - 1 && temp->siguiente != NULL; i++) 
        {
            temp = temp->siguiente;
        }
        nuevoNodo->siguiente = temp->siguiente;
        temp->siguiente = nuevoNodo;
    }
}

void borrarPorMatricula(Lista *lista, const char *matricula) 
{
    if (lista->cabeza == NULL) 
    {
        printf("La lista está vacía. No se puede borrar.\n");
        return;
    }

    Nodo *temp = lista->cabeza;
    Nodo *anterior = NULL;

    while (temp != NULL && strcmp(temp->datos.matricula, matricula) != 0) 
    {
        anterior = temp;
        temp = temp->siguiente;
    }

    if (temp == NULL)
     {
        printf("No se encontró un nodo con la matrícula proporcionada.\n");
        return;
    }

    
    if (anterior == NULL) 
    {
    
        lista->cabeza = temp->siguiente;
    } else 
    {
        anterior->siguiente = temp->siguiente;
    }

    free(temp);
    printf("Nodo con matrícula %s borrado exitosamente.\n", matricula);
}

void imprimir(Nodo *nodo) 
{
    printf("%-15s %-15s %-15s %-15s %d\n", nodo->datos.matricula, nodo->datos.nombre, nodo->datos.Apaterno,
           nodo->datos.Amaterno, nodo->datos.carrera);
}

void imprimirLista(Lista *lista) 
{
    Nodo *temp = lista->cabeza;

    if (temp == NULL) 
    {
        printf("La lista está vacía.\n");
        return;
    }

    printf("Contenido de la lista:\n");

    while (temp != NULL) 
    {
        imprimir(temp);
        temp = temp->siguiente;
    }
}

