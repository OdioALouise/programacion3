#include "OperacionesDeposito.h"
#include "Deposito.h"
#include "ListaOrd.h"
#include "Pila.h"
#include "Cola.h"
#include <stdio.h>
#include <limits.h>

void imprimirLista (ListaOrd &l);
void imprimirPila (Pila &p);
void imprimirDeposito (Deposito &l);
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



	//for(unsigned int i = 0; i<cantidadArticulos (d); i++)
		//printf("Es marcado? %d \n", 0);

	//imprimirPila(p);
	id=1;

	while(!esVaciaPila(p) ){
		//if(agrupamientos[cima(p)]==0){

		//if(getMarca(t,cima(p))==0){
		if(agrupamientos[cima(p)]==65535){
			//printf("\n");
			nuevosAccesibles (t, cima(p), id, agrupamientos);
			/*for(unsigned int i = 0; i<10; i++)
				printf("Las posiciones %d Los valores: %d \n", i, agrupamientos[i]);*/

			//printf("\n");
			id++;
		}

		desapilar(p);
	}


	for(unsigned int i = 0; i< cantidadArticulos (d); i++)
		agrupamientos[i]=agrupamientos[i] + cantidadArticulos (d);


	unsigned int aux;
	aux=agrupamientos[0];
	unsigned int contador=0;

	/*for(unsigned int i = 0; i< cantidadArticulos (d); i++)
		printf("ESTE TENEMOS ANTES DE PASAR %d \n", agrupamientos[i]);
*/


	for(unsigned int i=0; i<cantidadArticulos (d); i++){

		if(agrupamientos[i] >cantidadArticulos (d))
			contador++;

		//printf("PASMAOS I %d \n", agrupamientos[i]);
		aux=agrupamientos[i];
		//printf("\t \n");
		for(unsigned int j=0; j<cantidadArticulos (d); j++){
		//printf("PASMAOS J AGRUPAMIENTOS %d == aux %d ? \n", agrupamientos[j], aux );
			if(agrupamientos[j] == aux && agrupamientos[j]>contador){
				agrupamientos[j]=contador;
				//printf("\t \t AGRUPAMIENTOSS vale %d \t \n", agrupamientos[j]);				
				}
			/*if(agrupamientos[j] == aux)
			{
				agrupamientos[j]=contador;
			}else if(agrupamientos[j] == contador){
				agrupamientos[j]=aux;
			}*/	

		}
	}


	for(unsigned int i = 0; i< cantidadArticulos (d); i++)
		agrupamientos[i]--;


	//imprimirDeposito(d);

	//imprimirDeposito(t);

	//imprimirPila(p);

	
	/*for(unsigned int i = 0; i<10; i++)
			printf("iuiuLas posiciones %d Los valores: %d \n", i, agrupamientos[i]);*/


	return agrupamientos;

}



tipoT separacion_a_articulosBFS(Deposito d, tipoT v, ListaOrd &lista_ord, bool * articulos_considerados){


	Cola q;
	tipoT u;
	//tipoT w;
	unsigned int distAux;

	crearCola(q);
	setMarca(d, v, 0);
	
	//printf("MARCA %d \n", getMarca(d, v));
	

	encolar(v, q);

	distAux = 0;

	while(!esVaciaCola(q) ){

		u = frente (q); 
		desencolar(q);

		ListaOrd l;
		l=referencias (d,u);
		//printf("0001 --- El valor de adyacentes a %d \n", u);
		/*if(!esVaciaLista(l)){
			imprimirLista (l);
			irActual (l);
		}*/		

		while(!esVaciaLista(l)){
			//printf("0002 --- Valor de %d en marcas %d \n", primeroLista(l), getMarca(d,  primeroLista ( l) ));
			//printf("\t");

			if( getMarca(d,  primeroLista ( l) )  == 0 ){
				if(primeroLista ( l) != v){
					setMarca(d,  primeroLista ( l), getMarca(d,  u ) + 1 ) ;
					//printf("NIVEL DE %d recien sumado %d \n", primeroLista(l), getMarca(d,  primeroLista ( l) ));
				}
				//printf("marcas %d es mayor a la distancia actual? %d \n", getMarca(d,  primeroLista ( l) ), distAux );				
				if( getMarca(d,  primeroLista ( l) ) >  distAux && primeroLista ( l) != v && articulos_considerados[hash(primeroLista(l))])
					distAux=getMarca(d,  primeroLista ( l) );
				if(primeroLista ( l) != v)
					encolar(  primeroLista ( l) , q);				

				}
			restoLista(l);
			}

			irActual (l);
		}


	//printf("Distancia %d \n", distAux);
	return distAux;
	//insLista (distAux, lista_ord);

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



	/*for(unsigned int i = 0; i<cantidadArticulos(d); i++){
		if(!articulos_considerados[i]){
			printf("Marcamos con 1 A %d \n", i);
			setMarca(d,  i,  1 );
		}else{
			setMarca(d,  i,  0 );
		}
	}*/




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



	/*for(unsigned int i = 0; i<cantidadArticulos(d); i++){
				setMarca(d,  i,  0 );
	}*/



	


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



/*	ListaOrd l;
	unsigned int max_separacion=0;
*/
/*	unsigned int * agrupamientos =new unsigned int [6];

	for(unsigned int i = 0; i<6; i++)
		agrupamientos[i]=0;



	agrupamientos=colecciones(d);

	for(unsigned int i = 0; i<6; i++)
			printf("%d \n", agrupamientos[i]);
	
*/



	/*for(unsigned int i = 0; i<cantidadArticulos(d); i++)
	{

		for(unsigned int h = 0; h<cantidadArticulos(d); h++){
			setMarca(d, h, 0);
		}

		separacion_a_articulosBFS(d, i, l);


	}*/



	/*for(unsigned int i = 0; i<cantidadArticulos(d); i++)
	{

		for(unsigned int h = 0; h<cantidadArticulos(d); h++){
			setMarca(d, h, 0);
		}


		if(articulos_considerados[i]){
			separacion_a_articulosBFS(d, i, l);
			for(unsigned int j = 0; j<cantidadArticulos(d); j++){
				if(articulos_considerados[j] && j !=i){
					if(getMarca(d, j) > max_separacion){
						max_separacion=getMarca(d, j);
					}else if (getMarca(d, j) ==0){
						return USHRT_MAX;
					}
				}
			}
		}
	}*/

	//printf("Liegamos \n");
	//imprimirLista (l);

	//return Maximo(l);
	return maximo;

}




