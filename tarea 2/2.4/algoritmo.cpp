//La primera fila de la matriz g corresponde a los estados considerando el ultimo elemento del arreglo charlas
int albañilyosoy(int *charlas, int cantidadObjetos , int inicioSala, int finSala)
{
	//Inicialización de tabla
	int cantHoras=0;
	int ui=0;
	for(int i = inicio; i < fin; i++)
		cantHoras++;
	int g[cantidadObjetos + 1][cantHoras +1]

	//Inicialización ultima fila
	for(int c=0; c<=cantHoras; c++)
		g[cantidadObjetos][c]=0;
	//Recorrida de filas desde la (n – 1)-ésimas filas de la matriz, columna a columna
	for(int  j = cantidadObjetos -1; j>=0; j--){
		ui=siguienteCompatible( charlas, (cantidadObjetos  - 1)- j, cantidadObjetos);
		for(int c=0; c <= cantHoras; c++){
			if(charlas[(cantidadObjetos  - 1) - j].fechafin <= c + inicioSala){
				g[j][c]=max(charlas[(cantidadObjetos  - 1) - j].asistentes + g[ui][charlas[(cantidadObjetos  - 1) \ 
					- j].fechainicial, g[j+1][c] )
			}
			else
				g[j][c]=g[j+1][c]
		}
	}
	return g[0][cantHoras]
}

//La función devuelve el índice de la fila en la tabla de estados de la charla anterior compatible mas próxima a la charla j.
int siguienteCompatible( int charlas; int j; int cantidadObjetos){
	indice=(cantidadObjetos - 1 - j)
	for(int  h = j-1; h>=0;  h--){
		if(charla[h].fechafinal <=  charlas[j].fechainicial )
			return indice + (j-h);
	}
	return cantidadObjetos;
}

//Calculo de la matriz p para obtener valores optimos
//int optimo[cantidadObjetos + 1][cantHoras +1]
int albañilyosoy(int *charlas, int cantidadObjetos , int inicioSala, int finSala, int &optimo)
{
	//Inicialización de tabla
	int cantHoras=0;
	int ui=0;
	for(int i = inicio; i <= fin; i++)
		cantHoras++;
	int g[cantidadObjetos + 1][cantHoras +1]
	int optimo[cantidadObjetos + 1][cantHoras +1]

	//Inicialización ultima fila
	for(int c=0; c<=cantHoras; c++){
		g[cantidadObjetos][c]=0;
		optimo[cantidadObjetos][c]=0;
	}

	//Recorrida de filas desde la (n – 1)-ésimas filas de la matriz, columna a columna
	for(int  j = cantidadObjetos -1; j>=0; j--){
		ui=siguienteCompatible( charlas, j, cantidadObjetos);
		for(int c=0; c <= cantHoras; c++){
			if(charlas[(cantidadObjetos  - 1)) - j].fechafin < c + inicioSala){
				if(charlas[(cantidadObjetos  - 1) - j].asistentes + g[ui][(cantidadObjetos  - 1) - j].fechainicial \
														>= g[j+1][c]){
					g[j][c]=charlas[(cantidadObjetos  - 1) - j].asistentes + g[ui][charlas[(cantidadObjetos  - 1) \ 
														- j].fechainicial;
					optimo[j][c]=j;
				}else{
					g[j][c]=g[j+1][c];
					optimo[j][c]=optimo[j+1][c];
				}
			}
			else{
				g[j][c]=g[j+1][c];
				optimo[j][c]=optimo[j+1][c];
			}
		}
	}
	return g[0][cantHoras]
}
