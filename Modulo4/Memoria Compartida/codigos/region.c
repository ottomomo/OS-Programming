#include "shared.h"

/* Funcion para la creación de una región de memoria compartida */
/* La creación se realiza en función de los defines, PATH y ID  */

int crear_region(size_t size, mode_t modo) {

  key_t  llave;
  int    shmid;

  // Crear tokens para el nuevo segmento
  // CUIDADO: esta funcion se puede invocar varias veces
  // para crear diferentes regiones de memoria compartida
  //llave = ftok("/home/usuarioso", 1234);
  
  llave = ftok(PATH, ID);
  if (llave == (key_t) -1) 
  {
    perror("crear_region: ftok");
    exit(1);
  }

//// Crear segmento de memoria compartida
  shmid = shmget(llave, size, IPC_CREAT | IPC_EXCL | modo);

  if (shmid == -1) 
  {
    perror("crear_region: shmget");
    exit(1);
  }
  
  return shmid;
}

/* Funcion para "pegarse" a una region de memoria compartida */

void *coge_region(int shmid)
{
  void  *addr;  

  // Vincular segmento de memoria compartida
 shmctl(int shmid, int cmd, struct shmid_ds *buf)
 if (addr == (void *) -1) 
  {
    perror(" coge_region: shmat");
    exit(1);
  }
  return addr;
}

/* Funcion para "despegarse" de una region de memoria compartida */

void suelta_region(void * addr)
{
  // COMPLETAR
  if (shm...... == -1) 
  {
    perror("suelta_region: shmdt");
    exit(1);
  }
}

/* Funcion para eliminar una region de memoria compartida */

void borra_region(int shmid)

  // COMPLETAR
  if (shmctl(......) == -1) {
    
    if (errno == EPERM) 
    	return;
    else 
    	if (errno == EINVAL) 
      		return;
   	else 
        {
      		perror("borrar_region: shmctl");
      		exit(1);
    	}
  }
}
