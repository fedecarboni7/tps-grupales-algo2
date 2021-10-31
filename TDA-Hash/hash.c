#include "hash.h"
#include "lista.h"
#include <stdlib.h>

#define FACTOR_CARGA 0.7

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

void redimensionar(hash_t *hash) {
    hash->m = hash->m * 2;
    lista_t** nueva_tabla;
    hash_iter_t *iter = hash_iter_crear(hash);
    for (size_t i = 0; i < hash->m; i++) {
        if(hash->tabla[i]) {
            int pos = funcion_hash(hash_iter_ver_actual(iter)) % hash->m;
            nueva_tabla[pos] = hash->tabla[i];
        }
    }
    hash_iter_destruir(iter);
    hash->tabla = nueva_tabla;
}

/* *****************************************************************
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/

void *hash_obtener(const hash_t *hash, const char *clave) {
    int pos = funcion_hash(clave) % hash->m;
    void *dato = NULL;
    if (hash_pertenece(hash, clave)) {
        lista_iter_t *iter = lista_iter_crear(hash->tabla[pos]);
        campo_t *actual = lista_iter_ver_actual(iter);
        while (actual->clave != clave) {
            lista_iter_avanzar(iter);
            if (lista_iter_al_final(iter)) return NULL;
        }

        dato = actual->dato;
        lista_iter_destruir(iter);
    }
    return dato; 
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    if ((float) hash_cantidad(hash) / (float) hash->m >= FACTOR_CARGA) {
        redimensionar(hash);
    }
    campo_t *campo = malloc(sizeof(campo_t));
    if (!campo) return false; 
    int pos = funcion_hash(clave) % hash->m; 
    if (!hash_pertenece(hash, clave)) {
        lista_t *lista = lista_crear();
        hash->tabla[pos] = lista; 
    }
    lista_insertar_ultimo(hash->tabla[pos], campo);
    return true;
}

size_t hash_cantidad(const hash_t *hash) {
    size_t cantidad = 0;
    for(size_t i = 0; i < hash->m; i++) {
        if(hash->tabla[i] && !lista_esta_vacia(hash->tabla[i])) { // Corregir
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
    // Asigno a iter->actual
    return iter;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) return NULL;
    return iter->actual->clave; 
}

void hash_iter_destruir(hash_iter_t *iter) {
    free(iter);
}