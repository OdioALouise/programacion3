#include "Congreso.h"
#include <stdio.h>

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla, int *ultimacharla, int xi);

bool disponible (int idCharla, int idSala, charla *charlas, sala *salas);
bool compatibles (int idCharla1, int idCharla2, charla *charlas);
bool verificaRest(int *tupla, int n, charla* charlas, sala* salas, int i, int *ultimacharla);
bool esSalaDisponible(charla* charlas, int i, sala* salas, int xi);
bool esMejor(int *tupla, int *solucion, charla* charlas, int n);
bool esSolucion(int *tupla, int i, int n);
void copiar(int *tupla,int* solucion, int n);

bool predicado(int *tupla, int *solucion, int *ultimacharla, charla *charlas, sala *salas, int n, int m, int i); 
void SelectionSort(charla* charlas, int* indices, int n);

int* max_asistentes_m (charla* charlas, int n, sala* salas, int m)
{

	//Arreglos para trabajar
	/**
	solucion arreglo que contendrá la tupla solucion en [0...n-1]
		[n] contendra los asistentes de la solucion
		
	tupla arreglo que contendra la tupla generada para cada estado
		del arbol de soluciones en [0...n-1]
		en [n] contendra los asistenes de las charlas hasta ese momento asignadas
		en [n+1] contendra el resto de los asistentes del total de charlas

	indices arreglo que mantiene los indices del arreglo charla original una vez
		que este es ordenado por fecha de fin

	ultimacharla arreglo que mantiene la ultima charla asignada a una sala
	*/

	int *solucion = new int[n+1];	
	int *tupla = new int[n+2];
	int *indices = new int[n];
	int *ultimacharla= new int[m];

	//Inicializacion de valores 
	tupla[n+1]=0;

	for(int i=0; i < n; i++)
	{
		solucion[i]=-1;
		tupla[i]=-1;
		tupla[n+1]+=charlas[i].asistentes;
		indices[i]=i;
	}


	for(int i=0; i < m; i++)
	{
		ultimacharla[i]=-1;
	}

	solucion[n]=0;
	tupla[n]=0;



	//Ordenamiento de charlas
	SelectionSort(charlas, indices, n);


	//comienzo de backtracking
	backtracking(charlas, n, salas, m, solucion, 0, tupla, ultimacharla,-1);


	//Reordenamos charlas y solucion

	charla charla_temporal;
	int aux_indice;
	int aux_solucion;
	for (int k=0; k<n; k++){
		for(int l=0; l<n; l++){
			if(indices[l]==k){
				charla_temporal=charlas[l];
				charlas[l]=charlas[k];
				charlas[k]=charla_temporal;

				aux_indice=indices[l];
				indices[l]=indices[k];
				indices[k]=aux_indice;
	
				aux_solucion=solucion[l];
				solucion[l]=solucion[k];
				solucion[k]=aux_solucion;			
			}
		}
	}


	return solucion;
}



void SelectionSort(charla* charlas, int* indices, int n){
	int i, j, posmin, tmp;
	charla charla_temporal;
	for(i=0; i< n-1; i++){
		posmin=i;
		for(j=i+1; j<n; j++){
			if(charlas[j].fin < charlas[posmin].fin)		
				posmin=j;
		}
		tmp=indices[i];
		indices[i]=indices[posmin];
		indices[posmin]=tmp;
		charla_temporal=charlas[i];
		charlas[i]=charlas[posmin];
		charlas[posmin]=charla_temporal;
	}
}

/*
Implementacion de la tecnica backtracking

charlas arreglo de charlas de tamanio n
salas arreglo de salas de tamanio m

tupla es la tupla generada por la tecnica al recorrer el arbol de soluciones
solucion tupla solucion del problema
ultimacharla arreglo que mantiene la ultima charla asignada a una sala

posicion i a partir de la cual asignar una sala a una charla
en la tupla generada al recorrer el arbol de soluciones

xi ultimo valor de sala asignada para la charla i

*/
void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla, int *ultimacharla, int xi)
{

	if( predicado(tupla, solucion, ultimacharla,charlas, salas, n, m, i) ){
		if(verificaRest(tupla, n, charlas, salas, i, ultimacharla)){

			int *aux= new int;
			*aux=ultimacharla[xi];
			ultimacharla[xi] = i-1;

			if( esMejor(tupla, solucion, charlas, n)){
				
				copiar(tupla,solucion, n);
			}
			
			
			for(int j=i; j<n; j++) {
				for(int xi=0; xi < m; xi++)
				{
					tupla[j]=xi;

					tupla[n]+=charlas[j].asistentes;
					tupla[n+1]-=charlas[j].asistentes;

					backtracking(charlas, n, salas, m, solucion, j + 1, tupla, ultimacharla,xi);
					
					tupla[n]-=charlas[j].asistentes;
					tupla[n+1]+=charlas[j].asistentes;

					tupla[j]=-1;
				}
			}
			ultimacharla[xi] = *aux;
			delete aux;
		}
	}
}

/*
El predicado compara la cantidad de asistentes de la solucion actual con la cantidad de asistentes de las charlas de la tupla que tienen sala asignada mas los asistentes de aquellas charlas que aun no han sido procesadas ( [i...n-1] ) y que o bien son compatibles con las charlas que tiene sala asignada o bien tienen una sala disponible (que no tiene charla asignada aún).

Si el resultado de la segunda expresión es mayor a la cantidad de asistentes de la solucion actual, entonces es posible que haya una mejor solucion, se sigue el recorrido.
Si el resultado de la segunda expresión es menor a la cantidad de asistentes de la solución actual, entonces no es posible que haya una mejor solucion se realiza poda.
*/

bool predicado(int *tupla, int *solucion, int *ultimacharla, charla *charlas, sala *salas, int n, int m, int i) {

	int restoAsistentes= 0;
	bool esCompatible=false;

	for(int k=i; k<n; k++){
		esCompatible=false;
		for(int j=0; j<m && !esCompatible; j++){

			if( ( ultimacharla[j] == -1 && disponible (k, j, charlas, salas) ) || ( ultimacharla[j] != -1 && compatibles (k, ultimacharla[j], charlas))){
				restoAsistentes+=charlas[k].asistentes;
				esCompatible=true;
			}

		}
	}

	if(tupla[n] + restoAsistentes <= solucion[n]){
		return false;
		}

	return true;

}


//Se debe evaluar la compatibilidad de la charla actual 
//con la charla más próxima que tiene la misma sala asignada
bool verificaRest (int *t, int n, charla *charlas, sala *salas, int i, int *ultimacharla) //Verifica si las restricciones se cumplen
{ 
	bool boolean = true;

	i--;

	//Verifico si hay disponibilidad para la charla i
	if (i!=-1 && t[i]!=-1 && !disponible(i,t[i],charlas,salas)){
		boolean = false;
	}
	//Verifico compatibilidad
	if (i!=-1 && t[i]!=-1 && ultimacharla[t[i]]!=-1 && !compatibles(ultimacharla[t[i]],i,charlas)){
			boolean = false;
		}

	return boolean;
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
