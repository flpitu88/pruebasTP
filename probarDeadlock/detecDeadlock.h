/*
 * detecDeadlock.h
 *
 *  Created on: 28/07/2013
 *      Author: utnso
 */

#ifndef DETECDEADLOCK_H_
#define DETECDEADLOCK_H_

//#include "libNivel.h"
#include "commons/collections/queue.h"

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

//--------------------------------------------------------------------

V_RECURSOS* crearVector(int tamanio);
void destruirVector(V_RECURSOS* rec_vector);
M_RECURSOS* crearMatriz(int m,int n);
void destruirMatriz(M_RECURSOS* rec_matriz);
//void cargarMatrizAsignados(NIVEL_INST* nivel,M_RECURSOS* m_asignados);
//void cargarMatrizSolicitados(NIVEL_INST* nivel, M_RECURSOS* m_solicitados);
//void cargarVectorTotales(NIVEL_INST* nivel);
//void cargarVectorDisponibles(NIVEL_INST* nivel, V_RECURSOS* recursosDispo);
void marcarPersonaje(t_queue* marcados,char id); //funciona
void informarBloqueados();
int estaMarcado(t_queue* marcaddddzxczcos,char id);
int puedeCumplirDemanda(V_RECURSOS* recursosDispo, M_RECURSOS* recSolicito);
int esMayor(V_RECURSOS* recursosDispo, M_RECURSOS* recSolicito,int i);
int getFilaDelPersonaje(char id,M_RECURSOS* matriz);
void imprimirMatriz(M_RECURSOS* matriz);
void imprimirVector(V_RECURSOS* vector);
int detectarDeadlock(M_RECURSOS* m_asignados,M_RECURSOS* m_solicitados,V_RECURSOS* r_totales,V_RECURSOS* r_disponibles);

#endif /* DETECDEADLOCK_H_ */
