#include "mensaje.h"

dato_t bd[50];
int i = 0;

int main(int argc, char **argv)
{
	int msg_cs, msg_sc;
    key_t llave;
    msg_t msg;
    int fin = 0;
    pid_t pid;
    int k;
    char op;
    
	setbuf(stdout,NULL);        
    //// CREAR las 2 colas de mensajes usando KEYFILE y TOK_SC / TOK_CS respectivamente
    llave  = .....;
    msg_sc = ....; 
    
    llave  = ....;
    msg_cs = ....;
        
    
    printf("Cliente Activo\n");
    
    msg.tipo = getpid();
    
   while (!fin)
    {
    	printf("Operacion(l,a,f): ");
		scanf("%s",&op);           
                
        switch(op)
        {
           case 'l':
		/// ENVIAR mensjae con op LIST
               ...........

		/// RECIBIR MENSAJE CON respuesta 
		...........

                while(msg.op != FIN)
                {
                	printf("Nombre: %s\n",msg.dato.nombre);
                    	printf("Telf: %s\n\n",msg.dato.telf);
		  	// RECIBIR MENSAJE con respuesta	
			...
                }    
            	break;
            case 'a':
                
            		printf("Nombre: ");
			scanf("%s",msg.dato.nombre);                           
            		printf("Telf: ");
			scanf("%s",msg.dato.telf);                                 
               		// ENVIAR mensaje con op ADD 
			.....
            		break;
            case 'f':
            		// ENVIAR mensaje con op FIN
			......
                	fin = 1;
            		break;            
            default:
            	break;
	  }        
	};
                        
    return 1;
}    
