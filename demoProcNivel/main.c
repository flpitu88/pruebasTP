/*
 * main.c
 *
 *  Created on: 21/11/2013
 *      Author: utnso
 */

#include "/home/utnso/git/tp-2013-2c-sockete-s/librerias/libSockets/cliente.c"
#include "/home/utnso/git/tp-2013-2c-sockete-s/librerias/commons/string.c"
#include "/home/utnso/git/tp-2013-2c-sockete-s/librerias/libSockets/comunes.c"
#include "socket.h"
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
			socklen_t addrlen;
			int i;
			FD_ZERO(&master); // borra el conjunto maestro
			FD_ZERO(&read_fds);// borra el conjunto temporal

			listener = socket_crearServidor("127.0.0.3",puertoPlanificador+50);
			FD_SET(listener, &master); //agrego el listener al master
			fdmax = listener;

			int file_descriptor_inotify;
			if ((file_descriptor_inotify = inotify_init()) < 0) {
				printf("Da error creacion inotify\n");
					}

			inotify_add_watch(file_descriptor_inotify,PATH_CONFIG, IN_MODIFY);
			char buffer[BUF_LEN];
			FD_SET(socketCliente, &master); //METO SOCKET DEL PLANIFICADOR
			if (socketCliente > fdmax) {
				fdmax = socketCliente;
			}
			FD_SET(file_descriptor_inotify, &master); // METO AL DESCRIPTOR EN EL MASTER
			if (file_descriptor_inotify > fdmax) {
				fdmax = file_descriptor_inotify;
			}

			//ITERACION PRINCIPIO--------------------------------

			while(1) {

					read_fds = master; //paso el master a temporal
					if (select(fdmax + 1, &read_fds, NULL, NULL, NULL ) == -1) {

						printf("Error en el select\n");
						exit(1);
					}

					// explorar conexiones existentes en busca de datos que leer
					for (i = 0; i <= fdmax; i++) {
						if (FD_ISSET(i, &read_fds)) { //tengo datos
							if (i == listener) { // gestionar nuevas conexiones

								addrlen = sizeof(remoteaddr);
								if ((newfd = accept(listener,(struct sockaddr*) &remoteaddr, &addrlen)) != -1) {//lo acept��
									FD_SET(newfd, &master); // a��adir al conjunto maestro
									if (newfd > fdmax) { // actualizar el m��ximo
										fdmax = newfd;
									}

									printf(	"\n########################################################################\n"
											"ORQUESTADOR: Nueva Conexion ACEPTADA de la IP: %s en el  "
											"socket %d\n"
											"\n########################################################################\n",
											inet_ntoa(remoteaddr.sin_addr), //imprime IP del que se conecta y el descriptor del socket asociado.
											newfd);

									// Ac�� lo unico que se hace es agregar el descriptor al master, lo cual ya fue hecho un par de lineas arriba en
									// FD_SET(newfd, &master). Luego los gestionar�� cuando me env��en los mensajes correspondientes.


								} else{

										printf("\n########################################################################\n"
										 "Error al hacer Accept Orquestador"
										 "\n########################################################################\n");
								}

							} else
								if(i == file_descriptor_inotify){


						          int length = read(file_descriptor_inotify, buffer, BUF_LEN);

						          if (length < 0) {
						            perror("read");
						          }

						          int offset = 0;
						          while (offset < length / 2) {
						            struct inotify_event *event = (struct inotify_event *) &buffer[offset];
						            if (event->mask & IN_MODIFY) {

						            	printf("Se modifico archivo de configuracion\n");

						                 offset = length / 2;

						            }
						          }


					} else { // gestionar datos de un cliente
							printf("Recibi mensaje de un cliente\n");
								}
							}// end if de tengo datos
						}//end for
					}//end while
				close(puertoPlanificador+50);
				}

			//ITERACION FIN---------------------------------------------------

		}
	cerrar_cliente(socketCliente);
	return 0;
	}


