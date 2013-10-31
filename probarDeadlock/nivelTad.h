/*
 * nivelTad.h
 *
 *  Created on: 13/10/2013
 *      Author: utnso
 */

#ifndef NIVELTAD_H_
#define NIVELTAD_H_

#include "tad_items.h"
#include "./nivel-gui/nivel.h"
#include "./commons/config.h"


/*
 * Creo estructura que contiene los datos
 * representativos de un nivel
 */
struct level{
	char nombre[7];
	t_list* listaItems;
	t_list* listaPersonajes;
	char plataforma[20];
	int deadCheqTime;
	int recovery;
	int cantEnemigos;
	int sleepEnemigos;
	char algoritmo[2];
	int quantum;
	int retardo;
	t_config* configuracion;
};
typedef struct level NIVEL_INST;

/*
 * Tipo de dato abstracto que representa un personaje
 */
struct personaje {
	char id;
	t_list* listaRecursos;
	char recBloqueo;
};
typedef struct personaje T_PERSONAJE;


/*
 * Funcion que crea la estructura y retorna un puntero
 */
NIVEL_INST* generarNivel();


/*
 * Funcion que carga la estructura del nivel, con su configuracion y sus cajas
 */
void cargarNivel(NIVEL_INST* nivel,char* path);

/*
 * Funcion que imprime la configuracion del nivel para chequear si es correcta.
 */
void printConfig(NIVEL_INST* nivel);

void cargoConfig(NIVEL_INST* nivel, char* path);

void printListaPersonajes(t_list* listaItems);

void cargoCajas(NIVEL_INST* nivel);

void dibujarNivel(NIVEL_INST* nivel);

void agregarPersonajeEnLista(NIVEL_INST* nivel, char idPers);

void moverPersonaje(char idPersonaje, NIVEL_INST* nivel, char sentido);

void tomarRecurso(NIVEL_INST* nivel, char idRec, char idPersonaje);

void devolverRecurso(NIVEL_INST* nivel, char recurso);

void desconectarPersonaje(NIVEL_INST* nivel, char pje);

void agregarRecursoPje(NIVEL_INST* nivel, char idRec, char idPers);

int getAlgoritmo(NIVEL_INST* nivel);

void sacarRecursoPersonaje(NIVEL_INST* nivel, char idPersonaje, char idRec);

int getIndiceListaRecursos(t_list* listaRec, char idRec);

void printRecursosPersonaje(NIVEL_INST* nivel, char personaje);

int getRetardo(NIVEL_INST* nivel);

int getQuantum(NIVEL_INST* nivel);

int getRecovery(NIVEL_INST* nivel);

int getTiempoChequeo(NIVEL_INST* nivel);

int getSleep(NIVEL_INST* nivel);

int getPosicionX(NIVEL_INST* nivel, char idItem);

int getPosicionY(NIVEL_INST* nivel, char idItem);

int estaLibre(NIVEL_INST* nivel, int posx, int posy);

ITEM_NIVEL* getPunteroItem(NIVEL_INST* nivel, char id);

T_PERSONAJE* getPunteroPersonaje(NIVEL_INST* nivel, char id);

#endif /* NIVELTAD_H_ */
