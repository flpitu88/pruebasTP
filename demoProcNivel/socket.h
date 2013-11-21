/*
 * socket.h
 *
 *  Created on: 23/04/2013
 *      Author: cristiann91
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "string.h"


#define MAX_CONNECTION_SERVER 10 //VAMOS A ATENDER DE A 10 CONEXIONES COMO MAXIMO A LA VEZ

// Estructura para paquetizar datos a enviar/recibir
typedef struct {
	uint8_t tipo;
	uint16_t length;
} t_socketHeader;

typedef uint8_t t_tipoEstructura;

//FUNCIONES PARA EL CLIENTE
int socket_crearCliente(void);
int socket_conectarCliente(int sockfd,char *serverIp, int serverPort);
int socket_crearYConectarCliente(char *serverIp, int serverPort);

//FUNCIONES PARA EL SERVIDOR
int socket_crearServidor(char *ip, int port);
int socket_crearServidorPuertoRandom(char *ip, int * port);
int socket_aceptarCliente(int socketEscucha);

//FUNCIONES COMUNES
int socket_enviar(int socketReceptor, t_tipoEstructura tipoEstructura, void* estructura);
int socket_recibir(int socketEmisor, t_tipoEstructura * tipoEstructura, void** estructura);
int socket_cerrarConexion(int socket);


#endif /* SOCKET_H_ */
