#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>

typedef struct sockaddr_in INTERNET_SOCKET;

int enviar_mensaje_a_servidor(int socket_descriptor, int id_MSG, void *message, int size_str);
int conectar_a_servidor(char* unaIP, int unPuerto);
void desconectar_de_servidor(int sock_descriptor);
void* recibir_mensaje_de_servidor(int sock_descriptor);
void* recibir_mensaje_de_servidor_wa(int sock_descriptor);

