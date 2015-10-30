#include "OperacionesDeposito.h"
#include "Deposito.h"
#include "ListaOrd.h"
#include "Pila.h"
#include "Cola.h"
#include <stdio.h>
#include <limits.h>

void irActual (ListaOrd & l);
unsigned int getMarca(Deposito d, tipoT i);
void setMarca(Deposito d, tipoT i, tipoT j);
tipoT Maximo (ListaOrd & l);

unsigned int * colecciones (Deposito d){
	Deposito t;
	Pila p;
	tipoT id;
	p=dfsPostOrden(d);

	t=transpuesto(d);


	unsigned int * agrupamientos =new unsigned int [cantidadArticulos (d)];

	for(unsigned int i = 0; i<cantidadArticulos (d); i++)
		agrupamientos[i]=65535;

	id=1;

	while(!esVaciaPila(p) ){
		if(agrupamientos[cima(p)]==65535){
			nuevosAccesibles (t, cima(p), id, agrupamientos);
			id++;
		}

		desapilar(p);
	}


	for(unsigned int i = 0; i< cantidadArticulos (d); i++)
		agrupamientos[i]=agrupamientos[i] + cantidadArticulos (d);


	unsigned int aux;
	aux=agrupamientos[0];
	unsigned int contador=0;


	for(unsigned int i=0; i<cantidadArticulos (d); i++){

		if(agrupamientos[i] >cantidadArticulos (d))
			contador++;
		aux=agrupamientos[i];
		for(unsigned int j=0; j<cantidadArticulos (d); j++){
			if(agrupamientos[j] == aux && agrupamientos[j]>contador){
				agrupamientos[j]=contador;
				}
		}
	}


	for(unsigned int i = 0; i< cantidadArticulos (d); i++)
		agrupamientos[i]--;

	return agrupamientos;

}



tipoT separacion_a_articulosBFS(Deposito d, tipoT v, ListaOrd &lista_ord, bool * articulos_considerados){
	Cola q;
	tipoT u;
	unsigned int distAux;

	crearCola(q);
	setMarca(d, v, 0);

	encolar(v, q);

	distAux = 0;

	while(!esVaciaCola(q) ){

		u = frente (q); 
		desencolar(q);

		ListaOrd l;
		l=referencias (d,u);

		while(!esVaciaLista(l)){

			if( getMarca(d,  primeroLista ( l) )  == 0 ){
				if(primeroLista ( l) != v){
					setMarca(d,  primeroLista ( l), getMarca(d,  u ) + 1 ) ;
				}
				if( getMarca(d,  primeroLista ( l) ) >  distAux && primeroLista ( l) != v && articulos_considerados[hash(primeroLista(l))])
					distAux=getMarca(d,  primeroLista ( l) );
				if(primeroLista ( l) != v)
					encolar(  primeroLista ( l) , q);				

				}
			restoLista(l);
			}

			irActual (l);
		}
	return distAux;
	}


unsigned int gradosDeSeparacion (Deposito d, bool * articulos_considerados){

	unsigned int cfc=0;
	unsigned int contador=0;
	unsigned int maximo=0;
	ListaOrd l;
	crearLista (l);

	unsigned int * agrupamientos =new unsigned int [cantidadArticulos(d)];
	unsigned int * grados =new unsigned int [cantidadArticulos(d)];

	for(unsigned int i = 0; i<cantidadArticulos(d); i++)
		agrupamientos[i]=65535;
	
	for(unsigned int i = 0; i<cantidadArticulos(d); i++)
		grados[i]=0;


	agrupamientos=colecciones(d);

	for(unsigned int i = 0; i<cantidadArticulos(d); i++){
		if(articulos_considerados[i]){
			if(contador==0){
				cfc=agrupamientos[i];
				} else if(cfc!=agrupamientos[i]){
				return USHRT_MAX;
			}
				contador++;

				for(unsigned int h = 0; h<cantidadArticulos(d); h++){
								setMarca(d,  h,  0 );
				}
				grados[i]= separacion_a_articulosBFS(d, i, l, articulos_considerados);
		}
	}


	if(contador==1)
		return 0;


	for(unsigned int i = 0; i<cantidadArticulos(d); i++){
		if(maximo<grados[i])
			maximo=grados[i];
	}



	for(unsigned int i = 0; i<cantidadArticulos(d); i++){
		if(grados[i] !=0){
			ListaOrd l;
			l=referencias (d, i);
			bool hayCamino=false;

			while(!esVaciaLista(l)){
				if( grados[primeroLista(l)] != 0 ){
					hayCamino=true;
				}
				restoLista(l);
			}
			irActual( l);
			if(!hayCamino)
				return USHRT_MAX;

		}
	}

	return maximo;

}




