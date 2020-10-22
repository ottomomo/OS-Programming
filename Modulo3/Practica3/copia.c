#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUF_SIZE 4

ssize_t copia(int fdo, int fdd){
	
  ssize_t ret_in, ret_out;    
  char buffer[BUF_SIZE];     
      
  while((ret_in = read (fdo, &buffer, BUF_SIZE)) > 0){
    ret_out = write (fdd, &buffer, (ssize_t) ret_in);
  }

  close(fdo);
  close(fdd);

  return ret_out;

}