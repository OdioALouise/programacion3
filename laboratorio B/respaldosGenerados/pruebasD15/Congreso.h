#ifndef _PTRES_H
#define _PTRES_H

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



int* max_asistentes_m (charla* charlas, int n, sala* salas, int m);
/*
'charlas' es un array de tamaño 'n' y 'salas' es un array de tamaño 'm'.
Devuelve un array de tamaño 'n' que representa la sala a la que es
asignada cada charla.
La i-esima posicion del array devuelto corresponde a la i-esima charla. 
Es la sala a la que fue asignada, que es un número entre 0 y m - 1,
o -1 si no fue asignada.
La asignación debe maximizar la cantidad de asistentes a las charlas.
Los intervalos de desarrollo de dos charlas asignadas a la misma sala
no pueden superponerse.
El intervalo de tiempo de una charla debe estar contenido en la de la
sala a la que sea asignada.
*/




#endif /* PTRES */
