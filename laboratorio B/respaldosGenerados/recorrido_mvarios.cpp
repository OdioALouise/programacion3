#include <stdio.h>

struct charla
// La duracion (= fin - inicio) es mayor que 0.
{
	int inicio;
	int fin;  
	int asistentes;
};

struct sala
// fin > inicio
{
	int inicio;
	int fin;  
};

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla);
bool verificaRest(int *tupla, int i, charla* charlas);
bool esMejor(int *tupla, int *solucion, charla* charlas, int n);
void copiar(int *tupla,int* solucion, int n);
bool esSalaDisponible(charla* charlas, int i, sala* salas, int xi);
bool esSolucion(int *tupla, int n);

int main(){

	int n=3;
	int m=2;

	/*Inicializacion de charlas i salas*/
	charla * charlas = new charla [n];
	sala * salas = new sala [m];

	/*Juego de datos para charlas*/

	// Devuelve sala no disponible primero y sala disponible despues
 
	//Primera charla
	charlas[0].inicio=15;
	charlas[0].fin=17;
	charlas[0].asistentes=10;

	//Segunda charla
	charlas[1].inicio=9;
	charlas[1].fin=10;
	charlas[1].asistentes=2;

	//Tercera charla
	charlas[2].inicio=16;
	charlas[2].fin=19;
	charlas[2].asistentes=3;


	/*Juego de datos para salas*/
	//Primera sala
	salas[0].inicio=10;
	salas[0].fin=20;

	salas[1].inicio=8;
	salas[1].fin=12;

	int *solucion = new int[n];	
	int *tupla = new int[n];

	for(int i=0; i < n; i++)
	{
		solucion[i]=-1;
		tupla[i]=-1;
	}


	printf("BackTrackin!! \n");
	backtracking(charlas, n, salas, m, solucion, 0, tupla);
	
	for(int i=0; i < n; i++)
	{
		for(int j=0; j < n; j++)
		{
			tupla[j]=-1;

		}
		backtracking(charlas, n, salas, m, solucion, i, tupla);

	}

	int suma=0;
	for(int i=0; i < n; i++)
	{
		printf("solucion[%d]=%d \n", i, solucion[i]);
		if(solucion[i]>=0){
			suma+=charlas[i].asistentes;
		}

	}

	printf("Asistentes: %d \n", suma);

	return 0;
}


void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla)
{

	//printf("Valor de i: %d \n", i);

	/*
	for(int h=0; h < 10; h++)
	{
		printf("solucion[%d]=%d \n", h, solucion[h]);
	}*/

	
	/*printf("\n\n");

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

	printf("Asistentes: %d \n", suma);
	*/
	

	if( verificaRest(tupla, i, charlas) )
	{
		if( esMejor(tupla, solucion, charlas, n) )
		{
			if(esSolucion(tupla, n)){
				copiar(tupla, solucion, n);
			}else
			{
				for(int xi=0; xi < m; xi++)
				{

					//printf("\t xi = %d y i=%d \n", xi, i);

					if( esSalaDisponible(charlas, i, salas, xi) )
					{
						if(i<n){
							tupla[i]=xi;
							backtracking(charlas, n, salas, m, solucion, i + 1, tupla);
							if(tupla[i]=m)
								tupla[i]=-1;							
						}
					}
					//else{
					//	printf("\t No hay disponibilidad \n", xi, i);
					//}
				}
			}
		}
	}//else{
	//	printf("No verifica \n");
	//}
}



