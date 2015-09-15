/*
Cola de elementos de tipo tipoT.

Laboratorio de Programación 3.
InCo-Fing-UDELAR
*/

#ifndef _COLA_H
#define _COLA_H

#include "tipoT.h"

struct AuxCola;
typedef AuxCola* Cola;

void crearCola (Cola & c);
/*  Devuelve en 'c' la cola vacía. */

bool esVaciaCola (Cola c);
/*  Devuelve 'true' si 'c' es vacía, 'false' en otro caso. */

void encolar (tipoT t, Cola &c);
/*  Agrega el elemento 't' al final de 'c'. */

tipoT frente (Cola c);
/*  Precondición: '! esVaciaCola (c)'.
    Devuelve el primer elemento de 'c'*/

void desencolar (Cola &c);
/*  Precondición: '! esVaciaCola (c)'.
    Remueve el primer elemento de 'c'. */

void destruirCola (Cola &c);
/*  Libera toda la memoria ocupada por 'c'. */

#endif /* _COLA_H */
