#include "Congreso.h"
#include <stdio.h>

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla);
bool verificaRest(int *tupla, int i, charla* charlas);
bool esSalaDisponible(charla* charlas, int i, sala* salas, int xi);
bool esMejor(int *tupla, int *solucion, charla* charlas, int n);
bool esSolucion(int *tupla, int i, int n);
void copiar(int *tupla,int* solucion, int n);
bool predicado(int *tupla, int *solucion, int n);


int* max_asistentes_m (charla* charlas, int n, sala* salas, int m)
{
	int *solucion = new int[n+1];	
	int *tupla = new int[n+2];

   	

	tupla[n+1]=0;

	for(int i=0; i < n; i++)
	{
		solucion[i]=-1;
		tupla[i]=-1;
		tupla[n+1]+=charlas[i].asistentes;
	}

	solucion[n]=0;
	tupla[n]=0;

	backtracking(charlas, n, salas, m, solucion, 0, tupla);

	/*
	printf("\n\n");

	for(int k=0; k < n; k++)
	{
		printf("SOLUCION[%d]=%d \n", k, solucion[k]);
	}

	printf("Asistentes en solucion: %d \n", solucion[n]);
	*/
	return solucion;
}



//Implementacion de la tecnica backtracking

//charlas arreglo de charlas de tamanio n
//salas arreglo de salas de tamanio m

//solucion tupla solucion del problema

//posicion i a partir de la cual asignar una sala a una charla
//en la tupla generada al recorrer el arbol de soluciones

//tupla es la tupla generada por la tecnica al recorrer el arbol de soluciones

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla)
{

	printf("\n\n");

	for(int k=0; k < n; k++)
	{
		printf("tupla[%d]=%d \n", k, tupla[k]);
	}


	printf("Asistentes en tupla: %d \n", tupla[n]);
	printf("Asistentes que quedan tupla: %d \n", tupla[n + 1]);
	
		
	if(predicado(tupla, solucion, n)){

		if(verificaRest(tupla, i, charlas)){

				if( esMejor(tupla, solucion, charlas, n)){
					copiar(tupla,solucion, n);
				}

				for(int xi=-1; xi < m; xi++)
					{
						//printf("Charla: %d a sala %d \n", i, xi);
						if( (xi < 0) || esSalaDisponible(charlas,i, salas, xi) ){
								if(i<n){
									tupla[i]=xi;
									if(xi>=0){
										tupla[n]+=charlas[i].asistentes;
										tupla[n+1]-=charlas[i].asistentes;
									}
									backtracking(charlas, n, salas, m, solucion, i + 1, tupla);
									if(xi>=0){
										tupla[n]-=charlas[i].asistentes;
										tupla[n+1]+=charlas[i].asistentes;
									}
								}
						}
					}
		}
	}
}


bool predicado(int *tupla, int *solucion, int n){
	if(tupla[n] + tupla[n+1] <= solucion[n])
		return false;
	return true;
}



//Se debe evaluar la compatibilidad de la charla actual 
//con las charlas anteriores que tienen la misma sala asignada
bool verificaRest(int *tupla, int i, charla* charlas){

	if(tupla[i-1]<0)
		return true;

	for(int j=0; j<i-1; j++)
	{
		if(tupla[j]==tupla[i-1]){
			if( ! ( ( charlas[j].fin <=  charlas[i-1].inicio) || ( charlas[i-1].fin <=  charlas[j].inicio) ) ){
				return false;
			}

		}		
	}
	return true;
}


//Verificar si la charla cae dentro de la disponibilidad horaria
//de la sala
bool esSalaDisponible(charla* charlas, int i, sala* salas, int xi){
	if( !  ( (charlas[i].fin <= salas[xi].fin) && (charlas[i].inicio >= salas[xi].inicio) ) ){
		return false;
	}
	return true;
}


//Determina si la cantidad de asistentes de la tupla es mayor
//que la cantidad de asistentes de la tupla solucion
bool esMejor(int *tupla, int *solucion, charla* charlas, int n){
	if(tupla[n]<solucion[n])
		return false;	
	return true;
}

bool esSolucion(int *tupla, int i, int n){

	if(i==n)
		return true;

	return false;
}


//Se actualiza la tupla solucion
void copiar(int *tupla,int* solucion, int n){
	for(int j=0; j<=n; j++){
		solucion[j]=tupla[j];
	}
}

