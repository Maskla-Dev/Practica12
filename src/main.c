#include <stdio.h>
#include <stdlib.h>
#include "Constructor.h"
#include <string.h>

#define BUFFER_SIZE 124

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No se han introducido argumentos\n");
        return EXIT_FAILURE;
    }
    Arbol *arbol = construirArbol(argv[1]);
    if (arbol == NULL) {
        printf("No se pudo construir el arbol\n");
        return EXIT_FAILURE;
    }
    imprimirArbol(arbol->raiz);
    NodoArbol *especialidad_elegida;
    bool ha_terminado_especialidad = false;
    char nombre_alumno[BUFFER_SIZE];
    char entrada_usuario[BUFFER_SIZE];
    memset(nombre_alumno, 0, BUFFER_SIZE);
    memset(entrada_usuario, 0, BUFFER_SIZE);
    //Menu de seleccion especialidad y datos alumno
    /**
     * @TODO: Capturar el nombre del alumno
     * @TODO: Capturar las especialidades disponibles (buscarlas en el arbol nodos cuyo tipo sea ESPECIALIDAD y estado sea NO_COMPLETADO y mostrarlas)
     * @TODO: Una vez capturada se valida que su entrada coincida exactamente con alguna especialidad existente, si no se le pide que la vuelva a introducir
     * @TODO: Si la especialidad es correcta, el alumno tendra que seleccionar cualquiera de estas opciones: 1. Confirmar seleccion, 2. Volver a introducir especialidad, 3. Mostrar materias de la especialidad, 4. Salir
     */
    while (!ha_terminado_especialidad) {
        //Menu principal
        /**
         * @TODO: Mostrar las materias disponibles
         * @TODO: Pedir introducir un minimo de 4 (si las materias disponibles son mayor a 4) y un maximo de 7 (si no estan en el rango, pedir que las vuelva a introducir)
         * @TODO: Una vez introducidas, el alumno podra elegir entre 1. Confirmar seleccion, 2. Volver a introducir materias, 3. Mostrar materias seleccionadas, 4. Quitar una materia, 5.Mostrar arbol completo, 6. Salir
         * @TODO: Validar que las materias introducidas existan en el arbol, que no se repitan y que puedan cursarse (estado NO_CURSADO o sin hijos)
         * @TODO: Si se confirma la seleccion, se cambia el estado de las materias a CURSADO
         */
    }
    return EXIT_SUCCESS;
}
