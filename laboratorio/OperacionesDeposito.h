/*
Operaciones sobre Depósito.

Laboratorio de Programación 3.
InCo-Fing-UDELAR
*/

#ifndef _OPERACIONES_DEPOSITO_
#define _OPERACIONES_DEPOSITO_

#include "Deposito.h"

unsigned int gradosDeSeparacion (Deposito d, bool * articulos_considerados);
/*  Precondición: el tamaño de 'articulos_considerados' es igual a
    la cantidad de artículos de 'd'.
    Devuelve los grados de separación entre un conjunto de artículos
    considerados. El artículo x es considerado si y sólo si
    'articulos_considerados [hash (x)] == true'. Si uno de los artículos
    considerados es inaccesible desde otro de ellos, se debe retornar USHRT_MAX,
    incluido de limits.h. De haber uno o menos artículos considerados debe
    retornar 0. El acceso entre los artículos sólo se puede hacer siguiendo
    referencias hacia artículos considerados. */

unsigned int * colecciones (Deposito d);
/*  Devuelve las colecciones de 'd', cada una en una lista diferente. La salida
    de esta operación debe ser un arreglo en donde en la posición 'i' se
    encuentra el número de colección a la que pertenece el artículo 'x' que
    cumple 'hash (x) == i'.


# Formato de la salida

    Las colecciones se identifican con enteros de 0 a (k-1), siendo 'k' la
    cantidad de colecciones. Una colección A tiene un identificador menor que
    otra colección B si y sólo si hay un artículo de A que es menor que todos
    los artículos de B.

    Por ejemplo, dado el depósito que tiene los artículos 0, 1, 2 y 3, cuyas
    colecciones son:

    A = {1}
    B = {0, 2}
    C = {3}

    La salida debe ser: 0 1 0 2

    Observar que 0 2 0 1, 1 0 1 2, 1 2 1 0, 2 0 2 1 y 2 1 2 0 también agrupan
    correctamente las colecciones, pero no cumplen la forma de orden solicitada.
*/

#endif /* _OPERACIONES_DEPOSITO_ */
