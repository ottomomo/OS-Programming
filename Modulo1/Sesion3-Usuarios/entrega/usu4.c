#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
/*Creamos el ejecutable como osuser y activamos el bit de setuid.*/
/*Ejecutamos como usarioso */
/*Hacemos uso de la funcion set y get de uid , euid. Para cambiar los, y que sean diferentes.*/
int main(){
	uid_t uid;
	uid_t euid;         
	uid = getuid();    
	euid = geteuid();
	printf("UID: %d, EUID: %d\n",getuid(),geteuid());
	printf("pulsa una tecla para cambiar los usuarios.\n");
	getc(stdin);
	setreuid(euid, uid);
	printf("UID: %d, EUID: %d\n",getuid(),geteuid());
	printf("pulsa una tecla para cambiar los usuarios.\n");
	getc(stdin);
	setreuid(uid, euid);
	printf("UID: %d, EUID: %d\n",getuid(),geteuid());
	return 1;
}
/*setreuid() Unprivileged users may only set the real user ID to the real user ID or the effective user ID.*/