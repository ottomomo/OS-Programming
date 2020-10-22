#include <unistd.h>

int main() {

  //Crea un fichero (open)
	open("fich.txt", O_CREATE, 664);
	int status=0;
	char *path1 = "/home/usuarioso/Descargas/Sesion6/codigos/fich.txt";
	char *path2 = "/home/usuarioso/Descargas/Sesion6/codigos/linkFich";
  /* Creacion de un enlace hard */
  if(status=(link(path1, path2)==-1){
	perror("link: ");
  }

  /* Enlace simbolico */
  if(status=(symlink(..., ...)==-1){
	perror("symlink: ");
  }
 
  // Usar lstat para ver el tamaño de ambos 
  return 0;
}
