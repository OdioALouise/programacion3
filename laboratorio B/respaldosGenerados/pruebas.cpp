#include <stdio.h>

struct charla
// La duracion (= fin - inicio) es mayor que 0.
{
	int inicio;
	int fin;  
	int asistentes;
};

struct sala
{
	int inicio;
	int fin;  
};

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla, int parche);

int main(){

	int n=3;
	int m=2;

	/*Inicializacion de charlas i salas*/
	charla * charlas = new charla [n];
	sala * salas = new sala [m];

	/*Juego de datos para charlas*/

	//Primera charla
	charlas[0].inicio=9;
	charlas[0].fin=11;
	charlas[0].asistentes=20;

	//Segunda charla
	charlas[1].inicio=8;
	charlas[1].fin=10;
	charlas[1].asistentes=78;

	//Tercera charla
	charlas[2].inicio=11;
	charlas[2].fin=13;
	charlas[2].asistentes=10;

	/*Juego de datos para salas*/
	//Primera sala
	salas[0].inicio=8;
	salas[0].fin=12;

	//Segunda sala
	salas[1].inicio=15;
	salas[1].fin=19;

	//Tercera sala
	salas[2].inicio=13;
	salas[2].fin=17;


	int *solucion = new int[n];	
	int *tupla = new int[n];

	for(int i=0; i < n; i++)
	{
		solucion[i]=-1;
		tupla[i]=-1;
	}


	printf("BackTrackin!! \n");
	
	for(int i=0; i < n; i++)
	{
		for(int j=0; j < n; j++)
		{
			tupla[j]=-1;

		}

 		for(int k=i-1; k < n; k++){
 
			backtracking(charlas, n, salas, m, solucion, i, tupla, k);
		}
	}

	return 0;
}


void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla, int parche)
{

	printf("\n\n");

	for(int k=0; k < n; k++)
	{
		printf("tupla[%d]=%d \n", k, tupla[k]);
	}


	int suma=0;
	for(int l=0; l < 10; l++)
	{
		if(tupla[l]>=0){
			suma+=charlas[l].asistentes;
		}

	}


				for(int xi=0; xi < m; xi++)
				{

							if(i==parche)
								i=i+1;
							if(i<n){
								tupla[i]=xi;
								backtracking(charlas, n, salas, m, solucion, i + 1, tupla, parche);
								if(tupla[i]=m)
									tupla[i]=-1;							
							}
				}
}


