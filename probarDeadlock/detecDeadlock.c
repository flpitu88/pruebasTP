/*
 * detecDeadlock.c
 *
 *  Created on: 28/07/2013
 *      Author: utnso
 */

#include "detecDeadlock.h"
#include <stdlib.h>
#include <stdio.h>

int** marcados;
int cantRecursos;
int cantPersonajes;

//-------------------------------------------------------------

//A definir
//void cargarMatrizAsignados(NIVEL_INST* nivel,M_RECURSOS* m_asignados){}
//void cargarMatrizSolicitados(NIVEL_INST* nivel, M_RECURSOS* m_solicitados){}
//void cargarVectorTotales(NIVEL_INST* nivel){}


void informarBloqueados(V_PERSONAJES* marcados){
	int i=0;
	for (i=0;i<marcados->size;i++){
		if (marcados->marcado[i]==0){
			printf("El personaje %c se encuentra bloqueado\n",marcados->personajeId[i]);
		}
	}
}

//-------------------------------------------------------------

V_RECURSOS* crearVector(int tamanio){
	V_RECURSOS* rec_vector = malloc(sizeof(V_RECURSOS));
	rec_vector->cantidad = malloc(tamanio*sizeof(int));
	rec_vector->recursosId = malloc(sizeof(char[tamanio]));
	rec_vector->size=tamanio;
	return rec_vector;
}

//-------------------------------------------------------------

void destruirVector(V_RECURSOS* rec_vector){
	free(rec_vector->recursosId);
	free(rec_vector->cantidad);
	free(rec_vector);
}

//-------------------------------------------------------------

M_RECURSOS* crearMatriz(int m,int n){
	M_RECURSOS* rec_matriz = malloc(sizeof(M_RECURSOS));
	rec_matriz->cantidad = (int **)malloc(m*sizeof(int*));
	int i;
	for (i=0;i<m;i++)
			(rec_matriz->cantidad)[i] = (int*)malloc(n*sizeof(int));
	rec_matriz->personajesId = malloc(sizeof(char[m]));
	rec_matriz->recursosId = malloc(sizeof(char[n]));
	rec_matriz->xSize = m;
	rec_matriz->ySize = n;
	return rec_matriz;
}

//-------------------------------------------------------------

void destruirMatriz(M_RECURSOS* rec_matriz){
	free(rec_matriz->cantidad);
	free(rec_matriz->personajesId);
	free(rec_matriz->recursosId);
	free(rec_matriz);
}

//-------------------------------------------------------------

V_PERSONAJES* crearVectorPers(int tamanio){
	V_PERSONAJES* per_vector = malloc(sizeof(V_PERSONAJES));
	per_vector->marcado = malloc(tamanio*sizeof(int));
	per_vector->personajeId = malloc(sizeof(char[tamanio]));
	per_vector->size=tamanio;
	return per_vector;
}

//-------------------------------------------------------------

void destruirVectorPers(V_PERSONAJES* per_vector){
	free(per_vector->personajeId);
	free(per_vector->marcado);
	free(per_vector);
}

//-------------------------------------------------------------

/*
void cargarVectorDisponibles(NIVEL_INST* nivel, V_RECURSOS* recursosDispo){
	if (nivel->listaItems != NULL){
		ITEM_NIVEL* aux = nivel->listaItems;
		int i=0;
		while (aux != NULL){
			if (aux->item_type == '1'){
				recursosDispo->recursosId[i] = aux->id;
				recursosDispo->cantidad[i] = aux->quantity;
			}
			aux = aux->next;
			i++;
			}
		} else {
			printf("Error, lista vacia de items\n");
		}
}
*/

//-------------------------------------------------------------

int getFilaDelPersonaje(char id,M_RECURSOS* matriz){
	int indiceId=-1;
	int i=0;
	for (i=0;i<matriz->xSize;i++){
		if ( ((matriz->personajesId)[i]) == id){
			indiceId = i;
		}
	}
	return indiceId;
}

//-------------------------------------------------------------

int estaMarcado(V_PERSONAJES* marcados,char id){
	int i=0;
	int posicionId;
	for (i=0;i<marcados->size;i++){
		if (marcados->personajeId[i] == id){
			posicionId=i;
		}
	}
	return marcados->marcado[posicionId];
}

//-------------------------------------------------------------

void marcarPersonaje(V_PERSONAJES* marcados,char id){
	int i=0;
	int posicionId;
	for (i=0;i<marcados->size;i++){
		if (marcados->personajeId[i] == id){
			posicionId=i;
		}
	}
	marcados->marcado[posicionId] = 1;
}


//-------------------------------------------------------------

int esMayor(V_RECURSOS* recursosDispo, M_RECURSOS* recSolicito,int i){
	int j=0;
	int cumplido = 1;
	for (j=0;j<recSolicito->ySize;j++){
		if (((recursosDispo->cantidad)[j]) < ((recSolicito->cantidad)[i][j])){
			cumplido = -1;
		}
	}
	return cumplido;
}


//-------------------------------------------------------------

int puedeCumplirDemanda(V_RECURSOS* recursosDispo, M_RECURSOS* recSolicito, V_PERSONAJES* marcados){
	int i=0;
	int aux=0;
	for (i=0;i<recSolicito->xSize;i++){
		aux = esMayor(recursosDispo,recSolicito,i);
		if ((aux==1)&&(estaMarcado(marcados,recSolicito->personajesId[i])==0)){
			return i;
		}
	}
	return -1;
}

//-------------------------------------------------------------

int detectarDeadlock(M_RECURSOS* m_asignados,M_RECURSOS* m_solicitados,V_RECURSOS* r_totales,V_RECURSOS* r_disponibles,V_PERSONAJES* marcados){

	while (puedeCumplirDemanda(r_disponibles,m_solicitados,marcados) != -1){
		int posCumple = puedeCumplirDemanda(r_disponibles,m_solicitados,marcados);
		char idCumple = m_solicitados->personajesId[posCumple];

		int i=0;
		for (i=0;i<m_solicitados->ySize;i++){
			(r_disponibles->cantidad)[i] += (m_asignados->cantidad)[posCumple][i];
			//printf("la posicion %d del disponible vale %d\n",i,(r_disponibles->cantidad)[i]);
		}
		marcarPersonaje(marcados,idCumple);

	}

	informarBloqueados(marcados);

	return 1;
}

//-------------------------------------------------------------

void imprimirMatriz(M_RECURSOS* matriz){
	int i,j;
	for (i=0; i<matriz->xSize; i++)
		{
			printf("\n");
			for (j=0; j<matriz->ySize; j++)
				printf("\t%d", (matriz->cantidad)[i][j]);
		}
}

//-------------------------------------------------------------

void imprimirVector(V_RECURSOS* vector){
	int i;
	printf("\n");
	for (i=0; i<vector->size; i++)
				printf("\t%d", (vector->cantidad)[i]);
}


