#include <stdio.h>
#include "tipoT.h"
#include "Pila.h"
#include "ListaOrd.h"

 

int main(){

	ListaOrd l;
	crearLista(l);
	insLista(0, l);
	insLista(10, l);
	insLista(5, l);
	insLista(5, l);
	insLista(10, l);
	insLista(10, l);
	insLista(10, l);
	insLista(0, l);
	insLista(11, l);

 

	return 0;
}
