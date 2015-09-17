#include "ListaOrd.h"
#include "tipoT.h"
#include <string.h>
#include <stdio.h>

struct nodox
	{
		tipoT dato;
		nodox * sig;
	};

struct AuxListaOrd
	{
		nodox* primero;
		nodox* actual;
		nodox* ultimo;
	};

/*  Devuelve en 'l' la lista vacía. */ 
void crearLista (ListaOrd &l)
{
	l = new AuxListaOrd;
	l->primero = NULL;
	l->actual = NULL;
	l->ultimo = NULL;
}

/*  Inserta 't', manteniendo el orden, en la lista 'l', si 't' no está en 'l'.
    En otro caso no hace nada. */
void insLista (tipoT t, ListaOrd &l)
{


	bool entra;
	entra = true;
	
	nodox * aux;
	nodox * elanterior;
	aux = new nodox;
	aux->dato = t;
	aux->sig = NULL;


	if (!esVaciaLista (l)) 
		{

			if (esMenor (t ,l->primero->dato))
			{
				entra = false;
				aux->sig = l->primero;
				l->primero = aux;
				l->actual = l->primero;
			}

			if (esMayor (t, l->ultimo->dato))
			{
				entra = false;
				l->ultimo->sig = aux;
				l->ultimo = aux;
			}

			if (entra == true)
			{
				nodox * actual;
				actual=l->primero;
				while (esMenor(actual->dato,t))
				{
					elanterior = actual;
					actual=actual->sig;
				}
				elanterior->sig = aux;
				aux->sig = actual;
			}
		}
	else
		{
			l->primero = aux;
			l->ultimo = aux;
			l->actual = aux;
		}
}

/*  Devuelve 'true' si 'l' es vacía, 'false' en otro caso. */
bool esVaciaLista (ListaOrd l)
{
	if (l->primero == NULL)
		return true;
	else
		return false;
}


/*  Precondición: '! esVaciaLista (l)'.
    Devuelve el valor del primer elemento de 'l'. */
tipoT primeroLista (ListaOrd l)
{
	return l->primero->dato;
}

/*  Precondición: '! esVaciaLista (l)'.
    Cambia 'l' a su resto.   */
void restoLista (ListaOrd & l)
{
	l->primero = l->primero->sig;
}

/*  Libera toda la memoria ocupada por l. */
void destruirLista (ListaOrd &l)
{
	if (!esVaciaLista(l))
	{		
		nodox * ElTermineitor;
		
		while (l->ultimo != NULL) 
		{
			ElTermineitor = l->primero;
			if(l->primero != l->ultimo)
				restoLista(l);
			else 
			{
				l->primero = NULL;
				l->actual = NULL;
				l->ultimo = NULL;
			}
			delete ElTermineitor;
		}
		delete l;
	}
}


void imprimirLista (ListaOrd &l)
{
	int contador=0;
	contador++;
	nodox * actual;
	actual=l->primero;
	while (actual != NULL) 
	{
		printf("\t El valor en la posicion %d \t es %d \n", contador, actual->dato);
		contador++;
		actual=actual->sig;
	}
}


void irActual (ListaOrd & l)
{
	l->primero = l->actual;
}



