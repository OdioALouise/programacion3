/*
Depósito de artículos representados por elementos de tipo tipoT.

Laboratorio de Programación 3.
InCo-Fing-UDELAR
*/

#ifndef _DEPOSITO_H
#define _DEPOSITO_H

#include "ListaOrd.h"
#include "Pila.h"
#include "tipoT.h"

struct AuxDeposito;
typedef AuxDeposito * Deposito;

Deposito crearDeposito (unsigned int cantidad_articulos);
/*  Devuelve un depósito con 'cantidad_articulos' artículos, sin referencias. 
    Para cada i, '0 <= i < cantidad_articulos' hay un artículo 'a' que cumple
    'hash (a) == i'. */

void agregarReferencia (Deposito d, tipoT a1, tipoT a2);
/*  Precondiciones:
        1. 0 <= 'hash (a1)' < cantidad de artículos de 'd'.
        2. 0 <= 'hash (a2)' < cantidad de artículos de 'd'.
    Establece en 'd' una referencia desde 'a1' hacia 'a2'. */

ListaOrd referencias (Deposito d, tipoT a);
/*  Precondición: 0 <= 'hash (a)' < cantidad de artículos de 'd'.
    Devuelve la lista ordenada de las referencias de 'a'.
    La lista devuelta no debe compartir memoria con 'd'. */

tipoT elemento (Deposito d, unsigned int pos);
/*  Precondición: 0 <= 'pos' < cantidad de artículos de 'd'.
    Devuelve el elemento x que cumple 'hash (x)' = 'pos'.   */

unsigned int cantidadArticulos (Deposito d);
/*  Devuelve la cantidad de artículos de 'd'. */

Pila dfsPostOrden (Deposito d);
/*  Devuelve una pila con todos los artículos de 'd' tras una recorrida dfs.
    Los apila en postorden. Cuando haya que decidir entre más de un artículo a
    visitar, se debe elegir el menor. */

Deposito transpuesto (Deposito d);
/*  Devuelve un depósito igual a 'd' pero con las referencias
    en sentido inverso. */

void nuevosAccesibles (Deposito d, tipoT a, unsigned int id,
                       unsigned int * &agrupamientos);
/*  Precondiciones:
        1. El tamaño de 'agrupamientos' es igual a la cantidad de artículos de
           'd'.
        2. 'agrupamientos [hash (a)] == id'.

    El valor de 'agrupamientos [i]' es: el identificador del agrupamiento
    al que se ha asignado el artículo 'x' que cumple 'hash (x) == i', o
    USHRT_MAX si 'x' todavía no ha sido asignado a ningún agrupamiento.

    Modifica 'agrupamientos' asignando 'id' a los artículos que cumplen todas
    las siguientes condiciones:
        a) todavía no se les ha asignado agrupamiento;
        b) son accesibles desde 'a';
        c) el acceso desde 'a' debe poder hacerse sin seguir referencias a
           través de artículos a los que ya se había asignado agrupamiento antes
           de la invocación. */

void destruirDeposito (Deposito &d);
/*  Libera la memoria asignada a d. */

#endif /* _DEPOSITO_H */
