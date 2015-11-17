#include <assert.h>
#include <stdio.h>

#include "Congreso.h"
#include "test_helper.h"

/*
Lee desde la entrada estandar los datos de las charlas y las salas.
Los ejecuta y muestra resultados en la salida.
El formato de la entrada es


cantidadCharlas
<charlas>
cantidadSalas
<salas>


<charlas>
tiene una linea por cada charla con la forma
inicio-fin-asistentes

donde inicio, fin y asistentes son enteros no negativos y fin > inicio

<salas>
tiene una linea por cada sala con la forma
inicio-fin

donde inicio y fin son enteros no negativos y fin > inicio

*/

void imprimir (int *solucion, int n)
{
    for (int i = 0; i < n; i++) printf ("%d ", solucion[i]);
    printf ("\n");
}

int main ()
{
    int res;

    int cant_charlas;
    scanf("%i", &cant_charlas);
    charla * charlas = new charla [cant_charlas];
    for (int i = 0; i < cant_charlas; i++)
    {
        res = scanf("%i - %i -%i", &charlas[i].inicio, &charlas[i].fin, &charlas[i].asistentes);
        assert (res == 3);
        assert (charlas[i].inicio < charlas[i].fin);
    }

    int cant_salas;
    scanf("%i", &cant_salas);
    sala * salas = new sala [cant_salas];
    for (int i = 0; i < cant_salas; i++)
    {
        res = scanf("%i - %i", &salas[i].inicio, &salas[i].fin);
        assert (res == 2);
        assert (salas[i].inicio < salas[i].fin);
    }



    int * solucion_i = max_asistentes_m (charlas, cant_charlas, salas, cant_salas);
    check_asistentes_m (solucion_i, charlas, cant_charlas, salas, cant_salas);
    //imprimir (solucion_i, cant_charlas);

    return 0;
}
