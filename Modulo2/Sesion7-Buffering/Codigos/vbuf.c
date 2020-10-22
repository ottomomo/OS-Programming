#include <stdio.h>
#include <unistd.h>

int main() {
 int i = 0;
 //setvbuf(stdout,(char*)NULL,_IONBF,BUFSIZ);
 
 for (i = 0; i< 5; i++) {
	printf("Esta es la ");
  	sleep(1);	
	printf("Linea %d\n", i);
	getc(stdin);
 }
 printf("Final\n");
}
