#include <stdio.h>
#include <string.h>

void foo(char* s) {

	unsigned char buf[16];
	strcpy(buf,s);
	return;
}

int main(int argc, char** argv) {

	printf("Llamo a foo\n");
	foo(argv[1]);
	printf("Justo tras foo\n");
	printf("Despues del printf\n");

	return 1;
}
