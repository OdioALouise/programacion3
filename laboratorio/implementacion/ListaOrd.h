/*
Lista de elementos de tipo tipoT ordenada de manera creciente, sin elementos
repetidos.

Laboratorio de Programación 3.
InCo-Fing-UDELAR
*/

#ifndef _LISTAORD_H
#define _LISTAORD_H

#include "tipoT.h"

struct AuxListaOrd;
typedef AuxListaOrd* ListaOrd;

void crearLista (ListaOrd &l);
/*  Devuelve en 'l' la lista vacía. */

void insLista (tipoT t, ListaOrd &l);
/*  Inserta 't', manteniendo el orden, en la lista 'l', si 't' no está en 'l'.
    En otro caso no hace nada. */

bool esVaciaLista (ListaOrd l);
/*  Devuelve 'true' si 'l' es vacía, 'false' en otro caso. */

tipoT primeroLista (ListaOrd l);
/*  Precondición: '! esVaciaLista (l)'.
    Devuelve el valor del primer elemento de 'l'. */

void restoLista (ListaOrd & l);
/*  Precondición: '! esVaciaLista (l)'.
    Cambia 'l' a su resto.   */

void destruirLista (ListaOrd &l);
/*  Libera toda la memoria ocupada por l. */

#endif /* _LISTAORD_H */
