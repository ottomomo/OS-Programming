#include<errno.h>
#include<stdio.h>
/*
	api1.c
	@author Jorge López Octavio Sales
*/

int main () {

	int f1;
	if((f1=open(0,0))==-1){		//hacemos una llamada erronea...
		perror("main_open_f1: ");
		return -1;
	}
	close(f1);

	return 0;
}
	
