#include <stdio.h>



void crearGrafo(int filas, int columnas, int **&grafo){
	grafo=new int *[filas];
	for(int i = 0; i <columnas; i++)
	    grafo[i] = new int[10];

	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			grafo[i][j]=0;
		}
	}



};


bool esVacio(int filas, int columnas, int **&grafo){
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			if(!grafo[i][j])
				return false;
		}
	}
	return true;
}


void agregarArista(int i, int j, int **&grafo) {
        grafo[i][j] = true;
        grafo[j][i] = true;
    }

void removerArista(int i, int j, int **&grafo) {
        grafo[i][j] = false;
        grafo[j][i] = false;
    }

void imprimirGrafo(int filas, int columnas, int **&grafo){

	printf("MATRIZ \n");

	for(int i = 0; i < filas; i++){
		printf("Fila %d \n", i);
		for(int j = 0; j < columnas; j++){
			printf("%d \t ", grafo[i][j]);
		}
		printf("\n");
	}

}


int main(){

	int **grafo;
	grafo=NULL;
	crearGrafo(10, 10, grafo);
	if(!esVacio(10, 10, grafo))
		printf("Es vacio bo");

	agregarArista(2,1, grafo);	
	agregarArista(3,3, grafo);

	imprimirGrafo(10, 10,grafo);

	removerArista(1, 2, grafo);
	removerArista(3, 3, grafo);

	imprimirGrafo(10, 10,grafo);


	return 0;
}
