#include "OperacionesDeposito.h"
#include "Deposito.h"
#include "ListaOrd.h"
#include "Pila.h"
#include <stdio.h>

void imprimirLista (ListaOrd &l);
void imprimirPila (Pila &p);
void imprimirDeposito (Deposito &l);
void irActual (ListaOrd & l);
int getMarca(Deposito d, tipoT i);
		
unsigned int * colecciones (Deposito d){
	Deposito t;
	Pila p;
	tipoT id;
	p=dfsPostOrden(d);
	
	t=transpuesto(d);
	
	unsigned int * agrupamientos =new unsigned int [7];

	for(unsigned int i = 0; i<=6; i++)
		agrupamientos[i]=0;

	id=1;

	//imprimirPila(p);

	while(!esVaciaPila(p) ){
		//if(agrupamientos[cima(p)]==0){

		if(getMarca(t,cima(p))==0){
			printf("\n");
			nuevosAccesibles (t, cima(p), id, agrupamientos);
			printf("\n");
			id++;
		}

		desapilar(p);

	}


	for(unsigned int i = 0; i<=6; i++)
		agrupamientos[i]--;


	for(unsigned int i = 0; i<=6; i++)
		printf("VALORES %d \n ", agrupamientos[i]);

	//imprimirDeposito(d);

	//printf("BOLSO CAGON \t \n");

	//imprimirDeposito(t);

	//imprimirPila(p);

	return agrupamientos;

}



unsigned int gradosDeSeparacion (Deposito d, bool * articulos_considerados){
	unsigned int * agrupamientos =new unsigned int [7];

	for(unsigned int i = 0; i<=6; i++)
		agrupamientos[i]=0;

	agrupamientos=colecciones(d);

	unsigned int i=0;
	return i;

}




