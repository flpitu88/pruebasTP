/*
 * detecDeadlock.h
 *
 *  Created on: 28/07/2013
 *      Author: utnso
 */

#ifndef DETECDEADLOCK_H_
#define DETECDEADLOCK_H_

#include "/home/utnso/git/tp-2013-2c-sockete-s/procNivel/nivelTad.h"
#include "/home/utnso/git/tp-2013-2c-sockete-s/librerias/commons/collections/queue.h"

//---------------------------TADS-----------------------------------

struct matriz_de_recursos{
	char* personajesId;
	char* recursosId;
	int** cantidad;
	int xSize;
	int ySize;
};
typedef struct matriz_de_recursos M_RECURSOS;

//.............................

struct vector_de_recursos{
	char* recursosId;
	int* cantidad;
	int size;
};
typedef struct vector_de_recursos V_RECURSOS;

//.............................

struct vector_de_personajes{
	char* personajeId;
	int* marcado;
	int size;
};
typedef struct vector_de_personajes V_PERSONAJES;

//--------------------------------------------------------------------

V_RECURSOS* crearVector(int tamanio);
void destruirVector(V_RECURSOS* rec_vector);
M_RECURSOS* crearMatriz(int m,int n);
void destruirMatriz(M_RECURSOS* rec_matriz);
V_PERSONAJES* crearVectorPers(int tamanio);
void destruirVectorPers(V_PERSONAJES* per_vector);
void cargarEtiquetasVecPersonajes(NIVEL_INST* nivel, V_PERSONAJES* vector);
void cargarMatrizAsignados(NIVEL_INST* nivel,M_RECURSOS* m_asignados);
void cargarMatrizSolicitados(NIVEL_INST* nivel, M_RECURSOS* m_solicitados);
void cargarVectorTotales(NIVEL_INST* nivel, V_RECURSOS* r_totales);
void cargarVectorDisponibles(M_RECURSOS* asignados, V_RECURSOS* totales, V_RECURSOS* disponibles);
void marcarPersonaje(V_PERSONAJES* marcados,char id);
void informarBloqueados(V_PERSONAJES* marcados);
int estaMarcado(V_PERSONAJES* marcados,char id);
int puedeCumplirDemanda(V_RECURSOS* recursosDispo, M_RECURSOS* recSolicito, V_PERSONAJES* marcados);
int esMayor(V_RECURSOS* recursosDispo, M_RECURSOS* recSolicito,int i);
int getCantPersonajes(NIVEL_INST* nivel);
int getCantRecursos(NIVEL_INST* nivel);
int getFilaDelPersonaje(char id,M_RECURSOS* matriz);
void imprimirMatriz(M_RECURSOS* matriz);
void imprimirVector(V_RECURSOS* vector);
void imprimirVectorPers(V_PERSONAJES* vector);
int detectarDeadlock(M_RECURSOS* m_asignados,M_RECURSOS* m_solicitados,V_RECURSOS* r_totales,V_RECURSOS* r_disponibles,V_PERSONAJES* marcados);

#endif /* DETECDEADLOCK_H_ */
