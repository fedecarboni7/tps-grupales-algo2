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

// Definición del struct lista_iter.

typedef struct lista_iter {
    lista_t* lista;
    nodo_t* actual;
} lista_iter_t;


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

void *lista_ver_primero(const lista_t *lista) {
    return lista_esta_vacia(lista) ? NULL : lista->nodo_inicio->dato; 
}

size_t lista_largo(const lista_t *lista) {
    return lista->largo;
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    
}

lista_iter_t lista_iter_crear(lista_t *lista) {
    lista_iter_t *lista_iter = malloc(sizeof(lista_iter_t));
    lista_iter->lista = lista;
    lista_iter->actual = lista->nodo_inicio; 
    return lista_iter; 
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
    return lista_esta_vacia(iter->lista) ? iter->actual->dato : NULL; 
}

void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}

void *lista_iter_borrar(lista_iter_t *iter) {
    void *dato_borrado = iter->actual->dato;
    nodo_t *nodo_borrado = iter->actual;
    
    // Tengo que modificar el anterior al borrado para que apunte al próximo del borrado
    
    // Busco al anterior del nodo que quiero borrar
    while(lista_iter_ver_actual(iter)->prox != nodo_borrado) {
        lista_iter_avanzar(iter);
    }

    // Cambio la flecha y destruyo al nodo borrado
    iter->actual = nodo_borrado->prox;
    free(nodo_borrado);

    return dato_borrado;
}

bool lista_iter_avanzar(lista_iter_t *iter){

}

bool lista_iter_al_final(const lista_iter_t *iter){

}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){

}
