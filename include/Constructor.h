//
// Created by LAMM_ on 27/05/2023.
//

#ifndef PRACTICA12_CONSTRUCTOR_HPP
#define PRACTICA12_CONSTRUCTOR_HPP

#define BUFFER_LENGTH 512

/**
 * Construye un arbol a partir de un archivo de texto.
 * El arbol es jerarquico, por lo que la insercion de nodos debe
 * de ser indicando: <Nodo hijo>:<Nodo padre>.
 * El archivo de texto contiene, instrucciones de creacion e insercion,
 * teniendo a la primera linea (no vacia) como el contenido del nodo raíz, posteriormente las inserciones de nodos
 * son diferenciadas por saltos de linea.
 * El arbol debe mantener claves unicas para cada nodo, siendo estas
 * el contenido en texto de cada nodo, sensible a las mayusculas.
 * Si se trata de insertar un nodo con una clave ya existente, dicho nodo no será insertado.
 */

#include <stdio.h>
#include "Arboles.h"

#define NOMBRE_RAIZ "Especialidades"

typedef struct Nombres {
    char *padre;
    char *hijo;
} Nombres;

//Crea un arbol a partir de un archivo de texto, devuelve NULL si no se pudo crear el arbol
Arbol *construirArbol(char *nombre_archivo);

//Regresa el contenido de un archivo de texto, si el archivo no puede ser leido, devuelve NULL
char *leerArchivo(char *nombre_archivo);

//Obtiene el nombre de la raiz del arbol (primer linea), devuelve NULL si no se pudo obtener el nombre
char *obtenerNombreRaiz(char *texto_archivo);

//Obtiene los nombres de los nodos a insertar (hijo y padre separados por :), devuelve NULL si no se pudo obtener los nombres
void obtenerNombresNodo(Nombres *contenedor, char *fragmento_texto, size_t tam_fragmento);

//Verifica si el nombre el nombre corresponde a "Especialidades", devuelve true si es asi, false si no
bool esNodoEspecialidades(char *nombre_padre);

#endif //PRACTICA12_CONSTRUCTOR_HPP
