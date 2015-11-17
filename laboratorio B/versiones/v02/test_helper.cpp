#include "test_helper.h"
#include <stdio.h>

bool hay_solapamiento (bool * solucion, charla * charlas, int n)
{
    bool solapa = false;
    for (int i = 0; ((i < n - 1) && (! solapa)); i++)
    if (solucion [i])
        for (int j = i + 1; ((j < n) && (! solapa)); j++)
            if (solucion [j] && (charlas[i].fin > charlas[j].inicio) && (charlas[j].fin > charlas[i].inicio) )
                solapa = true;

    return solapa;
} // hay_solapamiento

bool hay_solapamiento_m (int * solucion, charla * charlas, int n, int m)
{
    bool solapa = false;

    // vector para pasar a la fucnion usada para el caso de una sala
    bool * solucion_h = new bool [n];

    for (int i = 0; (i < m) && (!solapa); i++)
    {
        for (int j = 0; j < n; j++)
        {
            solucion_h [j] = solucion[j] == i;
        }
        solapa = hay_solapamiento (solucion_h, charlas, n);
    }

    delete [] solucion_h;
    return solapa;
} // hay_solapamiento_m

bool hay_desborde_m  (int * solucion, charla * charlas, int n, sala * salas, int m)
// devuelve true si alguna charla es desarrollada a una sala con un intervalo que no contiene al de la tarea
{
    bool desborde = false;

    for (int i =0; ((i < n) && (! desborde)); i++)
    {
        if ( (solucion[i] != -1)
             &&  ((charlas[i].inicio < salas[solucion[i]].inicio)
                  || (charlas[i].fin > salas[solucion[i]].fin)))
            desborde = true;
    }

    return desborde;
} // hay_desborde_m

int asistentes_total_m (int * solucion, charla * charlas, int n)
{
    int result = 0;
    for (int i = 0; i < n; i++)
        if (solucion[i] >= 0) result += charlas[i].asistentes;
    return result;
} // asistentes_total_m

void check_asistentes_m (int * solucion, charla * charlas, int n, sala * salas, int m)
{
    printf ("Solucion %s. asistentes: %d. \n", (hay_solapamiento_m (solucion, charlas, n, m)) || (hay_desborde_m (solucion,
                                                                                                                  charlas, n,
                                                                                                                  salas, m))?"NO-Valida":"Valida", asistentes_total_m (solucion,
                                                                                                                                                                                      charlas, n));
}
