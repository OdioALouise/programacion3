/*
Programa principal de la tarea A.

Laboratorio de Programación 3.
InCo-FI-UDELAR
-------------------------------------------------------------------------------
Imprime en la salida estándar y lee desde la entrada estándar.
Imprime el mensaje de bienvenida "Tarea A - 2015 - Programación 3."
y lee la información del depósito:
   - Primero lee la cantidad de artículos.
   - Luego para cada uno de ellos, de menor a mayor, lee los artículos hacia los
     que tiene referencias. La línea termina con 'FIN'.

Imprime el prompt '>' y lee los comandos:

Comandos disponibles:

    - salir
    Termina la ejecución e imprime 'FIN'.

    - reiniciar
    Destruye el depósito y lo vuelve a leer.

    - grados [si se considera el artículo 1] ... [si se considera el artículo n]
    Llama a la operación gradosDeSeparacion de OperacionesDeposito
    con los parámetros pasados y devuelve el resultado. Si uno de los artículos
    considerados es inaccesible desde otro de ellos imprime 'INFINITO'.

    - colecciones
    Devuelve el resultado de aplicar la operación colecciones de
    OperacionesDeposito al depósito.

    - transpuesto
    Devuelve el depósito pero con las referencias transpuestas, aplicando la
    operación transpuesto de Deposito.

    - dfs
    Devuelve el resultado de aplicar la operación dfsPostOrden de Deposito.

    - nuevos [numero de articulo] [id] [numero de agrupamiento (si accesible)
    del articulo 1] ... [numero de agrupamiento (si accesible) del articulo n]
    Aplica la operación nuevosAccesibles de Deposito con los parámetros
    pasados y devuelve los nuevos valores del arreglo.
*/

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "OperacionesDeposito.h"

// mensajes de salida
const char MSJ_BIENVENIDA []        = "Tarea A - 2015 - Programacion 3.";
const char MSJ_FINAL []             = "FIN.";
const char MSJ_INACCESIBLE []       = "INFINITO";

// nombres de comandos
const char CMD_SALIR []             = "salir";
const char CMD_REINICIAR []         = "reiniciar";
const char CMD_GRADOS []            = "grados";
const char CMD_COLECCIONES []       = "colecciones";
const char CMD_TRANSPUESTO []       = "transpuesto";
const char CMD_DFS_POST_ORDEN []    = "dfs";
const char CMD_NUEVOS_ACCESIBLES [] = "nuevos";

void leerDeposito (Deposito & d)
{
    unsigned int cantidad_articulos;
    scanf ("%u", &cantidad_articulos);
    d = crearDeposito (cantidad_articulos);

    // leer aristas
    unsigned int v;
    for (unsigned int i = 0; i < cantidad_articulos; i++)
    {
        tipoT u = elemento (d, i);
        bool salir = false;
        while (! salir)
        {
            char referencia [10];
            scanf ("%s", referencia);
            if (strcmp (referencia, "FIN") == 0)
            {
                salir = true;
            }
            else
            {
                v = stringAtipoT (referencia);
                assert ((hash (v) != hash (u)) && (0 <= hash (v))
                        && (hash (v) < cantidad_articulos));
                agregarReferencia (d, u, v);
            }
        }
    }
}

void imprimirDeposito (Deposito d)
{
    printf ("%u\n", cantidadArticulos (d));
    for (unsigned int i = 0; i < cantidadArticulos (d); i++)
    {
        ListaOrd refs_aux = referencias (d, hash (i));
        for (ListaOrd refs = refs_aux; ! esVaciaLista (refs); restoLista (refs))
        {
            char * conv = tipoTAstring (primeroLista (refs));
            printf ("%s ", conv);
            delete [] conv;
        }
        destruirLista (refs_aux);
        printf ("\n");
    }
}
int main ()
{
    printf ("%s\n\n", MSJ_BIENVENIDA);

    char buffer [80];

    Deposito d;
    leerDeposito (d);

    bool salir = false;
    while (! salir)
    {
        printf (">");
        scanf ("%s", buffer);

        if (strcmp (buffer, CMD_SALIR) == 0)
        {
            salir = true;
            printf ("%s\n", MSJ_FINAL);
        }
        else if (strcmp (buffer, CMD_GRADOS) == 0)
        {
            bool * articulos_considerados = new bool [cantidadArticulos (d)];
            for (unsigned int i = 0; i < cantidadArticulos (d); i++)
            {
                char articulo_considerado [2];
                scanf (" %s", articulo_considerado);
                if (strcmp (articulo_considerado, "s") == 0)
                {
                    articulos_considerados [i] = true;
                }
                else if (strcmp (articulo_considerado, "n") == 0)
                {
                    articulos_considerados [i] = false;
                }
                else
                {
                    printf ("%s: Parámetro no reconocido \n",
                            articulo_considerado);
                    exit (1);
                }
            }

            unsigned int grados =
                    gradosDeSeparacion (d, articulos_considerados);
            if (grados == USHRT_MAX)
                printf ("%s\n", MSJ_INACCESIBLE);
            else
                printf ("%u\n", grados);
            delete [] articulos_considerados;
        }
        else if (strcmp (buffer, CMD_COLECCIONES) == 0)
        {
            unsigned int * result = colecciones (d);
            for (unsigned int i = 0; i < cantidadArticulos (d); i++)
            {
                printf ("%d ", result [i]);
            }
            printf ("\n");
            delete [] result;
        }
        else if (strcmp (buffer, CMD_TRANSPUESTO) == 0)
        {
            Deposito t = transpuesto (d);
            imprimirDeposito (t);
            destruirDeposito (t);
        }
        else if (strcmp (buffer, CMD_DFS_POST_ORDEN) == 0)
        {
            Pila pila = dfsPostOrden (d);
            while (! esVaciaPila (pila))
            {
                printf ("%d ", cima (pila));
                desapilar (pila);
            }
            destruirPila (pila);
            printf ("\n");
        }
        else if (strcmp (buffer, CMD_NUEVOS_ACCESIBLES) == 0)
        {
            unsigned int a;
            unsigned int id;
            scanf ("%u %d", &a, &id);

            assert ((0 <= a) && (a < cantidadArticulos (d)));

            unsigned int * agrupamientos =
                    new unsigned int [cantidadArticulos (d)];
            for (unsigned int i = 0; i < cantidadArticulos (d); i++)
            {
                scanf (" %d", &agrupamientos [i]);
            }

            nuevosAccesibles (d, a, id, agrupamientos);

            for (unsigned int i = 0; i < cantidadArticulos (d); i++)
            {
                printf ("%d ", agrupamientos [i]);
            }
            delete [] agrupamientos;
            printf ("\n");
        }
        else if (strcmp (buffer, CMD_REINICIAR) == 0)
        {
            destruirDeposito (d);
            leerDeposito (d);
        }
        else // ERROR
        {
            printf ("%s: Comando no reconocido \n", buffer);
            exit (1);
        }
    }
    destruirDeposito (d);
    return 0;
}
