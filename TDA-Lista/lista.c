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

void *lista_borrar_primero(lista_t *lista){
    if (lista_esta_vacia(lista)) return NULL;
    void* dato_anterior = lista->nodo_inicio->dato;
    nodo_t* nodo_aux = lista->nodo_inicio;
    if (lista->largo == 1) {
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
    }
    else {
        lista->nodo_inicio = lista->nodo_inicio->siguiente;
    }
    lista->largo--;
    free(nodo_aux);
    return dato_anterior;
}

void *lista_ver_ultimo(const lista_t* lista){
    return lista_esta_vacia(lista) ? NULL : lista->nodo_fin->dato;
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/
