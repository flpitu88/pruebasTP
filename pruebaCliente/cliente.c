/*
 * cliente.c

 *
 *  Created on: 06/04/2014
 *      Author: utnso
 */

#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "./commons/string.h"
#include "./commons/tad_cliente.h"
#include "./commons/shared_strs.h"

#define IP "127.0.0.1"
#define PORT 5000

/*
 * Prueba de conexion de un cliente utilizando las commons
 * de Fernando con un servidor de ejemplo de la catedra.
 */

int main(void){

	int socketServidor = conectar_a_servidor(IP, PORT);

	if (socketServidor < 0) {
		return EXIT_FAILURE;
	} else {
		printf("Conexion establecida\n");
	}

	int envio = enviar_mensaje_a_servidor(socketServidor, 1, "hola",4);
	printf("Envio datos y da %i\n",envio);

	void* mensajeARecibirAux = recibir_mensaje_de_servidor(socketServidor);
	t_GEN_MSG* mensajeARecibir = (t_GEN_MSG *) mensajeARecibirAux;

	printf("Mensaje recibido tipo %i\n",mensajeARecibir->id_MSJ);

	desconectar_de_servidor(socketServidor);

	return 1;
}
