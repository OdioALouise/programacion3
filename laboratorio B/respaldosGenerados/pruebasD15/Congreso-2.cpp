#include "Congreso.h"
#include <stdio.h>

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla, int ultimacharla, int xi);

bool disponible (int idCharla, int idSala, charla *charlas, sala *salas);
bool compatibles (int idCharla1, int idCharla2, charla *charlas);
bool verificaRest(int *tupla, int n, charla* charlas, sala* salas, int i, int ultimacharla);
bool esSalaDisponible(charla* charlas, int i, sala* salas, int xi);
bool esMejor(int *tupla, int *solucion, charla* charlas, int n);
bool ordenarCharlas(int *tupla, int i, int j, charla* charlas);
bool esSolucion(int *tupla, int i, int n);
void copiar(int *tupla,int* solucion, int n);
bool predicado(int *tupla, int *solucion, int n);


int* max_asistentes_m (charla* charlas, int n, sala* salas, int m)
{
	int *solucion = new int[n+1];	
	int *tupla = new int[n+2];
	int ultimacharla = new int[m];

	//Inicializo vectores
	tupla[n+1]=0;

	for(int i=0; i < n; i++)
	{
		solucion[i]=-1;
		tupla[i]=-1;
		ultimacharla[i]=-1;
		tupla[n+1]+=charlas[i].asistentes;
	}

	solucion[n]=0;
	tupla[n]=0;

	//Ordeno vector charlas según fecha de fin
	ordenarCharlas(tupla,0,n-1,charlas);

	for(int k=0; k < n; k++)
	{
		printf("charla[%d].inicio=%d; charla[%d].fin=%d; charla[%d].asistentes=%d;\n", k, charlas[k].inicio, k, charlas[k].fin, k, charlas[k].asistentes);
	}

	backtracking(charlas, n, salas, m, solucion, 0, tupla, ultimacharla,-1);

	
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

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla, int ultimacharla, int xi)
{
	//IMPRIMO tupla[]
	printf("\n\n");

	printf("i=%d \n", i);

	for(int k=0; k < n; k++)
	{
		printf("tupla[%d]=%d \n", k, tupla[k]);
	}


	printf("Asistentes en tupla: %d \n", tupla[n]);
	printf("Asistentes que quedan tupla: %d \n", tupla[n + 1]);

	//IMPRIMO ultimacharla[]
	printf("\n");

	for(int k=0; k < m; k++)
	{
		printf("ultimacharla[%d]=%d \n", k, ultimacharla[k]);
	}
	
		
	if(predicado(tupla, solucion, n)){
		printf("Verificando restricciones...\n");
		if(verificaRest(tupla, n, charlas, salas, i, ultimacharla)){
			printf("Restricciones cumplidas\n");

			ultimacharla[xi] = i-1;	/*Le asigno a la sala el nivel actual-1
									Obs: > el xi lo paso como parámetro en la función,
									y viene inicializado en -1. El paso base es entonces
									ultimacharla[-1] = -1 (porque te chupa un huevo). */

			if( esMejor(tupla, solucion, charlas, n)){
				copiar(tupla,solucion, n);
			}
			
			
			for(int j=i; j<n; j++) {
				for(int hi=0; hi < m; hi++)
				{
					tupla[j]=hi;

					tupla[n]+=charlas[j].asistentes;
					tupla[n+1]-=charlas[j].asistentes;

					backtracking(charlas, n, salas, m, solucion, j + 1, tupla, ultimacharla,hi);
					
					tupla[n]-=charlas[j].asistentes;
					tupla[n+1]+=charlas[j].asistentes;

					tupla[j]=-1;
				}
			}
			//ultimacharla[xi] = -1;	//Probablemente ACÁ ESTÉ EL PROBLEMA
		}
	}
}

bool ordenarCharlas(int *tupla, int left, int right, charla* charlas) {
      int i = left;
      int j = right;
      charla tmp;
      int pivot = charlas[(left + right) / 2].fin;

      //partition
      while (i <= j) {
            while (charlas[i].fin < pivot)
                  i++;

            while (charlas[j].fin > pivot)
                  j--;

            if (i <= j) {
                  tmp = charlas[i];
                  charlas[i] = charlas[j];
                  charlas[j] = tmp;
                  i++;
                  j--;
            }
      }

      //recursion 
      if (left < j)
            ordenarCharlas(tupla, left, j, charlas);
      if (i < right)
            ordenarCharlas(tupla, i, right, charlas);
}

bool predicado(int *tupla, int *solucion, int n) {
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
//con la charla más próxima que tiene la misma sala asignada
bool verificaRest (int *t, int n, charla *charlas, sala *salas, int i, int *ultimacharla) //Verifica si las restricciones se cumplen
{ 
	bool boolean = true;
	i--;

	//Verifico si hay disponibilidad para la charla i
	if (t[i]!=-1 && !disponible(i,t[i],charlas,salas))
		boolean = false;

	//Verifico compatibilidad
	if (t[i]!=-1 && ultimacharla[t[i]]!=-1 && !compatibles(ultimacharla[t[i]],i,charlas))
			boolean = false;

	return boolean;
}

//Determina si la cantidad de asistentes de la tupla es mayor
//que la cantidad de asistentes de la tupla solucion
bool esMejor(int *tupla, int *solucion, charla* charlas, int n){
	if(tupla[n]<=solucion[n])
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
