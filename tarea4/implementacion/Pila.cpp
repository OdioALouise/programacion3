#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Pila.h"

struct AuxPila{
	tipoT valor;
	struct AuxPila* siguiente;
	};

static tipoT cotaPila;

void crearPila (int cota, Pila &p){
	cotaPila=cota;
	p=NULL;
}


bool esLlenaPila (Pila p){
tipoT contador=0;
Pila actual=new AuxPila;
actual = p;
while(!esVaciaPila(actual))
{
	contador++;
	actual=actual->siguiente;
}


if(esIgual(contador,cotaPila))
	return true;
return false;

}


void apilar (tipoT t, Pila &p){
	Pila actual =new AuxPila;
	actual->valor=t;
	actual->siguiente=NULL;

	if(esVaciaPila (p))
		p=actual;
	else{
		actual->siguiente=p;
		p=actual;
	}
}


bool esVaciaPila (Pila p){
	if(!p)
		return true;
	return false;
}


void desapilar (Pila &p){

	Pila actual=new AuxPila;
	actual=p;
	p=p->siguiente;
	delete actual;
	actual=NULL;
}


tipoT cima (Pila p){
	return p->valor;
}

void destruirPila (Pila &p){
	while(!esVaciaPila(p)){
		desapilar(p);
	}
}


void imprimirPila (Pila &p){
	int contador=1;
	while(!esVaciaPila(p)){
		printf("La pila en la posicion %d \t %d \n", contador, cima(p));
		desapilar(p);
		contador++;
	}
}


