//Cliente recibiendo mensaje del servidor
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
     int socket_cliente;
     struct sockaddr_in cliente_direccion;
     int tamstructuracliente;
     char ipservidor[10];
     int puerto;
     int estadoConexion; //cuando conecto con el servidor

     char cadenaCliente[1024];
     char cadenaServidor[1024];

     int ciclo =1;
     int inicio_sesion=0;

     //1. socket
     socket_cliente = socket(AF_INET, SOCK_STREAM, 0);
     //1a. configuracion del cliente
     printf("Ingresa la ip del servidor: \n");
     scanf("%s", ipservidor);
     printf("Ingresa el puerto del servidor: \n");
     scanf("%d", &puerto);

 while(ciclo){   
      cliente_direccion.sin_family= AF_INET;  //familia
      cliente_direccion.sin_addr.s_addr = inet_addr(ipservidor); //especifico la direccion donde me conecto
      cliente_direccion.sin_port= puerto; //htons(80); //asignamos el puerto de comunicacion
      tamstructuracliente= sizeof(cliente_direccion);

    //2. connect (peticion de conexion)
       //int connect(int sfd, const void *addr, int addrlen);
       estadoConexion = connect(socket_cliente, (struct sockaddr *)&cliente_direccion,tamstructuracliente );
       if(estadoConexion == -1 ){
         printf("Problemas al conectar con servidor :c \n");
         exit(-1);
         close(socket_cliente);
      }

      //if(inicio_sesion==0){
         printf("/t--Sesion iniciada con el servidor--\n");
      //recibir mensaje del servidor
        recv(socket_cliente, cadenaServidor,1024,0);
        printf("%s \n",cadenaServidor);
        inicio_sesion = 1;
      //}
//3. write()
//Enviamos una mensaje de texto al servidor
       printf("Ingresa un texto para enviarle al servidor:\n");
       scanf("%*c%[^\n]",cadenaCliente);
       send(socket_cliente, cadenaCliente, 1024,0);
//4. read()
 //Recibimos la respuesta del servidor
      recv(socket_cliente,cadenaServidor,1024,0 );
      printf("El servidor contesto: %s \n", cadenaServidor);
      
  }
//5. close()
    close(socket_cliente);

}