#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef NONE


int bloquea(int fd, int bloqueo) {
  return 0;
}
#else
int bloquea(int fd, int bloqueo)
{

	struct flock c;

    c.l_type = bloqueo;
    c.l_whence = SEEK_SET;
    c.l_start = 0;
    c.l_len = 0;
    
  /*  if (fcntl(fd,F_SETLKW,&c) == -1 )
    {
    	perror("fcntl");        	
        exit(-1);
    }  */
    if(bloqueo== F_WRLCK){
      if (flock(fd, LOCK_EX) == -1){
	perror("flock");
	exit(-1);
      }
    }else{
      if (flock(fd, LOCK_UN) == -1){
	perror("flock");
	exit(-1);
      }
    }
    return 0;
}
#endif

int main()
{

    int fd;
    int num,i;
    
    /* Apertura del fichero */
    
    fd = open("./temporal", O_CREAT | O_RDWR | O_SYNC, 0666);
    
    /* Comprobacion de errores */
  
    for (i=0; i<10 ; i++)
    {    	
	lseek(fd,0,SEEK_SET);
	bloquea (fd, F_WRLCK);        
        if (read(fd,&num,sizeof(int)) == 0 )
        	num = 0;
    	num++; 
        lseek(fd,0,SEEK_SET);            
	usleep(500000);
        write(fd,&num,sizeof(int));
        printf("(%d) numero = %i\n",getpid(),num);
	bloquea (fd, F_UNLCK);                
	usleep(500000);
    }

    close(fd);
}    