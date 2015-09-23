#include "Cola.h"
#include <string.h>
#include <stdio.h>

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

/*  Devuelve en 'c' la cola vacía. */
void crearCola (Cola & c)
{
	c = new AuxCola;
	c->primero = NULL;
	c->ultimo = NULL;
}

/*  Devuelve 'true' si 'c' es vacía, 'false' en otro caso. */
bool esVaciaCola (Cola c)
{
	if (c->primero == NULL)
		return true;
	else
		return false;
}

/*  Agrega el elemento 't' al final de 'c'. */
void encolar (tipoT t, Cola &c)
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

/*  Precondición: '! esVaciaCola (c)'.
    Devuelve el primer elemento de 'c'*/
tipoT frente (Cola c)
{
	return c->primero->dato;
}

/*  Precondición: '! esVaciaCola (c)'.
    Remueve el primer elemento de 'c'. */
void desencolar (Cola &c)
{
	nodoz * ElTermineitor;
	ElTermineitor = c->primero;
	c->primero = c->primero->sig;
	delete ElTermineitor;

	if (c->primero == NULL)
		c->ultimo = NULL;
}

/*  Libera toda la memoria ocupada por 'c'. */
void destruirCola (Cola &c)
{
	while (!esVaciaCola (c))
	{
		desencolar(c);
	}
	delete c;
}



void imprimir (Cola &c)
{
	tipoT contador =1;

	while (!esVaciaCola (c))
	{
		printf("El valor en la posicion %d \t %d \n", contador, frente(c));
		desencolar(c);
		contador++;
	}
 
}
