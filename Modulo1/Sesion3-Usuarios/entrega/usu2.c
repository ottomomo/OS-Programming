
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>

char *getlogin(void);

int main()
{
/* Definir apropiadamente usuario y su estructura pw */
  uid_t usuario;       	//user ID
  char   *pw_name;	//user NAME
  char   *pw_passwd;	//user PASSWORD
  struct passwd *pw;
  //struct spwd *spw;
	
	
/* Obtener el uid del proceso */
  usuario = getuid();
    
/* Obtener la informacion de usuario con el identificador */
  pw = getpwuid(usuario); 
  printf("Entro al sistema como:\n name= %s\n uid=%d\n gid=%d\n home=%s\n shell=%s\n", pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);

/* Imprimir el pasword del usuario */
  printf(" Password = %s\n", pw->pw_passwd);
  printf(" El pasword es:%d\n", pw->pw_passwd);
	
/* Tratar de obtener la informacion de usuarioso con getspnam() 
e imprimir el passwd*/
  char *sp_namp;	//user NAME       
  char *sp_pwdp;	//user PASSWORD
  //struct spwd *sp = getspnam(usuario);
  //printf("Entro al sistema sp como:\n name= %s\n, pwd=%d\n", sp->sp_namp, sp->sp_pwdp);
/* Si no es posible usar getspnam(), explica por que y busca una solucion */

    
  return 1;
}    
    
