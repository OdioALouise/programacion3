#include "Congreso.h"
#include <stdio.h>

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla);
bool disponible (int chini, int chfin, int sini, int sfin);
bool compatibles (int chiini, int chifin, int chjini, int chjfin);
bool verificaRest (int *t, int i, charla *charlas); 
bool esMejor(int tn, int sn);
void copiar(int *tupla,int* solucion, int n);
bool predicado(int tn, int tn1, int sn);
void SelectionSort(charla* charlas, int* indices, int n);
bool greedy(charla *charlas, int* t, int n, int i);

int ruido(sala *salas, charla *charlas, int *tupla, int n, int m, int i );


int* max_asistentes_m (charla* charlas, int n, sala* salas, int m)
{
	int *solucion = new int[n+1];	
	int *tupla = new int[n+2];

	int *indices = new int[n];
	int *posta = new int[n];	


	tupla[n+1]=0;

	for(int i=0; i < n; i++)
	{
		solucion[i]=-1;
		tupla[i]=-1;
		tupla[n+1]+=charlas[i].asistentes;
		indices[i]=i;
		posta[i]=-1;
	}


	solucion[n]=0;
	tupla[n]=0;

	SelectionSort(charlas, indices, n);

	backtracking(charlas, n, salas, m, solucion, 0, tupla);

	int suma=0;

	printf("Veamos los indices de charlas \n");
	for(int i=0; i < n; i++)
	{
		posta[indices[i]]=solucion[i];
		if(solucion[i] >=0){
			suma+=charlas[i].asistentes;
		}
	}


	for(int i=0; i < n; i++)
	{
		printf("posta[%d]=%d \n", i, posta[i]);
	}

	printf("Asistentes: %d \n", suma);

	
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
	if(predicado(tupla[n], tupla[n+1], solucion[n])){
		//if(verificaRest(tupla, i, charlas)){
			if( esMejor(tupla[n], solucion[n])){
				copiar(tupla,solucion, n);
			}
			
			for(int j=i; j<n; j++){

				for(int xi=0; xi < m; xi++)
				{

					if ( (xi < 0) ||  disponible(charlas[j].inicio,  charlas[j].fin, salas[xi].inicio, salas[xi].fin)  ){
		

							if(j<n){
								tupla[j]=xi;

								if(xi>=0){
									tupla[n]+=charlas[j].asistentes;
									tupla[n+1]-=charlas[j].asistentes;
								}

								if( j==0 || greedy(charlas,  tupla, n,  j) ){
									backtracking(charlas, n, salas, m, solucion, j+1, tupla);
								}
					
								if(xi>=0){
									tupla[n]-=charlas[j].asistentes;
									tupla[n+1]+=charlas[j].asistentes;
								}

								if(tupla[j]=m)
									tupla[j]=-1;
							}//jmenorn
					}//restricciones 

				}//for1
			}//for 2

		//}//restricciones implicitas
	}
}

bool greedy(charla *charlas, int* t, int n, int i){

	int j = 0;

	bool boolean = true;

	//printf("valor de i %d \n", i);
	
		while ((j<i) && boolean)
		{
		 //printf("\t \t t[j]=%d != -1 y  t[i-1]=%d == t[j]=%d ? \n", t[j], t[i-1],t[j]);

			if(t[j]!=-1){
				if (t[j]==t[i] &&  !compatibles( charlas[j].inicio, charlas[j].fin, charlas[i].inicio, charlas[i].fin ))
					boolean = false;
			}
			j++;
		}

	return boolean;
}



bool predicado(int tn, int tn1, int sn)
{
	if(tn + tn1 <= sn)
		return false;
	return true;
}

bool compatibles (int chiini, int chifin, int chjini, int chjfin)
{
	if ((chiini>=chjfin) || (chifin<=chjini))
		return true;
	else
		return false;
}



 //Disponibilidad charla-sala
bool disponible (int chini, int chfin, int sini, int sfin)
{
	if ((chini>=sini) && (chfin<=sfin))
		return true;
	else
		return false;
}

//Se debe evaluar la compatibilidad de la charla actual 
//con las charlas anteriores que tienen la misma sala asignada
bool verificaRest (int *t, int i, charla *charlas) //Verifica si las restricciones se cumplen
{ 
	int j = 0;

	bool boolean = true;

	//printf("valor de i %d \n", i);
	
		while ((j<i-1) && boolean)
		{
		// printf("\t \t t[j]=%d != -1 y  t[i-1]=%d == t[j]=%d ? \n", t[j], t[i-1],t[j]);

			if ( t[j]!=-1 && (t[i-1]==t[j]) && !compatibles( charlas[j].inicio, charlas[j].fin, charlas[i-1].inicio, charlas[i-1].fin ))
				boolean = false;
			j++;
		}

	return boolean;
}



//Determina si la cantidad de asistentes de la tupla es mayor
//que la cantidad de asistentes de la tupla solucion
bool esMejor(int tn, int sn){
	if(tn<sn)
		return false;	
	return true;
}

//Se actualiza la tupla solucion
void copiar(int *tupla,int* solucion, int n){
	for(int j=0; j<=n; j++){
		solucion[j]=tupla[j];
	}
}


int ruido(sala *salas, charla *charlas, int *tupla, int n, int m, int i ){
	bool compatible=true;

	//Para cada charla desde i+1 hasta n-1
	for(int a= i+1; a<n ; a++){

		compatible=true;

		//printf(" Indice a %d \n", a);
		for(int b=0; b<=i && compatible; b++){
			//printf("\t  Indice b %d \n", b);

			if( compatibles( charlas[a].inicio, charlas[a].fin, charlas[b].inicio, charlas[b].fin ) ){
				//printf("\t\t  %d es compatible con %d \n", a, b);
				return a;
			}else{
				compatible=false;
			}
		}

		if(!compatible){
			for(int c=0; c<m; c++){
				bool disp=false;
				//printf("\t  Indice c %d \n", c);
				for(int d=0; d<=i && !disp; d++){
					if(c == tupla[d])
						disp=true;						
				}
				if(!disp){

					if( disponible(charlas[a].inicio,  charlas[a].fin, salas[c].inicio, salas[c].fin ) ){
						//printf("Encontramos sala \n");
						return a;
					}					
				}

			}
		}
		
	}

	return n;
}
