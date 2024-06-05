#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Nodo{
    int info;
    struct Nodo* siguiente;
};


struct Nodo *crearNodo(int i);
void insertar(struct Nodo **inicio, struct Nodo **Ultimo, int i);
void imprimir(struct Nodo *inicio);
void sacarNodo(struct Nodo **inicio);

int main()
{
    srand(time(NULL));
    struct Nodo *inicio = NULL;
    struct Nodo *Ultimo = NULL;

    int i = 0;
    // int info=5;
    while(i<3)
    {
        insertar(&inicio, &Ultimo, i);
        i++;
    }
    imprimir(inicio);
    printf("\n");
    sacarNodo(&inicio);
}

void sacarNodo(struct Nodo **inicio)
{
    if(*inicio == NULL)
    {
        printf("La lista esta vacia, no se puede sacar ningun dato");
    }
    while(*inicio != NULL)
    {
        struct Nodo *temp = *inicio;
        
        *inicio = (*inicio)->siguiente;
        printf("Se elimino el nodo con valor: %d\n", temp->info);
        free(temp);
    }
}

void insertar(struct Nodo **inicio, struct Nodo **Ultimo, int i)
{
    struct Nodo *nodo = crearNodo(i);
    
    if (*inicio == NULL)
    {
        // printf("primer sentencia");
        *inicio = nodo;
        *Ultimo = nodo;
        // printf("lista vacia\n");
    }
    else
    {
        (*Ultimo)->siguiente = nodo;
        *Ultimo = nodo;
    }
    // printf("fin insertar\n");
}


void imprimir(struct Nodo *inicio)
{
    struct Nodo *temp = inicio;

    if (temp == NULL)
    {
        printf("La cola está vacía.\n");
    }
    else
    {
        printf("Contenido de la cola:\n");
        while (temp != NULL)
        {
            printf("%d\n", temp->info);
            temp = temp->siguiente;
        }
    }
}

struct Nodo *crearNodo(int i)
{
    struct Nodo* nuevo_nodo = (struct Nodo*)malloc(tamanoof(struct Nodo));
    
    // nuevo_nodo->info = (rand()%100) + 1;
    nuevo_nodo->info = i;
    nuevo_nodo->siguiente = NULL;

    return nuevo_nodo;
}