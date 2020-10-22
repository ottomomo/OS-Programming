#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
/*El bit SUID activado sobre un fichero indica que todo aquél que ejecute el archivo va a tener durante la ejecución los mismos privilegios que quién lo creó; dicho de otra forma, si el administrador crea un fichero y lo setuida, todo aquel usuario que lo ejecute va a disponer, hasta que el programa finalice, de un nivel de privilegio total en el sistema*/

/*EL ejecutable tiene que tener el bit de setuid activo, para poder ejecutar el archivo con los mismo permisos de quien lo creó (usuarioso, root o quien sea...) . 
 Comando para activar el bit: chmod u+s usu3 */
#define usuarioso 1001	/* uid de usuarioso */
/*
int main(){
  
	uid_t uid;         // Declaramos el tipo de dato que contendrá el UID (es un int).
	uid = getuid();    // La función retorna el ID del usuario que llamó al proceso.
	if(uid != 0){      // Si no es 0, no es root.
	  	printf("ERROR: Debes lanzar el programa como \"root\".\n");
	  	return -1;
	}else{
		printf("UID: %d, EUID: %d\n",getuid(),geteuid());
		printf("CTRL + C para terminar proceso\n");
	//}
	while(1);	//Bucle infinito para ver en otra shell el proceso y su id.
	return 0;
}*/

/*Referencia: https://www.ibiblio.org/pub/linux/docs/LuCaS/Manuales-LuCAS/SEGUNIX/unixsec-2.1-html/node56.html*/
int main(){
	uid_t uid;         
	uid = getuid();
	if(uid != 0){      // Si no es 0, no es root.
	  	printf("ERROR: Debes lanzar el programa como \"root\".\n");
	  	return -1;
	}else{
	    printf("UID: %d, EUID: %d\n",getuid(),geteuid());
	    seteuid(usuarioso);
	    int i;
	    printf("UID: %d, EUID: %d\n",getuid(),geteuid());
	   // for(i=0;i<99999999;i++){};
	    printf("pulsa una tecla para volvcer a cambiar a root\n");
	    getc(stdin);
	}
	setuid(uid);
	printf("UID: %d, EUID: %d\n",getuid(),geteuid());
	return 0;
}
	  