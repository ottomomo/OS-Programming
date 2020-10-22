#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
 
int main(void)
{
    FILE* fp = fopen("ficheroEntrada", "r");
    FILE* fpo = fopen("ficheroSalida", "w");
    if(fp == NULL) {
       perror("fopen"); return 1;
    }
 
    struct stat stats;
    if(fstat(fileno(fp), &stats) == -1) { // POSIX only
        perror("fstat"); return 1;
    }
 
    printf("BUFSIZ is %d, but optimal block size is %ld\n", BUFSIZ, stats.st_blksize);
    if(setvbuf(fp, NULL, _IOFBF, stats.st_blksize) != 0) {
       perror("setvbuf failed"); // POSIX version sets errno
       return 1;
    }
 
    int ch;
    while((ch=fgetc(fp)) != EOF)
          fwrite(&ch,1,1,fpo);            
 
    fclose(fp);
    fclose(fpo);
}
