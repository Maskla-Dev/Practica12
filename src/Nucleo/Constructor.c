//
// Created by LAMM_ on 27/05/2023.
//
#include "Constructor.h"
#include <stdlib.h>
#include <string.h>

Arbol *construirArbol(char *nombre_archivo) {
    Arbol *arbol = NULL;
    NodoArbol *nodo = NULL;
    char *datos = leerArchivo(nombre_archivo);
    char *nombre_raiz;
    char *tmp;
    Nombres nombres;
    size_t indice_texto = 0;
    size_t inicio_fragmento = 0;
    size_t tam_fragmento = 0;
    if (datos == NULL) {
        printf("No se pudo leer el archivo %s\n", nombre_archivo);
        return NULL;
    }
    nombre_raiz = obtenerNombreRaiz(datos);
    indice_texto = strlen(nombre_raiz) + 1;
    inicio_fragmento = indice_texto;
    arbol = crearArbol(nombre_raiz);
    if (arbol == NULL) {
        printf("No se pudo crear el arbol\n");
        return NULL;
    }
    while (datos[indice_texto] != '\0') {
        if (datos[indice_texto] == '\n') {
            tam_fragmento = indice_texto - inicio_fragmento;
            tmp = (char *) calloc(tam_fragmento + 1, sizeof(char));
            if (tmp == NULL) {
                printf("No se pudo crear el fragmento\n");
                return NULL;
            }
            strncpy(tmp, datos + inicio_fragmento, tam_fragmento);
            obtenerNombresNodo(&nombres, tmp, tam_fragmento);
            if (nombres.hijo == NULL && nombres.padre == NULL) {
                printf("No se pudo obtener nombres nodo\n");
                return NULL;
            }
            free(tmp);
            tmp = NULL;
            nodo = crearNodoArbol(nombres.hijo, (esNodoEspecialidades(nombres.padre)) ? ESPECIALIDAD : MATERIA);
            if (nodo == NULL) {
                printf("No se pudo crear nodo\n");
                return NULL;
            }
            if (!insertarEnArbol(arbol, nombres.padre, nodo)) {
                printf("No se pudo insertar nodo\n");
                return NULL;
            }
            free(nombres.hijo);
            free(nombres.padre);
            nombres.hijo = NULL;
            nombres.padre = NULL;
            inicio_fragmento = indice_texto + 1;
        }
        ++indice_texto;
    }
    return arbol;
}

char *leerArchivo(char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");
    char *texto_archivo;
    size_t tam_archivo, bytes_leidos;
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s\n", nombre_archivo);
        return NULL;
    }
    fseek(archivo, 0, SEEK_END);
    tam_archivo = ftell(archivo);
    texto_archivo = (char *) calloc(tam_archivo, sizeof(char));
    rewind(archivo);
    bytes_leidos = fread(texto_archivo, sizeof(char), tam_archivo, archivo);
    if (bytes_leidos == 0) {
        printf("No se pudo leer el archivo %s\n", nombre_archivo);
        return NULL;
    }
    fclose(archivo);
    return texto_archivo;
}

char *obtenerNombreRaiz(char *texto_archivo) {
    char *nombre_raiz = calloc(BUFFER_LENGTH, sizeof(char));
    size_t i = 0;
    while (texto_archivo[i] != '\n' && texto_archivo[i] != '\0') {
        nombre_raiz[i] = texto_archivo[i];
        i++;
    }
    return nombre_raiz;
}

void obtenerNombresNodo(Nombres *contenedor, char *fragmento_texto, size_t tam_fragmento) {
    size_t i = 0;
    size_t tam_texto = strlen(fragmento_texto);
    while (fragmento_texto[i] != '\n' && i < tam_texto) {
        if (fragmento_texto[i] == ':') {
            contenedor->hijo = (char *) calloc(i + 1, sizeof(char));
            strncpy(contenedor->hijo, fragmento_texto, i);
            contenedor->padre = (char *) calloc((tam_fragmento - i), sizeof(char));
            strncpy(contenedor->padre, fragmento_texto + i + 1, tam_fragmento - i - 1);
            return;
        }
        i++;
    }
}

bool esNodoEspecialidades(char *nombre_padre) {
    return strcmp(nombre_padre, NOMBRE_RAIZ) == 0;
}