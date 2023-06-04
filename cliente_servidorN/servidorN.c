//Servidor enviando mensaje a cliente
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>//familia inet
//#include <sys/un.h> //familia unix
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(){
     struct sockaddr_in servidor_direccion; //es una estructura donde se define (puertos, direcciones, familia)
     struct sockaddr_in cliente_direccion;  //es donde defino las caracteristicas del cliente
     int tamstructuraservidor;
     int tamstructuracliente;
     int puerto;

     int socket_servidor, socket_cliente; //es el que se le asigna al socket sfd (socket_descriptor)
     int socket_bind;  //recibe el valor del bind
     int socket_listen;

     char mensajedelCliente[1024];
     char mensajedelServidor[1024];
    
     int ciclo =1;
     int inicio_sesion=0;

     printf("Creando el servidor en la ip 127.0.0.1 :\n");
    
//1. Declarar el socket  -Apertura del canal
      socket_servidor = socket(AF_INET, SOCK_STREAM,0);  //socket(tipo_familia, comportamiento, protocolo);
      //verifico si todo va bien
//1a. Inicializarlo
      if(socket_servidor == -1){
        printf("No se puede crear el socket \n");
        exit(-1);
      }
      printf("Ingrese el puerto de escucha:\n");
      scanf("%d", &puerto);

//1b. Configuracion -direccion,puerto etc.
      servidor_direccion.sin_family= AF_INET;  //familia
      servidor_direccion.sin_addr.s_addr = inet_addr("127.0.01"); //especifico la direccion donde me conecto
      servidor_direccion.sin_port= puerto; //htons(80); //asignamos el puerto de comunicacion
      tamstructuraservidor= sizeof(servidor_direccion);

//2. Usar el metodo bin- Publicidad de la direccion (conectar el socket con el puerto o direccion)
     
     //int bind (int sfd, const void *addr, int addrlen);
     socket_bind = bind(socket_servidor,(struct sockaddr *)&servidor_direccion,tamstructuraservidor );
     if(socket_bind == -1){
        printf("No se puede crear el bind \n");
        exit(-1);
      }

//3. Usar listen  -Disposicion de acpetar conexiones
      //int listen (int sfd, int backlog);
      socket_listen = listen(socket_servidor,2); //voy a escuchar a 2 clientes
      if(socket_listen == -1){
        printf("No se puede crear el listen \n");
        exit(-1);
      }
      printf("Servidor en espera de peticion cliente....\n");
//4. Usar accept()  - Aceptar una conexion. Bloquea el proceso hasta que reciba una peticion de conexion
      //int accept (int sfd, void *addr, int  *addrlen);

     while(ciclo){
      socket_cliente = accept(socket_servidor,(struct sockaddr *)&cliente_direccion,&tamstructuracliente );
      if(socket_cliente == -1){
        printf("No se puede crear el accept \n");
        exit(-1);
      }

     // if(inicio_sesion==0){
         printf("/tCliente inicio sesion\n");
         printf("-- CLIENTE YA CONECTADO--\n");
         //enviaremos mensajes al cliente
         strcpy(mensajedelServidor, "----El servidor te da la Bienvenida ---");
         send(socket_cliente,mensajedelServidor, 1024, 0 );
         inicio_sesion=1;
   //   }
 //5. Usar read() - Lectura de la peticion del servicio (cliente)
//recibimos lo que envia el cliente(peticion)
      recv(socket_cliente,mensajedelCliente,1024,0);
      printf("El cliente me envio el siguiente mensaje: %s\n",mensajedelCliente);

      //ahora el servidor envia mensaje
      printf("Ingrese una cadena para el cliente: \n");
      scanf("%*c%[^\n]",mensajedelCliente);
      send(socket_cliente,mensajedelCliente, 1024,0);

      close(socket_cliente);
    }
 
   close(socket_servidor);
}