bool esSolucion(int *tupla, int n){

	for(int j=0; j<=n-1; j++)
	{
		if(tupla[j]<-1)
			return false;
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

//Se actualiza la tupla solucion
void copiar(int *tupla,int* solucion, int n){
	for(int j=0; j<=n-1; j++){
		solucion[j]=tupla[j];
	}
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



//Se debe evaluar la compatibilidad de la charla actual 
//con las charlas anteriores que tienen la misma sala asignada
bool verificaRest(int *tupla, int i, charla* charlas){

	//if(tupla[i-1]<0)
	//	return true;

	for(int j=0; j<i-1; j++)
	{

		//printf("charla[%d].inicio = %d \n", j, charlas[j].inicio);	
		//printf("charla[%d].fin = %d \n", i-1, charlas[i-1].fin);	

		//printf("charla[%d].inicio = %d \n", i-1, charlas[i-1].inicio);	
		//printf("charla[%d].fin = %d \n", j, charlas[j].fin);	

		//printf("Valores de tupla tupla[%d]=%d  tupla[%d]=%d \n", j, tupla[j], i-1, tupla[i-1]);	

		if(tupla[j]==tupla[i-1]){

			if( ! ( ( charlas[j].fin <=  charlas[i-1].inicio) || ( charlas[i-1].fin <=  charlas[j].inicio) ) ){
				//printf("Terrible no verifica \n");
				return false;
			}

		}		
	}
	return true;
}

/*
Juegos de datos para rechazar y aceptar disponibilidad de sala

	//Juego de datos para charlas

	// Devuelve sala no disponible primero y sala disponible despues
	//Primera charla
	charlas[0].inicio=15;
	charlas[0].fin=19;
	charlas[0].asistentes=1;

	//Segunda charla
	charlas[1].inicio=11;
	charlas[1].fin=13;
	charlas[1].asistentes=10;

	//Tercera charla
	charlas[2].inicio=10;
	charlas[2].fin=15;
	charlas[2].asistentes=10;

	//Juego de datos para salas
	//Primera sala
	salas[0].inicio=10;
	salas[0].fin=14;

	//Segunda sala
	salas[1].inicio=15;
	salas[1].fin=19;


	int *solucion = new int[3];	
	int *tupla = new int[3];

	tupla[0]=0;
	tupla[1]=1;
	tupla[2]=-1;

	solucion[0]=-1;
	solucion[1]=-1;
	solucion[2]=1;

	if(esSalaDisponible(charlas, 2, salas, 0))
	{
		printf("Si es disponible \n");	
	}else{
		printf("No es disponible \n");
	}

	if(esSalaDisponible(charlas, 0, salas, 1))
	{
		printf("Si es disponible \n");	
	}else{
		printf("No es disponible \n");
	}


*/

/*
	//Probando la funcion copiar
	int *solucion = new int[3];	
	int *tupla = new int[3];

	tupla[0]=0;
	tupla[1]=1;
	tupla[2]=-1;

	solucion[0]=-1;
	solucion[1]=-1;
	solucion[2]=1;

	for(int j=0; j<=3-1; j++){
		printf("solucion[%d] = %d \n", j, solucion[j]);
	}

	copiar(tupla,solucion, 3);

	for(int j=0; j<=3-1; j++){
		printf("solucion[%d] = %d \n", j, solucion[j]);

	}
*/

/*
Juegos de datos para esMejor

	if(esMejor(tupla, solucion, charlas, 3))
	{
		printf("Si es mejor \n");	
	}else{
		printf("No es mejor \n");
	}


*/

/*
	// Devuelve esMejor true
	//Primera charla
	charlas[0].inicio=10;
	charlas[0].fin=11;
	charlas[0].asistentes=1;

	//Segunda charla
	charlas[1].inicio=11;
	charlas[1].fin=13;
	charlas[1].asistentes=10;

	//Tercera charla
	charlas[2].inicio=10;
	charlas[2].fin=13;
	charlas[2].asistentes=10;

	//Juego de datos para salas
	//Primera sala
	salas[0].inicio=10;
	salas[0].fin=14;

	//Segunda sala
	salas[1].inicio=15;
	salas[1].fin=19;


	int *solucion = new int[3];	
	int *tupla = new int[3];

	tupla[0]=0;
	tupla[1]=1;
	tupla[2]=-1;

	solucion[0]=-1;
	solucion[1]=-1;
	solucion[2]=1;

*/



/*
	// Devuelve esMejor false
	//Primera charla
	charlas[0].inicio=10;
	charlas[0].fin=11;
	charlas[0].asistentes=1;

	//Segunda charla
	charlas[1].inicio=11;
	charlas[1].fin=13;
	charlas[1].asistentes=10;

	//Tercera charla
	charlas[2].inicio=10;
	charlas[2].fin=13;
	charlas[2].asistentes=24;

	//Juego de datos para salas
	//Primera sala
	salas[0].inicio=10;
	salas[0].fin=14;

	//Segunda sala
	salas[1].inicio=15;
	salas[1].fin=19;


	int *solucion = new int[3];	
	int *tupla = new int[3];

	tupla[0]=0;
	tupla[1]=1;
	tupla[2]=-1;

	solucion[0]=-1;
	solucion[1]=-1;
	solucion[2]=1;

*/


/*
para verificaRest

	if(verificaRest(tupla, 2, charlas))
	{
		printf("Si verifica \n");	
	}else{
		printf("No verifica \n");
	}


*/

/*


	// Devuelve verificarRest false
	//Primera charla
	charlas[0].inicio=10;
	charlas[0].fin=11;
	charlas[0].asistentes=1;

	//Segunda charla
	charlas[1].inicio=10;
	charlas[1].fin=13;
	charlas[1].asistentes=10;

	//Tercera charla
	charlas[2].inicio=10;
	charlas[2].fin=13;
	charlas[2].asistentes=4;

	//Juego de datos para salas
	//Primera sala
	salas[0].inicio=10;
	salas[0].fin=14;

	int *solucion = new int[3];	
	int *tupla = new int[3];

	tupla[0]=0;
	tupla[1]=0;
	tupla[2]=-1;


*/


/*

	// Devuelve verificarRest true
	//Primera charla
	charlas[0].inicio=10;
	charlas[0].fin=11;
	charlas[0].asistentes=1;

	//Segunda charla
	charlas[1].inicio=11;
	charlas[1].fin=13;
	charlas[1].asistentes=10;

	//Tercera charla
	charlas[2].inicio=10;
	charlas[2].fin=13;
	charlas[2].asistentes=4;

	//Juego de datos para salas
	//Primera sala
	salas[0].inicio=10;
	salas[0].fin=14;

	//Segunda sala
	salas[1].inicio=15;
	salas[1].fin=19;


	int *solucion = new int[3];	
	int *tupla = new int[3];

	tupla[0]=0;
	tupla[1]=0;
	tupla[2]=-1;


*/
