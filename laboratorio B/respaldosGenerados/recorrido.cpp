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
bool disponible (int chini, int chfin, int sini, int sfin);
bool compatibles (int chiini, int chifin, int chjini, int chjfin);
bool verificaRest (int *t, int i, charla *charlas); 
bool esMejor(int tn, int sn);
void copiar(int *tupla,int* solucion, int n);
bool predicado(int tn, int tn1, int sn);
int ruido(sala *salas, charla *charlas, int *tupla, int n, int m, int i );


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


	printf("BackTrackin!! \n");

	//printf("Ruido imprime %d \n", ruido(salas, charlas, tupla, n, m, 1 ) );

	//backtracking(charlas, n, salas, m, solucion, 0, tupla);
	backtracking(charlas, n, salas, m, solucion,  0, tupla);

	//backtracking(charlas, n, salas, m, solucion, 0, tupla);

	//for(int i=0; i < n; i++)
	//{
	//	for(int j=0; j < n; j++)
	//	{
	//		tupla[j]=-1;
	//	}

		//printf("Es la vuelta i=%d \n", i);
 		//for(int k=i; k < n; k++){
/*		for(int k=0; k < n; k++){
			for(int c=k; c<n; c++){

			printf("\t No se pasa para k=%d mas este incremento %d \n", k, c-k);
			if(k==0){
					backtracking(charlas, n, salas, m, solucion, 0, tupla, k, c-k);
				}else{bool predicado(int *tupla, int *solucion, int n){
	if(tupla[n] + tupla[n+1] <= solucion[n])
		return false;
	return true;
}
					backtracking(charlas, n, salas, m, solucion, 0, tupla, k, c-k + 1);
				}
			}
		}
	//}
*/
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

	printf("%d \n", i);

	for(int k=0; k < n; k++)
	{
		printf("tupla[%d]=%d \n", k, tupla[k]);
	}


	printf("Asistentes en tupla: %d \n", tupla[n]);
	printf("Asistentes que quedan tupla: %d \n", tupla[n + 1]);
	printf("Asistentes que hay en solucion: %d \n", solucion[n]);

	if(predicado(tupla[n], tupla[n+1], solucion[n])){
		if(verificaRest(tupla, i, charlas)){
			if( esMejor(tupla[n], solucion[n])){
				copiar(tupla,solucion, n);
			}
			
			for(int j=i; j<n; j++){

				for(int xi=0; xi < m; xi++)
				{

					if ( (xi < 0) || disponible(charlas[j].inicio,  charlas[j].fin, salas[xi].inicio, salas[xi].fin )){
		

							if(j<n){
								tupla[j]=xi;

								if(xi>=0){
									tupla[n]+=charlas[j].asistentes;
									tupla[n+1]-=charlas[j].asistentes;
								}

	//							printf("Con vual voy ? %d --- con cual iria %d ?\n", j + 1, ruido(salas, charlas, tupla,  n,  m, j ) );
//
								backtracking(charlas, n, salas, m, solucion, ruido(salas, charlas, tupla,  n,  m, j ), tupla);
//
								//backtracking(charlas, n, salas, m, solucion, j+1, tupla);
					
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
}

//Tengo que fijarme la compatibilidad de las charlas que estan mas halla  
//de la charla i con i y antes.


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
