#include "mensaje.h"


/// nuestra base de datos con nombres y telefonos
dato_t bd[50];

/// posición de la bd en la que escribiremos a continuación
int i = 0;

int main(int argc, char **argv)
{
    int msg_cs, msg_sc;
    key_t llave;
    msg_t msg;
    int fin = 0;
    pid_t pid;
    int k;
    

   //// CREAR las 2 colas de mensajes usando KEYFILE y TOK_SC / TOK_CS respectivamente
    llave  = .....;
    msg_sc = ....; 
    
    llave  = ....;
    msg_cs = ....;
    
    printf("Servidor Activo\n");
    
   while (!fin)
    {
	/// RECIBIR MENSJAE (guardlo en msg)    
        
	............
	printf("Mensaje recibido del proceso %d\n",msg.tipo);
        
        switch(msg.op)
        {
        	case LIST:
            
            	printf("Opcion de listado, creando un hijo para atenderla \n");
            	pid = fork();
                
                if (pid == 0)
                {
                     // Recorremos nuestra base de datos y copiamos las cadenas de caracteres en el mensaje que envviaremos
		    for (k=0;k<i;k++)
                    {
                    	printf("Proceso hijo enviado mensaje %i/%i\n",k,i);
                        strcpy(msg.dato.nombre,bd[k].nombre);
                    	strcpy(msg.dato.telf,bd[k].telf);
                        
                        msgsnd(msg_sc,&msg,LONG,0);
		    }
                    
 		    // COMPLETAR: enviar un mensaje con el campo op a FIN para que el cliente sepa que no hay más mensajes
                    .............
 
                    exit(0);
                                            
                };
            break;
            case ADD:
			/// COMPLETAR: añandir los datos recibidos en el mensaje a nuestra base de datos (nombre y telf)	
			strcpy(bd[i].nombre,..........);
			strcpy(.......);
			i = i + 1;                
            break;
            case FIN:
            	printf("Eliminando colas y saliendo\n");                    	
		// COMPLETAR: eliminar colas y poner fin a 1 para terminar
		..............
                fin = 1;            
            break;            
	}        
    };
                        
    return 1;
}    
