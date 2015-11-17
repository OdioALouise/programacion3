#include "Congreso.h"

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla);
bool verificaRest(int *tupla, int i, charla* charlas);
bool esSalaDisponible(charla* charlas, int i, sala* salas, int xi);
bool esMejor(int *tupla, int *solucion, charla* charlas, int n);
bool esSolucion(int *tupla, int i, int n);
void copiar(int *tupla,int* solucion, int n);


int* max_asistentes_m (charla* charlas, int n, sala* salas, int m)
{
	int *solucion = new int[n];	
	int *tupla = new int[n];

	for(int i=0; i < n; i++)
	{
		solucion[i]=-2;
		tupla[i]=-2;
	}

	backtracking(charlas, n, salas, m, solucion, 0, tupla);

	return solucion;
}



//Implementacion de la tecnica backtracking

//charlas arreglo de charlas de tamanio n
//salas arreglo de salas de tamanio m

//solucion tupla solucion del problema

//posicion i a partir de la cual asignar una sala a una charla
//en la tupla generada al recorrer el arbol de soluciones

//tupla es la tupla generada por la tecnica al recorrer el arbol de soluciones

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int tupla)
{		
	if(verificaRest(tupla, i, charlas)){


				if(esSolucion(tupla, i, n) && esMejor(tupla, solucion, charlas, n)){
					copiar(tupla,solucion, n);
				}

				for(int xi=-1; xi < m; xi++)
					{
						if( (xi < 0) || esSalaDisponible(charlas,i, salas, xi) ){
								if(i<n){
									tupla[i]=xi;
									//if(xi>=0)
										//tupla[n]+=charlas[i].asistentes
									backtracking(charlas, n, salas, m, solucion, i + 1, tupla);
									if(tupla[i]==m)
										tupla[i]=-2;							
								}
						}
					}

	}
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

	int asistentes_tupla=0;
	int asistentes_solucion=0;

	for(int j=0; j<=n-1; j++)
	{
		if(solucion[j] >= 0){
			asistentes_solucion+=charlas[j].asistentes;
		}

		if(tupla[j] >= 0){
			asistentes_tupla+=charlas[j].asistentes;
		}
	}
	if(asistentes_tupla<asistentes_solucion)
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
	for(int j=0; j<=n-1; j++){
		solucion[j]=tupla[j];
	}
}

