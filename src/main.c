//Autores: Montoya Morales Luis Antonio,
#include <stdio.h>
#include <stdlib.h>
#include "Constructor.h"
#include <string.h>

#define BUFFER_SIZE 124

//argument list for char*
void vaciarCadenas(char *nombre_alumno, char *entrada_usuario, char *semestre) {
    memset(nombre_alumno, 0, BUFFER_SIZE);
    memset(entrada_usuario, 0, BUFFER_SIZE);
    memset(semestre, 0, BUFFER_SIZE);
}

char *obtenerAbreviacionEspecialidad(char *especialidad) {
    if (strcmp(especialidad, "Ingenieria en Sistemas Computacionales") == 0) {
        return "ISC";
    }
    if (strcmp(especialidad, "Inteligencia Artificial") == 0) {
        return "IA";
    }
    return "N/A";
}

void obtenerSemestreCadena(char *semestre, int semestre_actual, char *Especialidad) {
    sprintf(semestre, "Semestre %d (%s)", semestre_actual, obtenerAbreviacionEspecialidad(Especialidad));
}


void imprimirEspecialidades(Arbol *arbol) {
    struct ListaNodosArbol *especialidades = arbol->raiz->hijos;
    printf("Especialidades disponibles:\n");
    irAlInicioNA(especialidades);
    while (especialidades->actual != NULL) {
        if (especialidades->actual->nodo->estado == NO_COMPLETADO)
            printf("-%s\n", especialidades->actual->nodo->rotulo);
        irAlSiguienteNA(especialidades);
    }
}

NodoArbol *
eleccionEspecialidad(char *nombre_alumno, Arbol *arbol, char *entrada_usuario) {
    NodoArbol *especialidad_elegida;
    char tmp;
    printf("Introduzca su nombre: ");
    scanf("%[^\n]", nombre_alumno);
    printf("Bienvenido %s\n", nombre_alumno);
    imprimirEspecialidades(arbol);
    fflush(stdin);
    memset(entrada_usuario, 0, BUFFER_SIZE);
    scanf("%c", &tmp);
    do {
        printf("Introduzca la especialidad que desea cursar: ");
        scanf("%[^\n]s", entrada_usuario);
        scanf("%c", &tmp);
        especialidad_elegida = buscarNodoConClave(arbol->raiz, entrada_usuario);
        if (especialidad_elegida == NULL) {
            printf("La especialidad introducida no existe\n");
        }
        if (especialidad_elegida->estado == COMPLETADO) {
            printf("La especialidad introducida ya ha sido completada\n");
            especialidad_elegida = NULL;
        }
    } while (especialidad_elegida == NULL);
    return especialidad_elegida;
}

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
    NodoArbol *especialidad_elegida, *materia;
    bool ha_terminado_especialidad = false;
    char nombre_alumno[BUFFER_SIZE];
    char entrada_usuario[BUFFER_SIZE];
    int opcion = 0;
    int semestre_actual = 1;
    char semestre[BUFFER_LENGTH];
    vaciarCadenas(nombre_alumno, entrada_usuario, semestre);
    especialidad_elegida = eleccionEspecialidad(nombre_alumno, arbol, entrada_usuario);
    printf("Especialidad elegida: %s\n", especialidad_elegida->rotulo);
    do {
        printf("1. Confirmar seleccion\n");
        printf("2. Volver a introducir especialidad\n");
        printf("3. Mostrar materias de la especialidad\n");
        printf("4. Salir\n");
        printf("Introduzca una opcion: ");
        scanf("%d", &opcion);
        struct ListaNodosArbol *materias;
        switch (opcion) {
            case 1:
                obtenerSemestreCadena(semestre, semestre_actual, especialidad_elegida->rotulo);
                //introducir materias
                do {
                    ha_terminado_especialidad = especialidadTerminada(especialidad_elegida);
                    char tmp;
                    do {
                        materias = obtenerMateriasDisponibles(arbol, semestre);
                        irAlInicioNA(materias);
                        printf("Materias disponibles:\n");
                        while (materias->actual != NULL) {
                            printf("-%s\n", materias->actual->nodo->rotulo);
                            irAlSiguienteNA(materias);
                        }
                        scanf("%c", &tmp);
                        printf("Introduzca la materia que desea cursar: ");
                        scanf("%[^\n]s", entrada_usuario);
                        materia = buscarNodoConClave(buscarNodoConClave(arbol->raiz, semestre), entrada_usuario);
                        if (materia == NULL) {
                            printf("La materia introducida no existe\n");
                        } else {
                            if (materia->estado == NO_CURSADO) {
                                materia->estado = CURSADO;
                                printf("Materia %s cursada!\n", materia->rotulo);
                            } else {
                                printf("La materia introducida ya ha sido cursada o no se puede cursar\n");
                            }
                        }
                    } while (!seHaCursadoSemestreCompleto(arbol, semestre));
                    buscarNodoConClave(buscarNodoConClave(arbol->raiz, semestre), semestre)->estado = CURSADO;
                    semestre_actual++;
                    memset(semestre, 0, BUFFER_SIZE);
                    obtenerSemestreCadena(semestre, semestre_actual, especialidad_elegida->rotulo);
                    printf("Se ha completado el semestre %d\n", semestre_actual - 1);
                } while (ha_terminado_especialidad);
                printf("Se ha completado la especialidad %s\n", especialidad_elegida->rotulo);
                especialidad_elegida->estado = COMPLETADO;
            case 2:
                especialidad_elegida = eleccionEspecialidad(nombre_alumno, arbol, entrada_usuario);
                break;
            case 3:
                imprimirArbol(especialidad_elegida);
                break;
            case 4:
                return EXIT_SUCCESS;
            default:
                printf("Opcion no valida\n");
                break;
        }
    } while (opcion != 4);
    return EXIT_SUCCESS;
}
