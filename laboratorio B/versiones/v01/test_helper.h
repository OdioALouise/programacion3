#ifndef _TEST_HELPER_H
#define _TEST_HELPER_H

#include "Congreso.h"


void check_asistentes_m (int * solucion, charla * charlas, int n, sala * salas, int m);
/*
'charlas' es un array de tamaño 'n' y 'salas' es un array de tamaño 'm'.
Comprueba que 'solucion' es una solución válida para max_asistentes_m dados
los parámetros. Imprime la cantidad de asistentes de 'solucion'.
*/

#endif /* TEST_HELPER */
