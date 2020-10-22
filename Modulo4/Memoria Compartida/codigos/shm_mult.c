#include "shared.h"


void print_matriz ( float **m, int f, int c )
{
	int i,j;
    printf("-----------------------------------------\n");
    for (i=0 ; i<f ; i++)
    {
    	for (j=0 ; j<c ; j++)
        	printf("%13.5E ",m[i][j]);
        printf("\n");
	}            
    printf("-----------------------------------------\n");        
}

float **crear_matriz(int f, int c, int *shmid)
{
	float **matriz;
    float *addr;
    int i;
    
	*shmid = crear_region(sizeof(float) * f * c, 0600);
    
    addr = (float *) coge_region(*shmid);
    
    matriz = (float **) malloc( f * sizeof(float *) );
    
    matriz[0] = addr;
    
 	for( i=1 ; i<f ; i++ ) 
    	matriz[i] = matriz[i-1] + c;

  	return(matriz);
}    
    

float **get_matriz ( int f, int c, int *shmid )
{
	int i,j;
    float **m;
    
    m = (float **) crear_matriz(f,c,shmid);
    
    for (i=0 ; i<f ; i++)
    	for (j=0 ; j<c ; j++)
        {
        	printf("coef[%i][%i] = ",i,j);
        	scanf("%f",&m[i][j]);
		}    
                
	return m;
}



int main (int argc, char **argv)
{
	int shmidA,shmidB,shmidC;
	float **A,**B,**C;
	int f,c,proc;
    int act = 0;
    int rango,p;
    int i,j,l;    
    
    if (argc == 4)
    {
    	f = atoi(argv[1]);
    	c = atoi(argv[2]);    
        proc = atoi(argv[3]);
	}
    else {
	printf("Usage: ./mult filas cols procesos\n");	
    	exit(0);
      }      
	A = get_matriz(f,c,&shmidA);        
	B = get_matriz(f,c,&shmidB);        
	C = crear_matriz(f,c,&shmidC);            
    
    rango = f / proc;
        
    for (p=0;p <proc;p++)
    {
    	
    	if (fork() == 0)
        {
		// Cada proceso hijo multiplica un grupo de filas desde act hasta act+rango

		printf("Proceso (%i), multiplicando filas %i hasta %i\n"
            	   ,getpid(),act,act+rango);
        	for(l = act ; l < (act + rango) ; l++)
            	{
            		for (j=0;j<c;j++)
                	{
                		C[l][j] = 0;
                    		for (i = 0; i < c ; i++)
                    			C[l][j] += A[act][i] * B[i][j];
			}            
             	}           	
		exit(0);                            
        }    
	// padre
        act=act+rango;            
    }
    
    for (p=0;p <proc;p++)
    	wait(NULL);
        
	print_matriz ( C, f, c );   
        
    borra_region(shmidA);
    borra_region(shmidB);    
    borra_region(shmidC);    
    
    return 0;
}       	
