//
// Created by LAMM_ on 27/05/2023.
//

#ifndef PRACTICA12_ARBOLES_H
#define PRACTICA12_ARBOLES_H

#include "ListaNodosArbol.h"
#include "Utilidades.h"

typedef enum TipoNodo {
    RAIZ,
    ESPECIALIDAD,
    MATERIA
} TipoNodo;

typedef enum Estado {
    COMPLETADO,
    NO_COMPLETADO,
    CURSADO,
    NO_CURSADO,
    NO_IMPORTA
} Estado;

typedef struct NodoArbol {
    char *rotulo;
    size_t profundidad;
    struct ListaNodosArbol *hijos;
    TipoNodo tipo;
    Estado estado;
} NodoArbol;

typedef struct Arbol {
    NodoArbol *raiz;
    size_t altura;
} Arbol;

//Crea un arbol, requiere el nombre de la raiz, profundidad y altura inicializadas en 1, tipo en RAIZ y estado en NO_IMPORTA
Arbol *crearArbol(char *contenido_raiz);

//Crea un nodo, requiere el nombre, y tipo. Si es ESPECIALIDAD el estado es NO_COMPLETADO, si es MATERIA el estado es NO_CURSADO
NodoArbol *crearNodoArbol(char *contenido, TipoNodo tipo);

//Verifica si altura es mayor que la altura del arbol, si es asi, cambia la altura del arbol
void cambiarAltura(Arbol *arbol, size_t altura);

//Devuelve el nodo cuyo nombre sea clave, si no existe devuelve NULL
NodoArbol *buscarNodoConClave(NodoArbol *nodo, char *clave);

//Inserta un nodo en el arbol, objetivo es el nombre del padre del nodo, si el padre no existe devuelve false, caso contrario devuelve true
bool insertarEnArbol(Arbol *arbol, char *objetivo, NodoArbol *nodo);

//@TODO: Implementar
//Borra un nodo en el arbol
bool destruirNodoEnArbol(Arbol *arbol, char *clave);

//@TODO: Implementar
//Borra un nodo
bool destruirNodo(NodoArbol *nodo);

//Imprime el arbol desde el nodo indicado
void imprimirArbol(NodoArbol *nodo_arbol);

bool cambiarEstadosDesdeLista(struct ListaNodosArbol *lista, Estado nuevo_estado);

void obtenerMateriasDisponibles(NodoArbol *nodo, struct ListaNodosArbol *lista);

bool sePuedeCursar(NodoArbol *nodo);

bool especialidadTerminada(NodoArbol *nodo);

#endif //PRACTICA12_ARBOLES_H
