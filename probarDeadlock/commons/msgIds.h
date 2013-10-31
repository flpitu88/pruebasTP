#ifndef MSGIDS_H_
#define MSGIDS_H_

/*
 *
 *  Created on: 02/10/2013
 *      Author: utnso
 */


/*
 * MENSAJES QUE ENVIA EL NIVEL
 */

#define NIVEL_MJE_INICIAR 0
#define NIVEL_MJE_DAMENRONIVEL 1 //no necesita payload
#define NIVEL_MJE_EJECUTATURNO 2 //no necesita payload
#define NIVEL_MJE_DIBUJA 3 //no necesita payload
#define NIVEL_MJE_TOMARREC 4 //en payload por ej. "#F" primero id del personaje y despues id del recurso que queire pedir
#define NIVEL_MJE_IMPRIMIRCONFIG 5 //no necesita payload
#define NIVEL_MJE_POSXITEM 6 //
#define NIVEL_MJE_POSYITEM 7 //
#define NIVEL_MJE_UBICOCUPADA 8 // no necesita payload
#define NIVEL_MJE_MOVERPJE 9 //en payload por ej. "#r" primero id del personaje y depsues direccion de movimiento ('r', 'l', 'u', 'd') right, left, up, down
#define NIVEL_MJE_UBICLIBRE 10 //en payload por ej. "24&12" primero coordenada x despues coordenada y. El & es el separador
#define NIVEl_MJE_DEVOLREC 11 //en payload vienen todos los recursos por ej. "$FMFCHF&" '&' Es el caracter delimitador. Se pone el id personaje al principio
#define NIVEL_MJE_AGREGARPJE 12 //en payload viene el id del personaje a agregar por ej. "&"
#define NIVEL_MJE_IMPRIMIRPJES 13 //no necesita payload
#define NIVEL_MJE_GETPOSMUEVO 14 //en payload viene el id del recurso a buscar. Por ej "F"
#define NIVEL_MJE_RECPOS 15 //Retorno posicion del recurso en payload como "12&34" . idem codigo 10
#define NIVEL_MJE_GETALGO 16 //en payload va el char* con el algoritmo
#define NIVEL_MJE_GETQUAN 17 //en payload va por ej. "10" Es un char* que se debe convertir a int
#define NIVEL_MJE_GETRETARD 18 //en payload va por ej. "10" Es un char* que se debe convertir a int
#define NIVEL_MJE_RECOVERY 19 //en payload va por ej. "10" Es un char* que se debe convertir a int
#define NIVEL_MJE_TICHEQ 20 //en payload va por ej. "10" Es un char* que se debe convertir a int
#define NIVEL_MJE_SLEEP 21 //en payload va por ej. "10" Es un char* que se debe convertir a int
#define NIVEL_MJE_PERSOFF 22 //en payload vienen todos los recursos por ej. "$FMFCHF&" '&' Es el caracter delimitador. Se pone el id personaje al principio


#define PJE_MJE_CONECT 100 // Se conecta al servidor un personaje.
#define PJE_MJE_SUTURNO 101 // Turno asignado al personaje




/* NIVEL_MJE_HANDSHAKE
 * Envia un mensaje de bienvenida con el numero de nivel
 * PL: (char*) SALUDO Ej. "¡HOLA! Soy el planificador del Nivel 7"
 */
#define NIVEL_MJE_HANDSHAKE 150

/* NIVEL_MJE_TURNO
 * El nivel avisa que es el turno del personaje
 * S/PL
 */
#define NIVEL_MJE_TURNO 151

/* NIVEL_MJE_MUERTE_ENEMIGO
 * Avisa al personaje que lo mato un enemigo.
 * S/PL
 */
#define NIVEL_MJE_MUERTE_ENEMIGO 180

/* NIVEL_MJE_MUERTE_IB
 * Avisa al personaje que murio como victiva de interbloqueo.
 * S/PL
 */
#define NIVEL_MJE_MUERTE_IB 181

/* NIVEL_MJE_MUERTE_ERROR
 * Avisa al personaje que murio por algun motivo que puede ser incluso que se murio el nivel
 * S/PL
 */
#define NIVEL_MJE_MUERTE_ERROR 182




/*
 * MENSAJES QUE ENVIA EL PERSONAJE
 */

/* PJE_MJE_HANDSHAKE
 * Envia un mensaje de bienvenida con el nombre del personaje
 * PL: (char*) SALUDO Ej. "¡HOLA! Soy Mario"
 */
#define PJE_MJE_HANDSHAKE 200

/* PJE_MJE_HOST_NIVEL
 * Solicita el host del planificador al orquestador
 * PL: (int) NIVEL Ej. 15
 */
#define PJE_MJE_HOST_NIVEL 201

/* PJE_MJE_PERSONAJE
 * Devuelve el nombre del personaje
 * PL: (char *) PERSONAJE Ej. "Mario"
 */
#define PJE_MJE_PERSONAJE 202

/* PJE_MJE_SIMBOLO
 * Devuelve el simbolo del personaje
 * PL: (char *) SIMBOLO Ej. "@"
 */
#define PJE_MJE_SIMBOLO 203

/* PJE_MJE_ENNIVEL 22
 * Se envia el simbolo el personaje al principio, y luego los objetivos, mas un delimitador.
 * PL: (char *) PAYLOAD Ej. "$FMFCHF&" '&' Es el caracter delimitador.
 */
#define PJE_MJE_ENNIVEL 22

/* PJE_MJE_MUERTE
 * El personaje avisa que murio
 * S/PL
 */
#define PJE_MJE_MUERTE 250











/*
 * MENSAJES QUE ENVIA EL ORQUESTADOR
 */

/* ORQ_MJE_HANDSHAKE
 * Envia un mensaje de bienvenida
 * PL: (char*) SALUDO Ej. "¡HOLA! Soy el orquestador"
 */
#define ORQ_MJE_HANDSHAKE 300

/* ORQ_MSJ_HOST_NIVEL
 * El orquestador devuelve el host del planificador solicitado.
 * PL: (char*) IP:PUERTO Ej. "000.000.000.000:00000"
 */
#define ORQ_MSJ_HOST_NIVEL 301







#endif /* MSGIDS_H_ */
