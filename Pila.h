/*
Pila acotada de elementos de tipo tipoT.

Laboratorio de Programación 3.
InCo-Fing-UDELAR
*/

#ifndef _PILA_H
#define _PILA_H

#include "tipoT.h"


struct AuxPila;
typedef AuxPila* Pila;

void crearPila (int cota, Pila &p);
/*  Devuelve en 'p' la pila vacía, que podrá contener hasta 'cota' elementos. */

bool esVaciaPila (Pila p);
/*  Devuelve 'true' si 'p' es vacía, 'false' en otro caso. */

bool esLlenaPila (Pila p);
/*  Devuelve 'true' si 'p' tiene cota elementos, donde cota es el valor del
    parámetro pasado en crearPila, 'false' en otro caso. */

void apilar (tipoT t, Pila &p);
/*  Si '!esLlenaPila (p)' inserta 't' en la cima de 'p', en otro caso no hace
    nada. */

tipoT cima (Pila p);
/*  Precondición: '! esVaciaPila (p)'.
    Devuelve la cima de 'p'. */

void desapilar (Pila &p);
/*  Precondición: '! esVaciaPila (p)'.
    Remueve la cima de 'p'. */

void destruirPila (Pila &p);
/*  Libera toda la memoria ocupada por 'p'. */

#endif /* _PILA_H */
