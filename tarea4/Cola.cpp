
#include "tipoT.h"
#include "string.h"

struct nodoz
	{
		tipoT dato;
		nodoz * sig;
	};

struct AuxCola
	{
		nodoz* primero;
		nodoz* ultimo;
	};

void crearCola (Cola & c);
/*  Devuelve en 'c' la cola vacía. */
{
	c = new AuxCola;
	c->primero = NULL;
	c->ultimo = NULL;
}

bool esVaciaCola (Cola c);
/*  Devuelve 'true' si 'c' es vacía, 'false' en otro caso. */
{
	if (c->primero == NULL)
		return true;
	else
		return false;
}

void encolar (tipoT t, Cola &c);
/*  Agrega el elemento 't' al final de 'c'. */
{
	nodoz * aux;
	aux = new nodoz;
	aux->dato = t;
	aux->sig = NULL;

	if (!esVaciaCola(c))
	{
		c->ultimo->sig = aux;
		c->ultimo = aux;
	}
	else
	{
		c->ultimo = aux;
		c-> primero = aux;
	}
}

tipoT frente (Cola c);
/*  Precondición: '! esVaciaCola (c)'.
    Devuelve el primer elemento de 'c'*/
{
	return c->primero->dato;
}

void desencolar (Cola &c);
/*  Precondición: '! esVaciaCola (c)'.
    Remueve el primer elemento de 'c'. */
{
	nodoz * ElTermineitor;
	ElTermineitor = c->primero;
	c->primero = c->primero->sig;
	delete ElTermineitor;

	if (c->primero == NULL)
		c->ultimo = NULL;
}

void destruirCola (Cola &c);
/*  Libera toda la memoria ocupada por 'c'. */
{
	while (!esVaciaCola (c))
	{
		desencolar(c);
	}
	delete c;
}
