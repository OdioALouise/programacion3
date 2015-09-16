#include <string.h>
#include <stdio.h>
#include "Deposito.h"
#include "ListaOrd.h"

void imprimirLista (ListaOrd &l);
void imprimirPila (Pila &p);

struct nodo{
	ListaOrd l;
	tipoT valor;
	nodo *siguiente;
};

struct AuxDeposito{
	nodo *tabla;
	unsigned int cantidad_articulos;
	int * marcas;
};



/*  Devuelve un depósito con 'cantidad_articulos' artículos, sin referencias. */
Deposito crearDeposito (unsigned int cantidad_articulos){
	Deposito deposito= new AuxDeposito;
	deposito->cantidad_articulos=cantidad_articulos;
	deposito->tabla=new nodo;
	deposito->marcas=new int[cantidad_articulos];

	for(int i=0; i<cantidad_articulos; i++){

		nodo* n=new nodo;
		crearLista(n->l);
		n->valor=cantidad_articulos-i;
		n->siguiente=NULL;


		if(i==0){

			deposito->tabla=n;
		}else{
			nodo* aux;
			aux=deposito->tabla;
			n->siguiente=aux;
			deposito->tabla=n;

		}

		deposito->marcas[i]=0;

	}

	return deposito;
}





/*  Precondiciones:
        1. 0 <= 'hash (a1)' < cantidad de artículos de 'd'.
        2. 0 <= 'hash (a2)' < cantidad de artículos de 'd'.
    Establece en 'd' una referencia desde 'a1' hacia 'a2'. */
void agregarReferencia (Deposito d, tipoT a1, tipoT a2){
	nodo* actual;
	actual=d->tabla;

	for(int i=1; i<a1; i++){
		actual=actual->siguiente;
	}
	insLista (a2, actual->l);
}

/*  Precondición: 0 <= 'hash (a)' < cantidad de artículos de 'd'.
    Devuelve la lista ordenada de las referencias de 'a'. */
ListaOrd referencias (Deposito d, tipoT a){

	nodo * actual;
	actual=d->tabla;

	for(int i=1; i<a; i++){
		actual=actual->siguiente;
	}	

	return actual->l;
	
}

/*  Precondición: 0 <= 'pos' < cantidad de artículos de 'd'.
    Devuelve el elemento x que cumple 'hash (x)' = 'pos'.   */
tipoT elemento (Deposito d, unsigned int pos){
	nodo * actual;
	actual=d->tabla;

	for(int i=1; i<pos; i++){
		actual=actual->siguiente;
	}	

	return actual->valor;
}


/*  Devuelve la cantidad de artículos de 'd'. */
unsigned int cantidadArticulos (Deposito d){
	return d->cantidad_articulos;
}

/*  Devuelve una pila con todos los artículos de 'd' tras una recorrida dfs.
    Los apila en postorden. Cuando haya que decidir entre más de un artículo a
    visitar, se debe elegir el menor. */
void dfs(tipoT valor, Deposito d, Pila &p){

	d->marcas[valor]=1;

	ListaOrd l;
	l=referencias (d, valor);
	
	while(!esVaciaLista(l))
	{
		if( d->marcas[primeroLista(l)] == 0){
			d->marcas[primeroLista(l)]=1;
			dfs(primeroLista(l), d, p);
		}
		restoLista(l);
	}

	apilar(valor, p);

}


Pila dfsPostOrden (Deposito d){

	nodo * actual;
	actual=d->tabla;

	Pila p;
	crearPila(d->cantidad_articulos, p);

	int contador=1;

	while(actual!=NULL){

	//printf("Se marco %d  el valor %d tenia marca %d \n", contador, actual->valor, d->marcas[actual->valor]);
	
	if(d->marcas[actual->valor]==0)
		dfs(actual->valor, d, p);
	
	actual=actual->siguiente;
	contador++;
	}

	return p;

}




void imprimirDeposito (Deposito &l)
{
	int contador=0;
	contador++;
	nodo * actual;
	actual=l->tabla;
	while (actual != NULL) 
	{
		printf("La lista para la posicion %d con el valor %d \n", contador, actual->valor);
		imprimirLista(actual->l);
		contador++;
		actual=actual->siguiente;
	}
}








