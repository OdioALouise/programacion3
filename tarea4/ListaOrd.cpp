
#include "tipoT.h"
#include "string.h"

struct nodox
	{
		tipoT dato;
		nodox * sig;
	};

struct AuxListOrd
	{
		nodox* primero;
		nodox* ultimo;
	};
void crearLista (ListaOrd &l);
/*  Devuelve en 'l' la lista vacía. */ 
{
	l = new AuxListOrd;
	l->primero = NULL;
	l->ultimo = NULL;
}

void insLista (tipoT t, ListaOrd &l);
/*  Inserta 't', manteniendo el orden, en la lista 'l', si 't' no está en 'l'.
    En otro caso no hace nada. */
{
	bool * entra;
	entra = true;
	
	AuxListOrd * m;
	nodox * aux;
	nodox * elanterior;
	aux = new nodox;
	aux->dato = t;
	aux->sig = NULL;

	if (!esVaciaLista (l)) 
		{
			m = l;

			if (esMenor (t ,m->primero->dato))
			{
				entra = false;
				aux->sig = m->primero;
				m->primero = aux;
			}

			if (esMayor (t, m->ultimo->dato))
			{
				entra = false;
				m->ultimo->sig = aux;
				ultimo = aux;
			}

			if (entra == true)
			{
				while (esMenor(primeroLista(m),t))
				{
					elanterior = m->primero;
					restoLista(m);
				}
				elanterior->sig = aux;
				aux->sig = primeroLista(m);
			}
		}
	else
		{
			l->primero = aux;
			l->ultimo = aux;
		}
}

bool esVaciaLista (ListaOrd l);
/*  Devuelve 'true' si 'l' es vacía, 'false' en otro caso. */
{
	if (l->primero == NULL)
		return true;
	else
		return false;
}


tipoT primeroLista (ListaOrd l);
/*  Precondición: '! esVaciaLista (l)'.
    Devuelve el valor del primer elemento de 'l'. */
{
	return l->primero->dato;
}

void restoLista (ListaOrd & l);
/*  Precondición: '! esVaciaLista (l)'.
    Cambia 'l' a su resto.   */
{
	l->primero = l->primero->sig;
}

void destruirLista (ListaOrd &l);
/*  Libera toda la memoria ocupada por l. */
{
	if (!esVaciaLista(l))
	{		
		nodox * ElTermineitor;
		
		while (l->ultimo <> NULL) 
		{
			ElTermineitor = l->primero;
			if l->primero <> l->ultimo 
				restoLista(l);
			else 
			{
				l->primero = NULL;
				l->ultimo = NULL;
			}
			delete ElTermineitor;
		}
		delete l;
	}
}


















