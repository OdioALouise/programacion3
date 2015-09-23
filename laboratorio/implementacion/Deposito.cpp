#include <string.h>
#include <stdio.h>
#include "Deposito.h"
#include "ListaOrd.h"
#include "Cola.h"


void imprimirLista (ListaOrd &l);
void imprimirPila (Pila &p);
void imprimirDeposito (Deposito &l);
void irActual (ListaOrd & l);
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
		n->valor=cantidad_articulos-i-1;
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

	for(int i=0; i<hash(a1); i++){
		actual=actual->siguiente;
	}
	insLista (a2, actual->l);
}

/*  Precondición: 0 <= 'hash (a)' < cantidad de artículos de 'd'.
    Devuelve la lista ordenada de las referencias de 'a'. */
ListaOrd referencias (Deposito d, tipoT a){

	nodo * actual;
	actual=d->tabla;

	for(int i=0; i<hash(a); i++){
		actual=actual->siguiente;
	}	

	return actual->l;
	
}

/*  Precondición: 0 <= 'pos' < cantidad de artículos de 'd'.
    Devuelve el elemento x que cumple 'hash (x)' = 'pos'.   */
tipoT elemento (Deposito d, unsigned int pos){
	nodo * actual;
	actual=d->tabla;

	for(int i=0; i<pos; i++){
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
		if( d->marcas[hash(primeroLista(l))] == 0){
			d->marcas[hash(primeroLista(l))]=1;
			dfs(primeroLista(l), d, p);
		}
		restoLista(l);
	}
	irActual (l);
	apilar(valor, p);

}


Pila dfsPostOrden (Deposito d){

	nodo * actual;
	actual=d->tabla;

	Pila p;
	crearPila(d->cantidad_articulos, p);

	int contador=1;

	for(int i=0; i<d->cantidad_articulos;i++){
		d->marcas[i]=0;
	}

	while(actual!=NULL){

	//printf("Se marco %d  el valor %d tenia marca %d \n", contador, actual->valor, d->marcas[actual->valor]);

		if(d->marcas[hash(actual->valor)]==0)
			dfs(actual->valor, d, p);
	
		actual=actual->siguiente;
		contador++;
	}

	return p;

}


/*  Devuelve un depósito igual a 'd' pero con las referencias
    en sentido inverso. */
Deposito transpuesto (Deposito d)
{

	Deposito transpuesto;
	transpuesto=crearDeposito (d->cantidad_articulos);

	nodo* actual;
	actual=d->tabla;
	
	//imprimirDeposito(d);

	while(actual!=NULL)
	{
		ListaOrd l;
		l=actual->l;
		imprimirLista(l);
		if(!esVaciaLista(l))
		{

			while(!esVaciaLista(l)){
				//printf("a1 %d \t a2 %d \n", primeroLista(l), actual->valor);
				agregarReferencia (transpuesto, primeroLista(l), actual->valor);
				restoLista(l);
			}
		}
		irActual (l);
		actual=actual->siguiente;
	}

	return transpuesto;
}



void bfs(Deposito d, tipoT valor, unsigned int id, unsigned int * &agrupamientos){
	Cola c;
	tipoT u;
	crearCola(c);
	encolar (valor, c);


	d->marcas[valor]=1;
	agrupamientos[valor]=id;

	int contador=1;

	while(!esVaciaCola (c)){
		u=frente(c);
		desencolar (c);

		//Vamos hacia el nodo
		nodo * actual;
		actual=d->tabla;

		for(int i=0; i<u; i++){
			actual=actual->siguiente;
		}

		//obtenemos su lista de adyacentes
		ListaOrd l;
		l=actual->l;
		//printf("PASADA NUMERO: %d \n", contador);
		//imprimirLista(l);
		
		while(!esVaciaLista(l)){
				if( d->marcas[hash(primeroLista(l))] == 0 && agrupamientos[hash(primeroLista(l))]==0 ){
					d->marcas[hash(primeroLista(l))]=1;
					encolar (primeroLista(l), c);
					agrupamientos[hash(primeroLista(l))]=id;
				}
			restoLista(l);
			}
		irActual (l);
		contador++;
		}
}


/*  Precondiciones:
        1. El tamaño de 'agrupamientos' es igual a la cantidad de artículos de
           'd'.
        2. 'agrupamientos [hash (a)] == id'.

    El valor de 'agrupamientos [i]' es: el identificador del agrupamiento
    al que se ha asignado el artículo 'x' que cumple 'hash (x) == i', o
    USHRT_MAX si 'x' todavía no ha sido asignado a ningún agrupamiento.

    Modifica 'agrupamientos' asignando 'id' a los artículos que cumplen todas
    las siguientes condiciones:
        a) todavía no se les ha asignado agrupamiento;
        b) son accesibles desde 'a';
        c) el acceso desde 'a' debe poder hacerse sin seguir referencias a
           través de artículos a los que ya se había asignado agrupamiento antes
           de la invocación. */
void nuevosAccesibles (Deposito d, tipoT a, unsigned int id,
                       unsigned int * &agrupamientos){




	for(int i=0; i<d->cantidad_articulos;i++){
		d->marcas[i]=0;
	}


	bfs(d, a, id, agrupamientos);



	/*for(int i=1; i<=d->cantidad_articulos;i++){
		if(d->marcas[i]==1){
			agrupamientos[i]=id;
		}
	}*/

	/*for(int i=0; i<d->cantidad_articulos;i++){
			printf("Valor en la posicion %d \t %d \n", i, agrupamientos[i]);
	}*/



}


void destruirDeposito (Deposito &d){

	nodo * actual;
	actual=d->tabla;
	while (actual != NULL) 
	{
		nodo * aux;
		destruirLista(actual->l);
		aux=actual;
		actual=actual->siguiente;
		delete aux;
	}
	delete d->marcas;
	delete d;

}


int getMarca(Deposito d, tipoT i){
	return d->marcas[i];
}

void setMarca(Deposito d, tipoT i, tipoT j){
	d->marcas[hash(i)]=j;
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








