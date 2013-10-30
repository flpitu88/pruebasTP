
#include "/home/utnso/git/tp-2013-2c-sockete-s/librerias/libSockets/cliente.c"
#include "/home/utnso/git/tp-2013-2c-sockete-s/librerias/commons/msgIds.h"
#include "/home/utnso/git/tp-2013-2c-sockete-s/librerias/commons/string.h"


#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PUERTO_SERVIDOR 5000
#define IP_SERVIDOR "127.0.0.1"

void imprimirRecibido(struct NIPC recibido){
    printf("Recibido mensaje del tipo: %d\n",recibido.Type);
    printf("Mje recibido: %s\n",recibido.Payload);
    printf("Longitud recibido: %d\n",recibido.Length);
}

int main(void){

    int socketServidor;
    struct sockaddr_in socketInfo;
    struct NIPC datosRecibidos;
    //struct NIPC datosEnviar;
    char id = '#';
    char recBusco = 'H';

    inicializar_cliente(&socketInfo, &socketServidor,IP_SERVIDOR,PUERTO_SERVIDOR);

    mandarMensaje(&id,PJE_MJE_CONECT,socketServidor);


    while (1){

    datosRecibidos = esperarDatos(socketServidor);

    if (datosRecibidos.Type == PJE_MJE_SUTURNO){

    //el personaje intentaria conectarse al nivel
    mandarMensaje(&id,NIVEL_MJE_AGREGARPJE,socketServidor);
    datosRecibidos = esperarDatos(socketServidor);
    imprimirRecibido(datosRecibidos);

    //el personaje pide ubicacion de un recurso
    mandarMensaje(&recBusco,NIVEL_MJE_GETPOSMUEVO,socketServidor);
    datosRecibidos = esperarDatos(socketServidor);
    imprimirRecibido(datosRecibidos);
        }
    }

    return 0;
}
