#include "hash.h"
#include <stdlib.h>

// Definición del struct hash

typedef struct hash {
    lista_t** tabla;
    size_t largo;
} hash_t;

// Definición del struct campo

typedef struct campo {
    const char* clave;
    void* dato;
} campo_t;

