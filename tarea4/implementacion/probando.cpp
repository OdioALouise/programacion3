#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tipoT.h"
#include "Cola.h"
#include "ListaOrd.h"
#include "Pila.h"
#include "Deposito.h"

void imprimir (Cola &c);
void imprimirLista (ListaOrd &l);
void imprimirPila (Pila &p);
void imprimirDeposito (Deposito &l);



int main(){

	ListaOrd l;
	
	Deposito d;
	d=crearDeposito(7);

	agregarReferencia(d, 3, 2);
	agregarReferencia(d, 3, 5);
	agregarReferencia(d, 3, 1);


	agregarReferencia(d, 2, 5);

	//l=referencias (d, 3);
	//imprimirLista(l);
	//imprimirLista(l);
	//l=referencias (d, 2);
	//imprimirLista(l);

	//printf("Elemento en posicion 2: %d \n", elemento (d, 2) );
	//printf("Elemento en posicion 3: %d \n", elemento (d, 3) );

	//printf("Cantidad de articulos %d \n", cantidadArticulos(d));


        unsigned int * agrupamientos =new unsigned int [7];

	for(unsigned int i = 0; i<7; i++)
		agrupamientos[i]=0;

	nuevosAccesibles (d, 3, 12 ,agrupamientos);

	printf("BOLSO CAGON \n");

	for(unsigned int i = 0; i<7; i++)
		agrupamientos[i]=0;

	nuevosAccesibles (d, 4, 12 ,agrupamientos);


	printf("BOLSO CAGON \n");

	for(unsigned int i = 0; i<7; i++)
		agrupamientos[i]=0;

	nuevosAccesibles (d, 6, 12 ,agrupamientos);


	printf("BOLSO CAGON \n");

	for(unsigned int i = 0; i<7; i++)
		agrupamientos[i]=0;

	nuevosAccesibles (d, 7, 12 ,agrupamientos);


	/*Pila p;	
	p=dfsPostOrden(d);

	printf("IMPRIMIR PILAS \n\n\n");

	imprimirPila(p);
	
	Deposito t;

	t=transpuesto (d);
	printf("VA MANYAR MIERDA \n\n\n");
	imprimirDeposito(t);

	printf("AGORA EL OTRO CARA \n\n\n");
	imprimirDeposito(d);
	*/

	destruirDeposito (d);

	return 0;
}


/*
	Pila c;
	crearPila(10, c);

	if (esVaciaPila(c))
		printf("Es vacia PILA \n");

	if (!esLlenaPila(c))
		printf("NO Es LLENA PILA \n");

	tipoT t=23;
	apilar (t,c);

	t=53;
	apilar (t,c);

	t=5;
	apilar (t,c);

	imprimirPila(c);

	destruirPila(c);


*/


	/*ListaOrd c;
	crearLista(c);

	if (esVaciaLista(c))
		printf("Es vacia Lista \n");


	tipoT t=23;
	insLista(t,c);

	t=53;
	insLista(t,c);

	t=5;
	insLista(t,c);

	t=30;
	insLista(t,c);

	printf("Es vacia Lista %d \n", primeroLista(c));
	

	//imprimirLista(c);
	//imprimir(c);


	destruirLista(c);
	*/



	/*Cola c;
	crearCola (c);

	if (esVaciaCola(c))
		printf("Es vacia cola \n");


	tipoT t=23;
	encolar (t,c);

	t=53;
	encolar (t,c);

	t=5;
	encolar (t,c);

	//imprimir(c);


	desencolar(c);
	desencolar(c);
	desencolar(c);

	imprimir(c);


	destruirCola(c);*/


	
/*		tipoT t1=2;
		tipoT t2=2;

		if( esMayor (t1, t2))
			printf("Es mayor \n");
		else if ( esMenor (t1, t2))
			printf("Es menor \n");
		else if(esIgual(t1, t2))
			printf("Es igual \n");
	


	//FUNCION tipoTAstring ANDANDO
	char s[2]={'1', '5'};
	char* referencia2;
	referencia2=s;
	printf("ACA CONVERTIMOS STRING A TIPO T RESULTADO: %d \n", stringAtipoT(referencia2));



	//FUNCION tipoTAstring ANDANDO
	int n=53;
	char* referencia;

	int i=0;

	printf("ACA CONVERTIMOS TIPO T A STRING RESULTADO: ");

	referencia=tipoTAstring (111);

	for (n = 0; isdigit(referencia[i]); i++)
		printf("%c ", referencia[i]);
*/
