#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>

static void prueba_lista_vacia(void) {
    printf("INICIO DE PRUEBAS CON LISTA VACIA\n");

    lista_t *lista = lista_crear();
    print_test("Crear lista", lista != NULL);
    
    printf("\nCONDICIÓN DE BORDE\n");
    print_test("La lista está vacía", lista_esta_vacia(lista));
    print_test("Borrar un elemento de una lista vacía devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("Ver el primer elemento de una lista vacía devuelve NULL", lista_ver_primero(lista) == NULL);

    lista_destruir(lista, NULL);
}

static void prueba_agregar_elementos(void) {
    printf("\nINICIO DE PRUEBAS INSERTAR Y BORRAR ELEMENTOS\n");

    lista_t *lista = lista_crear();
    int arreglo[] = {0, 2, 5, 6};

    print_test("Agregar 1 elemento al principio", lista_insertar_primero(lista, &arreglo[0]));
    print_test("El elemento agregado es el primero", lista_ver_primero(lista) == &arreglo[0]);
    print_test("Agregar un segundo elemento al principio", lista_insertar_primero(lista, &arreglo[1]));
    print_test("El elemento agregado es el primero", lista_ver_primero(lista) == &arreglo[1]);
    print_test("Agregar un tercer elemento al final", lista_insertar_ultimo(lista, &arreglo[2]));
    print_test("El elemento agregado es el último", lista_ver_ultimo(lista) == &arreglo[2]);
    print_test("Agregar un cuarto elemento al final", lista_insertar_ultimo(lista, &arreglo[3]));
    print_test("El elemento agregado es el último", lista_ver_ultimo(lista) == &arreglo[3]);
    print_test("Borro el primer elemento", lista_borrar_primero(lista) == &arreglo[1]);
    print_test("Borro el segundo elemento", lista_borrar_primero(lista) == &arreglo[0]);
    print_test("Borro el tercer elemento", lista_borrar_primero(lista) == &arreglo[2]);
    print_test("Borro el cuarto elemento", lista_borrar_primero(lista) == &arreglo[3]);
    print_test("La lista está vacía", lista_esta_vacia(lista));
    
    lista_destruir(lista, NULL);
}

static void prueba_de_volumen(void) {
    printf("\nINICIO DE PRUEBAS VOLUMEN\n");

    lista_t *lista = lista_crear();
    int dato;
    bool resultado = true;

    for (int i = 0; i <= 999; i++) {
        resultado = lista_insertar_ultimo(lista, &dato);
        if (!resultado) break;
    }
    print_test("Puedo insertar todos los elementos", resultado);

    for (int i = 999; i >= 0; i--) {
        if (i == 0) {
            resultado = lista_borrar_primero(lista) == &dato && lista_esta_vacia(lista);
            break;
        }
        resultado = lista_borrar_primero(lista) == &dato;
        if (!resultado) break;
    }
    print_test("Puedo borrar todos los elementos", resultado);

    lista_destruir(lista, NULL);
}

static void prueba_insertar_NULL(void) {
    printf("\nINICIO DE PRUEBAS INSERTAR ELEMENTO NULL\n");

    lista_t *lista = lista_crear();

    print_test("Agrego NULL", lista_insertar_primero(lista, NULL));
    print_test("La lista no está vacía", lista_esta_vacia(lista) == false);
    print_test("El primer elemento es NULL", lista_ver_primero(lista) == NULL);
    print_test("Borro NULL", lista_borrar_primero(lista) == NULL);
    print_test("La lista queda vacía", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);
}

void pila_destruir_wrapper(void* pila) {
    pila_destruir(pila);
}

static void prueba_destruccion(void) {
    printf("\nINICIO DE PRUEBAS DESTRUCCIÓN\n");

    pila_t *pila = pila_crear();
    lista_t *lista = lista_crear();
    int valor;

    print_test("Agrego elementos a una pila", pila_apilar(pila, &valor) && pila_apilar(pila, &valor) && pila_apilar(pila, &valor));
    print_test("Agrego a la lista una pila que tiene elementos", lista_insertar_primero(lista, pila));
    print_test("El primer elemento es la pila", lista_ver_primero(lista) == pila);

    lista_destruir(lista, pila_destruir_wrapper);
}

void pruebas_lista_estudiante() {
    prueba_lista_vacia();
    prueba_agregar_elementos();
    prueba_de_volumen();
    prueba_insertar_NULL();
    prueba_destruccion();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
