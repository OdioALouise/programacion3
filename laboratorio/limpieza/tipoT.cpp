#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "tipoT.h"
#include <sstream>

using namespace std;

bool esMayor (tipoT t1, tipoT t2){
	if(t1>t2)
		return true;
	return false;
}

bool esMenor (tipoT t1, tipoT t2){
	if(t1<t2)
		return true;
	return false;
}

bool esIgual (tipoT t1, tipoT t2){
	if(t1==t2)
		return true;
	return false;
}

unsigned int hash (tipoT t){
	return t;
}

tipoT stringAtipoT (char * string){
	int n=0;
	int i=0;
	for (n = 0; isdigit(string[i]); i++)
		n = 10 * n + (string[i] - '0');
	return n;
}

char* tipoTAstring (tipoT t){

	char* puntero;
	puntero = new char[80];	
	sprintf(puntero,"%d",t); 

	return puntero;
}
