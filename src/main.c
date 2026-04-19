/**
 * @file main.c
 * @brief Programa principal para la prueba del módulo alumno.
 *
 * Este archivo cumple con la consigna de contener únicamente la función main,
 * actuando como cliente del Tipo de Dato Abstracto (ADT) Alumno.
 * * @copyright Copyright (c) 2026 [Gerardo Agustin Diaz].
 * Todos los derechos reservados. Licencia MIT.
 */

/**
 * @mainpage Laboratorio 3 - Electrónica IV
 *
 * @section intro_sec Introducción
 * Este proyecto implementa un Tipo de Dato Abstracto (ADT) para gestionar
 * la información de un alumno y serializarla a formato JSON.
 * Se enfoca en el encapsulamiento de datos, donde la estructura interna
 * del alumno es privada y solo accesible a través de su interfaz pública.
 *
 * @section features_sec Características
 * - Separación de interfaz (.h) e implementación (.c).
 * - Gestión de memoria dinámica para la creación de objetos.
 * - Robustez ante desbordamientos de buffer mediante macros de control.
 * - Documentación automatizada con Doxygen.
 *
 * @section license_sec Licencia
 * Este software se distribuye bajo la Licencia MIT.
 */

#include <stdio.h>
#include "alumno.h"

/**
 * @brief Función principal del programa.
 *
 * Coordina la creación de una instancia de alumno, solicita su
 * serialización en formato JSON y muestra el resultado por la salida
 * estándar.
 *
 * @return int Retorna 0 si la ejecución fue exitosa, o -1 si hubo errores.
 */

int main(void) {
    /* 1. Intentar crear la instancia del alumno usando el ADT */
    alumno_t yo = AlumnoCrear("Diaz", "Gerardo Agustin", 40700105);

    /*Verifica que se creó correctamente*/
    if (yo == NULL) {
        printf("Error: No se pudo asignar memoria para el alumno.\n");
        return -1;
    }

    /* 2. Preparar el buffer para la serialización */
    char buffer[256];

    /* 3. Ejecutar la serialización */
    int caracteres_escritos = AlumnoSerializar(yo, buffer, sizeof(buffer));

    /* 4. Procesar el resultado */
    if (caracteres_escritos >= 0) {
        printf("Datos del alumno: \n%s\n", buffer);
        printf("Total de caracteres: %d\n", caracteres_escritos);
    } else {
        printf(
            "Error: El buffer es demasiado chico para serializar los datos.\n");
    }

    return 0;
}
