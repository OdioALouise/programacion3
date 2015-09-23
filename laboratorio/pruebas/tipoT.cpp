#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "tipoT.h"
#include <iostream>
#include <sstream>

using namespace std;

bool esMayor (tipoT t1, tipoT t2){
	if(t1>t2)
		return true;
	else
		return false;
}

bool esMenor (tipoT t1, tipoT t2){
	if(t1<t2)
		return true;
	else
		return false;
}

bool esIgual (tipoT t1, tipoT t2){
	if(t1==t2)
		return true;
	else
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

void reverse(char s[])
 {
	 int c, i, j;
	 for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		 c = s[i];
		 s[i] = s[j];
		 s[j] = c;
	 }
 }


void itoa(int n, char s[])
 {
	 int i, sign;
	 if ((sign = n) < 0) /* record sign */
		 n = -n; /* make n positive */
	 i = 0;
	 do { /* generate digits in reverse order */
		 s[i++] = n % 10 + '0'; /* get next digit */
	 } while ((n /= 10) > 0); /* delete it */
	 if (sign < 0)
		 s[i++] = '-';
	 s[i] = '\0';

	 reverse(s);
 }


char* tipoTAstring (tipoT t){

	char* puntero;
	puntero = new char[80];	
	sprintf(puntero,"%d",t); 

	//string Result;

/*ostringstream convert;

convert << Number;    

Result = convert.str();*/

	//return s;
	return puntero;
}
