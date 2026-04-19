/**
 * @file alumno.h
 * @brief Interfaz del módulo de alumno (ADT).
 *
 * Define las funciones públicas para la creación y serialización de alumnos,
 * utilizando un puntero opaco para asegurar el encapsulamiento de los datos.
 *
 * @copyright Copyright (c) 2026 [Gerardo Agustin Diaz].
 * Todos los derechos reservados. Licencia MIT.
 */

#ifndef ALUMNO_H_
#define ALUMNO_H_

#include <stdint.h>

/**
 * @brief Tipo de dato abstracto para representar a un alumno.
 *
 * Los detalles de la estructura alumno_s no son visibles fuera de alumno.c,
 * lo que impide que el programa principal acceda directamente a sus campos.
 */

typedef struct alumno_s *alumno_t;

/**
 * @brief Crea una nueva instancia de un alumno.
 *
 * Reserva la memoria necesaria y asigna los valores iniciales de nombre,
 * apellido y documento.
 *
 * @param apellido Cadena de caracteres con el apellido del alumno.
 * @param nombre Cadena de caracteres con el nombre del alumno.
 * @param documento Número de documento.
 * @return alumno_t Puntero a la estructura creada, o NULL si no se pudo asignar
 * memoria.
 */

alumno_t AlumnoCrear(const char *apellido, const char *nombre,
                     uint32_t documento);

/**
 * @brief Serializa los datos de un alumno en una cadena con formato JSON.
 *
 * Toma los atributos del alumno y genera una representación de texto encerrada
 * entre llaves.
 *
 * @param alumno Puntero a la estructura del alumno a serializar.
 * @param cadena Buffer de caracteres donde se guardará el resultado.
 * @param espacio Cantidad de bytes disponibles en el buffer.
 * @return int Longitud de la cadena generada, o -1 si el espacio es
 * insuficiente.
 */

int AlumnoSerializar(alumno_t alumno, char *cadena, int espacio);

#endif
