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

void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla);
bool verificaRest(int *tupla, int i, charla* charlas);
bool esSalaDisponible(charla* charlas, int i, sala* salas, int xi);
bool esMejor(int *tupla, int *solucion, charla* charlas, int n);
bool esSolucion(int *tupla, int n);
void copiar(int *tupla,int* solucion, int n);

int main(){

	int n=10;
	int m=4;

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

	//Cuarta charla
	charlas[3].inicio=9;
	charlas[3].fin=11;
	charlas[3].asistentes=5;

	//Quinta charla
	charlas[4].inicio=8;
	charlas[4].fin=12;
	charlas[4].asistentes=10;

	//Sexta charla
	charlas[5].inicio=13;
	charlas[5].fin=16;
	charlas[5].asistentes=40;


	//Septima charla
	charlas[6].inicio=15;
	charlas[6].fin=17;
	charlas[6].asistentes=12;

	//Octava charla
	charlas[7].inicio=17;
	charlas[7].fin=19;
	charlas[7].asistentes=5;

	//Novena charla
	charlas[8].inicio=16;
	charlas[8].fin=17;
	charlas[8].asistentes=8;

	//Decima charla
	charlas[9].inicio=13;
	charlas[9].fin=17;
	charlas[9].asistentes=54;

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

	//Cuarta sala
	salas[3].inicio=9;
	salas[3].fin=13;

	int *solucion = new int[n];	
	int *tupla = new int[n];

	for(int i=0; i < n; i++)
	{
		solucion[i]=-2;
		tupla[i]=-2;
	}


	printf("BackTrackin!! \n");
	
	backtracking(charlas, n, salas, m, solucion, 0, tupla);

	printf("Solucion!! \n");
	
	for(int k=0; k < n; k++)
	{
		printf("solucion[%d]=%d \n", k, solucion[k]);
	}


	int suma=0;
	for(int l=0; l < n; l++)
	{
		if(solucion[l]>=0){
			suma+=charlas[l].asistentes;
		}

	}

	printf("Asistentes: %d \n", suma);
	

	return 0;
}


void backtracking(charla* charlas, int n, sala* salas, int m, int *solucion, int i, int *tupla)
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

	printf("Asistentes: %d \n", suma);
	
	
	if(verificaRest(tupla, i, charlas)){
		//if(esMejor(tupla, solucion, charlas, n)){

				if(esSolucion(tupla, i) && esMejor(tupla, solucion, charlas, n)){
					copiar(tupla,solucion, n);
				}

				for(int xi=-1; xi < m; xi++)
					{

						printf("Nos movemos a evaluar charla %d en sala %d \n", i, xi);
						if( (xi < 0) || esSalaDisponible(charlas,i, salas, xi) ){
								if(i<n){
									tupla[i]=xi;
									backtracking(charlas, n, salas, m, solucion, i + 1, tupla);
									if(tupla[i]=m)
										tupla[i]=-2;							
								}
						}else{
							printf("No es sala disponible \n");
						}
					}
		//}
	}
else{
		printf("No verifica restricciones \n");
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


	printf("Asistentes tuplas %d -- Asistentes solucion %d", asistentes_tupla, asistentes_solucion);
	if(asistentes_tupla<asistentes_solucion)
		return false;	
	return true;
}

bool esSolucion(int *tupla, int n){

	if(n==10)
		return true;

/*	for(int j=0; j<=n-1; j++)
	{
		if(tupla[j]<-1)
			return false;
	}
*/
	return false;
}


//Se actualiza la tupla solucion
void copiar(int *tupla,int* solucion, int n){
	for(int j=0; j<=n-1; j++){
		solucion[j]=tupla[j];
	}
}

/*
	//Juego de datos para charlas

	//Primera charla
	charlas[0].inicio=9;
	charlas[0].fin=11;
	charlas[0].asistentes=20;

	//Segunda charla
	charlas[1].inicio=8;
	charlas[1].fin=10;
	charlas[1].asistentes=78;

	//Tercera charla
	charlas[2].inicio=15;
	charlas[2].fin=19;
	charlas[2].asistentes=10;

	//Juego de datos para salas
	//Primera sala
	salas[0].inicio=8;
	salas[0].fin=12;

	//Segunda sala
	salas[1].inicio=15;
	salas[1].fin=19;

	//Tercera sala
	salas[2].inicio=13;
	salas[2].fin=17;


*/

