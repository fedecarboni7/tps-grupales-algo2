#include "lista.h"
#include <stdlib.h>

// Definición del struct lista.

struct lista {
    struct nodo* nodo_inicio;
    struct nodo* nodo_fin;
    size_t largo;
};

// Definición del struct nodo.

typedef struct nodo {
    void* dato;
    struct nodo* prox;    
} nodo_t;


/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t *lista_crear(void) {
    lista_t *lista = calloc(1, sizeof(lista_t));
    return lista;
}

nodo_t* nodo_crear(void* dato) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

bool lista_esta_vacia(lista_t lista) {
    return lista->largo == 0;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
    while (!lista_esta_vacia(lista)) {
        void *elemento = lista_borrar_primero(lista);
        if (destruir_dato) destruir_dato(elemento);
    }
    free(lista);
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t* nodo = nodo_crear(dato);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) {
        lista->nodo_inicio = nodo;
        lista->nodo_fin = nodo;
        lista->nodo_inicio->prox = lista->nodo_fin;
    }
    else {
        nodo->prox = lista->nodo_inicio;
        lista->nodo_inicio = nodo;
    }
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t *nodo = nodo_crear(dato);
    if (!nodo) return false;
    if(lista_esta_vacia(lista)) {
        return false;
    }
    lista->nodo_fin->prox = nodo;
    lista->nodo_fin = nodo; 
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista){
    
}

void *lista_ver_primero(const lista_t *lista) {
    if (!lista_esta_vacia(lista)) {
        return lista->nodo_inicio->dato;
    }
    return NULL; 
}

size_t lista_largo(const lista_t *lista) {
    return lista->largo;
}