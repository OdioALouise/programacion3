#include "Congreso.h"
#include <stdio.h>

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla);

bool disponible (int idCharla, int idSala, charla *charlas, sala *salas);
bool compatibles (int idCharla1, int idCharla2, charla *charlas);
bool verificaRest(int *tupla, int n, charla* charlas, sala* salas);
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

	
	printf("\n\n");

	for(int k=0; k < n; k++)
	{
		printf("SOLUCION[%d]=%d \n", k, solucion[k]);
	}

	printf("Asistentes en solucion: %d \n", solucion[n]);
	
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

	/*printf("\n\n");

	printf("%d \n", i);

	for(int k=0; k < n; k++)
	{
		printf("tupla[%d]=%d \n", k, tupla[k]);
	}


	printf("Asistentes en tupla: %d \n", tupla[n]);
	printf("Asistentes que quedan tupla: %d \n", tupla[n + 1]);
	*/
		
	if(predicado(tupla, solucion, n)){

		if(verificaRest(tupla, n, charlas, salas)){

			if( esMejor(tupla, solucion, charlas, n)){
				copiar(tupla,solucion, n);
			}
			
			for(int j=i; j<n; j++){
				for(int xi=0; xi < m; xi++)
				{
						if(j<n){
							tupla[j]=xi;

							if(xi>=0){
								tupla[n]+=charlas[j].asistentes;
								tupla[n+1]-=charlas[j].asistentes;
							}

							backtracking(charlas, n, salas, m, solucion, j + 1, tupla);
					
							if(xi>=0){
								tupla[n]-=charlas[j].asistentes;
								tupla[n+1]+=charlas[j].asistentes;
							}

							if(tupla[j]=m)
								tupla[j]=-1;
						}
				}
			}

		}
	}
}

//Tengo que fijarme la compatibilidad de las charlas que estan mas halla  
//de la charla i con i y antes.



bool predicado(int *tupla, int *solucion, int n){
	if(tupla[n] + tupla[n+1] <= solucion[n])
		return false;
	return true;
}

bool compatibles (int idCharla1, int idCharla2, charla *charlas) //Compatibilidad charla-charla
{
	if ((charlas[idCharla1].inicio>=charlas[idCharla2].fin) || (charlas[idCharla1].fin<=charlas[idCharla2].inicio))
		return true;
	else
		return false;
}

bool disponible (int idCharla, int idSala, charla *charlas, sala *salas) //Disponibilidad charla-sala
{
	if ((charlas[idCharla].inicio>=salas[idSala].inicio) && (charlas[idCharla].fin<=salas[idSala].fin))
		return true;
	else
		return false;
}

//Se debe evaluar la compatibilidad de la charla actual 
//con las charlas anteriores que tienen la misma sala asignada
bool verificaRest (int *t, int n, charla *charlas, sala *salas) //Verifica si las restricciones se cumplen
{ 
	int j = 0;
	int k = 1;
	bool boolean = true;
	
	while (j<n && boolean)	//n-1 es la ultima charla de la tupla
	{
		//Verifico compatibilidad entre charlas hasta n-1
		while ((k<i-1) && (j<i-2) && boolean)
		{
			if (t[k]!=-1 && t[j]!=-1 && !compatibles(j,k,charlas))
				boolean = false;
			k++;
		}

		//Verifico si hay disponibilidad para las charlas de la tupla
		if (t[k]!=-1 && t[j]!=-1 && !disponible(j,t[j],charlas,salas))
			boolean = false;

		j++;
		k = j+1;
	}

	return boolean;
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
