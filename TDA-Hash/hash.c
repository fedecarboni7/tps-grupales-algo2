#include "hash.h"
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

size_t hash_cantidad(const hash_t *hash) {
    size_t cantidad = 0;
    for(size_t i = 0; i < hash->m; i++) {
        if(hash->lista[i] && !lista_esta_vacia(hash->lista[i])) {
            lista_iter_t *iter = lista_iter_crear(hash->lista[i]);
            while (lista_iter_ver_actual(iter)) {
                lista_iter_avanzar(iter);
                cantidad++;
            }
            lista_iter_destruir(iter);
        }
    }
    return cantidad; 
}