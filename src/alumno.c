/**
 * @file alumno.c
 * @brief Implementación del módulo de alumno (ADT).
 *
 * Este archivo contiene las funciones internas y públicas necesarias para
 * gestionar la memoria de un alumno y convertir su información en una
 * cadena de texto con formato JSON válido.
 *
 * @copyright Copyright (c) 2026 [Gerardo Agustin Diaz].
 * Todos los derechos reservados. Licencia MIT.
 */

#include "alumno.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> /*Libreria para malloc*/

/**
 * @brief Macro para comprobar el espacio restante en el buffer y actualizar
 * contadores.
 *
 * Si la operación de escritura falló o el espacio no es suficiente, fuerza
 * a la función invocadora a retornar -1. Si tiene éxito, descuenta el
 * espacio utilizado y avanza el puntero.
 *
 * @param res Resultado de la función snprintf (caracteres a escribir).
 * @param disp Variable que almacena el espacio disponible en el buffer.
 * @param ptr Puntero a la posición actual dentro del buffer de caracteres.
 */

#define GESTIONAR_ESPACIO(res, disp, ptr)                                      \
    do {                                                                       \
        if ((res) < 0 || (res) >= (disp))                                      \
            return -1;                                                         \
        (disp) -= (res);                                                       \
        (ptr) += (res);                                                        \
    } while (0)

/**
 * @brief Estructura privada que contiene la información personal de un alumno.
 *
 * Al estar definida en el archivo .c, sus atributos quedan ocultos
 * para el resto del programa, cumpliendo con el patrón de Tipo de Dato
 * Abstracto.
 */

struct alumno_s {
    char nombre[30];    /**< Nombre del alumno */
    char apellido[30];  /**< Apellido del alumno */
    uint32_t documento; /**< Documento del alumno */
};

/**
 * @brief Serializa un campo de texto y su valor en formato JSON.
 *
 * Genera una subcadena con el formato "campo":"valor".
 *
 * @param campo Puntero a la cadena que representa la clave del JSON.
 * @param valor Puntero a la cadena que representa el contenido del texto.
 * @param cadena Puntero al buffer donde se guardará el resultado parcial.
 * @param espacio Cantidad de bytes disponibles en el buffer.
 * @return int Cantidad de caracteres que se intentaron escribir.
 */

static int SerializarTexto(const char *campo, const char *valor, char *cadena,
                           int espacio) {

    return snprintf(cadena, espacio, "\"%s\":\"%s\"", campo, valor);
}

/**
 * @brief Serializa un campo numérico y su valor en formato JSON.
 *
 * Genera una subcadena con el formato "campo":valor.
 *
 * @param campo Puntero a la cadena que representa la clave del JSON.
 * @param valor Valor numérico entero a serializar.
 * @param cadena Puntero al buffer donde se guardará el resultado parcial.
 * @param espacio Cantidad de bytes disponibles en el buffer.
 * @return int Cantidad de caracteres que se intentaron escribir.
 */

static int SerializarNumero(const char *campo, int valor, char *cadena,
                            int espacio) {

    return snprintf(cadena, espacio, "\"%s\":%d", campo, valor);
}

/**
 * @brief Crea un nuevo alumno reservando memoria dinámicamente.
 *
 * @param apellido Cadena de caracteres con el apellido del alumno.
 * @param nombre Cadena de caracteres con el nombre del alumno.
 * @param documento Número de documento del alumno.
 * @return alumno_t Puntero a la estructura asignada, o NULL si falló la
 * asignación.
 */

alumno_t AlumnoCrear(const char *apellido, const char *nombre,
                     uint32_t documento) {
    /*Reservar memoria dinamicamente para la estructura*/
    alumno_t nuevo_alumno = malloc(sizeof(struct alumno_s));

    if (nuevo_alumno != NULL) {

        strncpy(nuevo_alumno->apellido, apellido,
                sizeof(nuevo_alumno->apellido) - 1);
        nuevo_alumno->apellido[sizeof(nuevo_alumno->apellido) - 1] = '\0';

        strncpy(nuevo_alumno->nombre, nombre, sizeof(nuevo_alumno->nombre) - 1);
        nuevo_alumno->nombre[sizeof(nuevo_alumno->nombre) - 1] = '\0';

        nuevo_alumno->documento = documento;
    }

    return nuevo_alumno;
}

/**
 * @brief Serializa los datos completos de un alumno en formato JSON.
 *
 * Construye un objeto JSON con los atributos del alumno proporcionado.
 * Realiza verificaciones continuas para evitar desbordamientos de memoria
 * utilizando la macro GESTIONAR_ESPACIO.
 *
 * @param alumno Puntero a la estructura opaca con los datos del alumno.
 * @param cadena Puntero al buffer donde se almacenará el JSON resultante.
 * @param espacio Capacidad total del buffer en bytes.
 * @return int Longitud total de la cadena generada, o -1 si el espacio es
 * insuficiente.
 */

int AlumnoSerializar(alumno_t alumno, char *cadena, int espacio) {
    int disponibles = espacio;
    int resultado;
    char *puntero = cadena;

    // Abrir el objeto JSON
    resultado = snprintf(puntero, disponibles, "{");
    GESTIONAR_ESPACIO(resultado, disponibles, puntero);

    // Serializar Nombre
    resultado = SerializarTexto("nombre", alumno->nombre, puntero, disponibles);
    GESTIONAR_ESPACIO(resultado, disponibles, puntero);

    // Separador
    resultado = snprintf(puntero, disponibles, ",");
    GESTIONAR_ESPACIO(resultado, disponibles, puntero);

    // Serializar Apellido
    resultado =
        SerializarTexto("apellido", alumno->apellido, puntero, disponibles);
    GESTIONAR_ESPACIO(resultado, disponibles, puntero);

    // Separador
    resultado = snprintf(puntero, disponibles, ",");
    GESTIONAR_ESPACIO(resultado, disponibles, puntero);

    // Serializar Documento
    resultado =
        SerializarNumero("documento", alumno->documento, puntero, disponibles);
    GESTIONAR_ESPACIO(resultado, disponibles, puntero);

    // Cerrar el objeto JSON
    resultado = snprintf(puntero, disponibles, "}");
    if (resultado < 0 || resultado >= disponibles)
        return -1;
    disponibles -= resultado;

    return espacio - disponibles;
}
