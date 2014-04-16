#include <stdint.h>
/*ID MENSAJES PLATAFORMA PERSONAJE COMIENZO*/
#define HANDSHAKE_PERSONAJE_ORQUESTADOR 1 //acepta conexion de personaje con su plan de nivel. El orquetador lo delega al planificador correspondiente
#define UBICACION_CAJA 3 // Pide la ubicacion de la caja de recursos que necesita.
#define MUERTE_PERSONAJE 11 // Notifica la muerte del personaje
#define MOVIMIENTO_PERMITIDO 19
#define MUERTE_CORRECTA 35
/*ID MENSAJES PLATAFORMA PERSONAJE FIN*/

/*ID MENSAJES PLATAFORMA NIVEL COMIENZO*/
#define HANDSHAKE_NIVEL_ORQUESTADOR 4 //acepta conexion de nivel
#define RECURSOS_LIBERADOS 41
#define CAMBIO_CRITERIO 45
#define DETECCION_DEADLOCK 47
#define MUERTE_ANORMAL 51
#define BLOQUEO_PERSONAJE 15 // Notifica el bloqueo del personaje
#define INICIALIZAR_PERSONAJE 53
#define PERSONAJE_LIBERADO 55
#define CAJA_FUERA_DE_LIMITE 57
#define PERSONAJE_NO_LIBERADO 59
/*ID MENSAJES PLANIFICADOR NIVEL FIN*/

/*ID MENSAJES PLATAFORMA/PERSONAJE/NIVEL COMIENZO*/
#define PEDIR_RECURSO 9
#define SIN_RECURSOS 23
#define CON_RECURSOS 25
#define AVISO_MOVIMIENTO 5 // Le avisa que se va a mover
#define FINALIZAR 7 // Avisa el personaje que no tiene mas recursos que obtener, por ende termina
#define MOVIMIENTO_EXITO 31 // Mensaje del planificador por si el movimiento se dio con exito
#define MUERTE_ALCANCE_ENEMIGO 43
#define MUERTE_POR_DEADLOCK 33 // Mensaje por si muere por deadlock
#define CONTINUA_NIVEL 37 // Mensaje por si el personaje fue desbloqueado y procede a continuar
#define TERMINA_NIVEL 39 // Mensaje por si el personaje fue desbloqueado y procede a terminar el nivel
#define ME_QUEDE_SIN_VIDAS 49
/*ID MENSAJES PLANIFICADOR/PERSONAJE/NIVEL FIN*/

typedef struct strGenMsg { // estructura generica, debe estar en todas las estructuras
	int id_MSJ;
	int disconnected;
	int socket_descriptor;
	int socket_descriptor_server;
	int size_str;
} __attribute__ ((__packed__)) t_GEN_MSG;

/*ESTRUCTURAS PLATAFORMA PERSONAJE COMIENZO*/
typedef struct strPlatPerNiv {
	t_GEN_MSG gen_msg;
	//Campos PER_NIVE_PLAT
	char simbolo;
	int nivel;
	int handshake_ok;
	char caja;
	int x;
	int y;
	int soy_personaje;

	//Campos NIV_PLAT
	int quantum;
	int algoritmo;
	int retardo;
	char personajes_liberados[256];
	char recursos_liberados[256];
	char personajes[256];
	char ubicacion_recursos[256];

	//Campos PER_PLAT
	char plan_nivel[256];
	int cantidad_niveles;

}__attribute__ ((__packed__)) t_PLAT_PER_NIV;

char* id_a_mensaje(int id);
