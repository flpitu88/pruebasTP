#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log_app.h"
#include "tad_cliente.h"
#include "shared_strs.h"

void* recibir_mensaje_de_servidor(int sock_descriptor) {
	//begin log
//	char log_text[500];
//	sprintf(log_text, "Esperando mensaje del servidor por socket %d",sock_descriptor);
//	log_debug_message(log_text);
	//end log
	int nbytes_peek_rec = 0;
	t_GEN_MSG * peek;
	peek = (t_GEN_MSG *) malloc(sizeof(t_GEN_MSG));
	nbytes_peek_rec = recv(sock_descriptor, peek, sizeof(t_GEN_MSG), MSG_PEEK);
	if (nbytes_peek_rec < 0) {
		//beging log
//		sprintf(log_text,
//				"Error al recibir mensaje peek del servidor por socket %d",
//				sock_descriptor);
//		log_error_message(log_text);
		//end log
		return NULL ;
	} else if (nbytes_peek_rec == 0) {
		//beging log
//		sprintf(log_text,
//				"Error al recibir mensaje peek del servidor por socket %d llego con 0 bytes",
//				sock_descriptor);
//		log_error_message(log_text);
		return NULL ;
		//end log
	}

	void *response_message;
	response_message = (void *) malloc(peek->size_str);
	int nbytes_rec = 0;
	nbytes_rec = recv(sock_descriptor, response_message, peek->size_str,
			MSG_WAITALL);

	if (nbytes_rec < 0) {
		//beging log
//		sprintf(log_text, "Error al recibir mensaje del servidor por socket %d",
//				sock_descriptor);
//		log_error_message(log_text);
		//end log
		return NULL ;
	} else if (nbytes_rec == 0) {
		//beging log
//		sprintf(log_text,
//				"Error al recibir mensaje del servidor por socket %d llego con 0 bytes",
//				sock_descriptor);
//		log_error_message(log_text);
		return NULL ;
		//end log
	}

	t_GEN_MSG * temp = (t_GEN_MSG *) response_message;

	//beging log
//	sprintf(log_text,
//			"Mensaje recibido del servidor por socket %d con id %d:%s y tamanio buffer %d bytes",
//			sock_descriptor, temp->id_MSJ, id_a_mensaje(temp->id_MSJ),temp->size_str);
//	log_trace_message(log_text);
	//end log

	return response_message;
}


void* recibir_mensaje_de_servidor_wa(int sock_descriptor) {
	//begin log
//	char log_text[500];
//	sprintf(log_text, "Esperando mensaje del servidor por socket %d",sock_descriptor);
//	log_debug_message(log_text);
	//end log

	t_PLAT_PER_NIV*response_message;
	response_message = (void *) malloc(sizeof(t_PLAT_PER_NIV));
	int nbytes_rec = 0;
	nbytes_rec = recv(sock_descriptor, response_message, sizeof(t_PLAT_PER_NIV),
			MSG_WAITALL);

	if (nbytes_rec < 0) {
		//beging log
//		sprintf(log_text, "Error al recibir mensaje del servidor por socket %d",
//				sock_descriptor);
//		log_error_message(log_text);
		//end log
		return NULL ;
	} else if (nbytes_rec == 0) {
		//beging log
//		sprintf(log_text,
//				"Error al recibir mensaje del servidor por socket %d llego con 0 bytes",
//				sock_descriptor);
//		log_error_message(log_text);
		return NULL ;
		//end log
	}

	//beging log
//	sprintf(log_text,
//			"Mensaje recibido del servidor por socket %d con id %d:%s y tamanio buffer %d bytes",
//			sock_descriptor, response_message->gen_msg.id_MSJ, id_a_mensaje(response_message->gen_msg.id_MSJ),response_message->gen_msg.size_str);
//	log_trace_message(log_text);
	//end log

	return response_message;
}


int enviar_mensaje_a_servidor(int socket_descriptor, int id_MSG, void *message,
		int size_str) {
	t_GEN_MSG* gen_msg = (t_GEN_MSG *) message;

	gen_msg->disconnected = 0;
	gen_msg->id_MSJ = id_MSG;
	gen_msg->socket_descriptor = socket_descriptor;
	gen_msg->size_str = size_str;
	//begin log
//	char log_text[500];
//	sprintf(log_text, "Enviando mensaje a servidor por socket %d con id %d:%s",
//			socket_descriptor, id_MSG,id_a_mensaje(id_MSG));
//	log_debug_message(log_text);
	//end log

	int i = send(socket_descriptor, message, size_str, 0);

	if (i >= 0) {
		//begin log
//		sprintf(log_text, "Mensaje enviado a servidor por socket %d con id %d:%s",
//				socket_descriptor, id_MSG,id_a_mensaje(id_MSG));
//		log_trace_message(log_text);
		//end log
	} else {
		//begin log
//		sprintf(log_text,
//				"Error al enviar datos a servidor por socket %d con id %d:%s",
//				socket_descriptor, id_MSG,id_a_mensaje(id_MSG));
//		log_error_message(log_text);
		//end log
	}

	return i;
}
int conectar_a_servidor(char* unaIP, int unPuerto) {
	//begin log
	//char log_text[500];
	//sprintf(log_text, "Conectando con ip %s puerto %d", unaIP, unPuerto);
	//log_debug_message(log_text);
	//end log

	int unSocket;

	INTERNET_SOCKET socketInfo;

	if ((unSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		//begin log
		//sprintf(log_text, "Error al crear socket con ip %s puerto %d", unaIP,
		//		unPuerto);
		//log_error_message(log_text);
		//end log
		return unSocket;
	}

	socketInfo.sin_family = AF_INET;
	socketInfo.sin_addr.s_addr = inet_addr(unaIP);
	socketInfo.sin_port = htons(unPuerto);

	// Conectar el socket con la direccion 'socketInfo'.
	if (connect(unSocket, (struct sockaddr*) &socketInfo, sizeof(socketInfo))
			!= 0) {
		//begin log
		//sprintf(log_text, "Error al conectar socket con ip %s puerto %d", unaIP,
		//		unPuerto);
		//log_error_message(log_text);
		//end log
		return -1;
	}

	//begin log
	//sprintf(log_text, "Conectado con ip %s puerto %d y socket descriptor %d",
//			unaIP, unPuerto, unSocket);
	//log_trace_message(log_text);
	//end log

	return unSocket;
}
void desconectar_de_servidor(int sock_descriptor) {
	//begin log
	//char log_text[500];
	//sprintf(log_text, "Cerrando socket %d", sock_descriptor);
	//log_debug_message(log_text);
	//end log

	close(sock_descriptor);

	//beging log
	//sprintf(log_text, "Socket cerrado: %d", sock_descriptor);
	//log_trace_message(log_text);
	//end log

}
