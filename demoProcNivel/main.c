/*
 * main.c
 *
 *  Created on: 21/11/2013
 *      Author: utnso
 */

#include "/home/utnso/git/tp-2013-2c-sockete-s/librerias/libSockets/cliente.c"
#include "/home/utnso/git/tp-2013-2c-sockete-s/librerias/commons/string.c"
#include "/home/utnso/git/tp-2013-2c-sockete-s/librerias/libSockets/comunes.c"
#include "socket.c"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/inotify.h>
#include <errno.h>
#include <sys/types.h>


#define PUERTO_SERVIDOR 5000
#define IP_SERVIDOR "127.0.0.1"
#define PATH_CONFIG "/home/utnso/git/tp-2013-2c-sockete-s/procNivel/config/nivel1.cfg"
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * EVENT_SIZE)
#define MIN_LOG LOG_LEVEL_TRACE

struct NIPC datosRecibidos;
struct NIPC datosAEnviar;
struct NIPC reportDeadlock;
struct NIPC reportEnemigo;
struct NIPC reportNotify;
//----------- Parametros de conexion de nivel como cliente a plataforma --------------
int socketCliente;
struct sockaddr_in socketInfo;
//------------------------------------------------------------------------------------
int iExitCode = 0; // variable global, cada error esperado se informa con esta variable
int puertoPlanificador;
int file_descriptor_inotify;

//---------------------------------------------------------------------------------------------------

void imprimirMensaje(struct NIPC recibido){
    printf("Recibido mensaje del tipo: %d\n",recibido.Type);
    printf("Mje recibido: %s\n",recibido.Payload);
    printf("Longitud recibido: %d\n",recibido.Length);
}

//---------------------------------------------------------------------------------------------------


int main(void){
	// Me conecto al orquestador
	inicializar_cliente(&socketInfo, &socketCliente,IP_SERVIDOR,PUERTO_SERVIDOR);
	mandarMensaje("1",50, socketCliente);
	// Recibo datos del orquestador
	datosRecibidos = esperarDatos(socketCliente);

	if (datosRecibidos.Type != 201){ // usar 50 pero pongo el numero no lo encuentra
		iExitCode = -1;
		printf("No recibo mensaje del puerto planificador, recibo %i\n",datosRecibidos.Type);

	} else {
		//Se recibio conexion con el orquestador.

		imprimirMensaje(datosRecibidos);
		puertoPlanificador = atoi(datosRecibidos.Payload);
		//Cierro conexion con el orquestador
		cerrar_cliente(socketCliente);
		//Realizo conexion con el planificador
		inicializar_cliente(&socketInfo,&socketCliente,IP_SERVIDOR,puertoPlanificador);
		mandarMensaje("1",50, socketCliente);
		datosRecibidos = esperarDatos(socketCliente);
		//Espero respuesta del planificador
		if (datosRecibidos.Type != 130){
			iExitCode = -1;
		} else {
						//Instancio y cargo el nivel
			int algor = 2;
			char* quantum;
			if (algor == 0){
				quantum = "0";
			} else {
				quantum = string_itoa(algor);
			}
			//Mando mensaje al planificador con 0, si es el algoritmo del mas cercano, o el quantum si es RR.
			mandarMensaje(quantum,25,socketCliente);

			fd_set master; // conjunto maestro de descriptores de socket
			fd_set read_fds; // conjunto temporal de descriptores de socket para select()
			int fdmax; // nï¿½ï¿½mero mï¿½ï¿½ximo de descriptores de socket
			int listener; // descriptor de socket a la escucha
			struct sockaddr_in remoteaddr; // direcciï¿½ï¿½n del cliente
			int newfd; // descriptor de socket de nueva conexiï¿½ï¿½n aceptada
			int nbytes;
			socklen_t addrlen;
			int i;
			FD_ZERO(&master); // borra el conjunto maestro
			FD_ZERO(&read_fds);// borra el conjunto temporal

			listener = socket_crearServidor("127.0.0.1", PUERTO); //aca ya estï¿½ï¿½ hecho el bind y el listen.
			FD_SET(listener, &master); //agrego el listener al master
			fdmax = listener;

		}
	}
	cerrar_cliente(socketCliente);
	return 0;
}
