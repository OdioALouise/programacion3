/*
Tipo genérico.
En la actual versión se implementa con enteros no negativos.

Laboratorio de Programación 3.
InCo-Fing-UDELAR
*/

#ifndef _TIPO_T
#define _TIPO_T

typedef unsigned int tipoT;

bool esMayor (tipoT t1, tipoT t2);
/*  Devuelve 'true' si 't1' es mayor que 't2', 'false' en otro caso. */

bool esMenor (tipoT t1, tipoT t2);
/*  Devuelve 'true' si 't1' es menor que 't2', 'false' en otro caso. */

bool esIgual (tipoT t1, tipoT t2);
/*  Devuelve 'true' si 't1' es igual que 't2', 'false' en otro caso. */

/*   NUEVA   */
unsigned int hash (tipoT t);
/*  Devuelve un entero no negativo que representa la posición en un arreglo en
    el que debe alojarse 't'. En la actual versión de tipoT (unsigned int)
    devuelve 't'. */

/*   NUEVA   */
tipoT stringAtipoT (char * string);
/*  Devuelve la conversión de 'string' en tipoT. */

/*   NUEVA   */
char* tipoTAstring (tipoT t);
/*  Devuelve la conversión de 't' a string. */

#endif /* _TIPO_T */
