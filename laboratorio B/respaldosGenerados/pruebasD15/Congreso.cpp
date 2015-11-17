#include "Congreso.h"
#include <stdio.h>

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla, int *ultimacharla, int xi);

bool disponible (int idCharla, int idSala, charla *charlas, sala *salas);
bool compatibles (int idCharla1, int idCharla2, charla *charlas);
bool verificaRest(int *tupla, int n, charla* charlas, sala* salas, int i, int *ultimacharla);
bool esSalaDisponible(charla* charlas, int i, sala* salas, int xi);
bool esMejor(int *tupla, int *solucion, charla* charlas, int n);
bool ordenarCharlas(int *tupla, int i, int j, charla* charlas);
bool esSolucion(int *tupla, int i, int n);
void copiar(int *tupla,int* solucion, int n);
//bool predicado(int *tupla, int *solucion, int n);
bool predicado(int *tupla, int *solucion, int *ultimacharla, charla *charlas, sala *salas, int n, int m, int i); 
void SelectionSort(charla* charlas, int* indices, int n);

int* max_asistentes_m (charla* charlas, int n, sala* salas, int m)
{
	int *solucion = new int[n+1];	
	int *tupla = new int[n+2];
	int *indices = new int[n];
	int *ultimacharla= new int[m];

	//Inicializo vectores
	tupla[n+1]=0;

	for(int i=0; i < n; i++)
	{
		solucion[i]=-1;
		tupla[i]=-1;
		tupla[n+1]+=charlas[i].asistentes;
	}


	for(int i=0; i < m; i++)
	{
		ultimacharla[i]=-1;
	}


	solucion[n]=0;
	tupla[n]=0;

	//SelectionSort(charlas, indices, n);

	//Ordeno vector charlas según fecha de fin
	ordenarCharlas(tupla,0,n-1,charlas);

	for(int k=0; k < n; k++)
	{
		//printf("charla[%d].inicio=%d; charla[%d].fin=%d; charla[%d].asistentes=%d;\n", k, charlas[k].inicio, k, charlas[k].fin, k, charlas[k].asistentes);
	}

	backtracking(charlas, n, salas, m, solucion, 0, tupla, ultimacharla,-1);

	
/*	printf("\n\n");

	int suma=0;

	for(int k=0; k < n; k++)
	{
printf("SOLUCION[%d]=%d charla[%d].asistentes=%d charla[%d].inicio=%d charla[%d].fin=%d \n", k, solucion[k], k, charlas[k].asistentes, k, charlas[k].inicio, k, charlas[k].fin);
		if(solucion[k] != -1)
			suma+=charlas[k].asistentes;
	}

	printf("Asistentes en solucion: %d %d\n", solucion[n], suma);
*/	
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


//Implementacion de la tecnica backtracking

//charlas arreglo de charlas de tamanio n
//salas arreglo de salas de tamanio m

//solucion tupla solucion del problema

//posicion i a partir de la cual asignar una sala a una charla
//en la tupla generada al recorrer el arbol de soluciones

//tupla es la tupla generada por la tecnica al recorrer el arbol de soluciones

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla, int *ultimacharla, int xi)
{
	//IMPRIMO tupla[]
	/*printf("\n\n");

	printf("i=%d \n", i);

	for(int k=0; k < n; k++)
	{
		printf("tupla[%d]=%d \n", k, tupla[k]);
	}


	printf("Asistentes en tupla: %d \n", tupla[n]);
	printf("Asistentes que quedan tupla: %d \n", tupla[n + 1]);
	printf("Asistentes en solucion: %d \n", solucion[n]);

	//IMPRIMO ultimacharla[]
	printf("\n");

	for(int k=0; k < m; k++)
	{
		printf("ultimacharla[%d]=%d \n", k, ultimacharla[k]);
	}
	
*/		
	//if(predicado(tupla, solucion, n)){
	if(predicado(tupla, solucion, ultimacharla,charlas, salas, n, m, i) ){
		//printf("Verificando restricciones...\n");
		if(verificaRest(tupla, n, charlas, salas, i, ultimacharla)){
			//printf("Restricciones cumplidas\n");

				/*Le asigno a la sala el nivel actual-1
									Obs: > el xi lo paso como parámetro en la función,
									y viene inicializado en -1. El paso base es entonces
									ultimacharla[-1] = -1 (porque te chupa un huevo). */
			int aux=ultimacharla[xi];
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
			ultimacharla[xi] = aux;
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

bool predicado(int *tupla, int *solucion, int *ultimacharla, charla *charlas, sala *salas, int n, int m, int i) {

	int restoAsistentes=0;
	bool esCompatible=false;

	//printf("\t %d \n", i);

	for(int k=i; k<n; k++){
		esCompatible=false;
		for(int j=0; j<m && !esCompatible; j++){

			if( ( ultimacharla[j] == -1 && disponible (k, j, charlas, salas) ) || ( ultimacharla[j] != -1 && compatibles (k, ultimacharla[j], charlas))){
				//printf("sumo %d \n", charlas[k].asistentes);
				restoAsistentes+=charlas[k].asistentes;
				esCompatible=true;
			}

		}
	}

	//printf("\t tupla[n]=%d + restoAsistentes=%d <= solucion[n]=%d \n", tupla[n], restoAsistentes, solucion[n]);

	if(tupla[n] + restoAsistentes <= solucion[n])
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
	//printf("\t %d \n", i);
	i--;
	//printf("\t %d \n", i);

	//printf("\t t[i=%d]=%d !=-1 && !disponible(i=%d,t[i]=%d,charlas,salas) \n", i, t[i], i, t[i]);

	//Verifico si hay disponibilidad para la charla i
	if (i!=-1 && t[i]!=-1 && !disponible(i,t[i],charlas,salas)){
		//printf("\t Bruto false 2 \n");
		boolean = false;
	}
	//printf("\t t[i=%d]=%d!=-1 && ultimacharla[t[i]=%d]=%d!=-1 && !compatibles(ultimacharla[t[i]=%d]=%d,i=%d,charlas) \n", i, t[i], t[i], ultimacharla[t[i]], t[i], ultimacharla[t[i]], i);
	//Verifico compatibilidad

	if (i!=-1 && t[i]!=-1 && ultimacharla[t[i]]!=-1 && !compatibles(ultimacharla[t[i]],i,charlas)){
	 //if (i!=-1 && t[i]!=-1 && ultimacharla[t[i]]!=-1 &&  charlas[ultimacharla[t[i]]].fin > charlas[i].inicio ){

			//printf("\t Bruto false 1 \n");
			boolean = false;
		}

	//printf("\t Bruto true \n");

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
