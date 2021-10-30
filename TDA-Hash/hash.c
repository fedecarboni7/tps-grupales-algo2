#include "hash.h"
#include "lista.h"
#include <stdlib.h>

// Definición del struct hash

typedef struct hash {
    lista_t** tabla;
    size_t m;
    hash_destruir_dato_t destruir_dato;
} hash_t;

// Definición del struct campo

typedef struct campo {
    const char* clave;
    void* dato;
} campo_t;

// Definición del struct hash_iter

typedef struct hash_iter {
    hash_t* hash;
    campo_t* actual;
} hash_iter_t;

// Definición de la función de hashing elegida: DJB2
// Fuente: https://softwareengineering.stackexchange.com/a/49566

unsigned long funcion_hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
        
    return hash;
}

/* *****************************************************************
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/

void *hash_obtener(const hash_t *hash, const char *clave) {
    bool pertenece = hash_pertenece(hash, clave);
    int pos = funcion_hash(clave) % hash->m;
    void *dato = NULL;

    if (pertenece) {
        lista_iter_t *iter = lista_iter_crear(hash->tabla[pos]);
        while (lista_iter_ver_actual(iter)->clave != clave) {
            lista_iter_avanzar(iter);
            if (lista_iter_al_final(iter)) return NULL;
        }

        dato = lista_iter_ver_actual(iter)->dato;
        lista_iter_destruir(iter);
    }

    return dato; 
}

size_t hash_cantidad(const hash_t *hash) {
    size_t cantidad = 0;
    for(size_t i = 0; i < hash->m; i++) {
        if(hash->tabla[i] && !lista_esta_vacia(hash->tabla[i])) {
            lista_iter_t *iter = lista_iter_crear(hash->tabla[i]);
            while (lista_iter_ver_actual(iter)) {
                lista_iter_avanzar(iter);
                cantidad++;
            }
            lista_iter_destruir(iter);
        }
    }
    return cantidad; 
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

hash_iter_t *hash_iter_crear(const hash_t *hash) {
    hash_iter_t *iter = malloc(sizeof(hash_iter_t));
    if (!iter) return NULL;
    lista_t *lista;
    int i = 0;
    do {
        lista = hash->tabla[i];
        i++;
    } while(lista_esta_vacia(lista));
    iter->actual = lista_iter_crear(lista);
    return iter;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) return NULL;
    return iter->actual->actual->clave; 
}

void hash_iter_destruir(hash_iter_t *iter) {
    lista_iter_destruir(iter->actual);
    free(iter);
}