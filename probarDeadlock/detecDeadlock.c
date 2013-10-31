/*
 * detecDeadlock.c
 *
 *  Created on: 28/07/2013
 *      Author: utnso
 */

// ([fila],[columna])
// (personaje,recurso)

#include "detecDeadlock.h"
#include "/home/utnso/git/tp-2013-2c-sockete-s/procNivel/nivelTad.h"
#include <stdlib.h>
#include <stdio.h>

int** marcados;
int cantRecursos;
int cantPersonajes;

//-------------------------------------------------------------
//Auxiliar

void cargarEtiquetasRecursos(NIVEL_INST* nivel, M_RECURSOS* matriz){
	int i=0;
	int j=0;
	t_list* listaAux = list_create();
	int cantElem = list_size(nivel->listaItems);
	listaAux = list_take(nivel->listaItems,cantElem);
	for (i=0;i<cantElem;i++){
		ITEM_NIVEL* item = (ITEM_NIVEL*)list_get(listaAux,i);
		if (item->item_type == RECURSO_ITEM_TYPE){
			matriz->recursosId[j] = item->id;
			j++;
		}
	}
	list_destroy(listaAux);
}

// ------       --------          --------         ---------      ---------

void cargarEtiquetasPersonajes(NIVEL_INST* nivel, M_RECURSOS* matriz){
	int i=0;
	t_list* listaAux = list_create();
	int cantElem = list_size(nivel->listaPersonajes);
	listaAux = list_take(nivel->listaPersonajes,cantElem);
	for (i=0;i<cantElem;i++){
		T_PERSONAJE* personaje = (T_PERSONAJE*)list_get(listaAux,i);
		matriz->personajesId[i] = personaje->id;
	}
	list_destroy(listaAux);
}

// ------       --------          --------         ---------      ---------

void cargarEtiquetasMatriz(NIVEL_INST* nivel,M_RECURSOS* matriz){
	cargarEtiquetasRecursos(nivel,matriz);
	cargarEtiquetasPersonajes(nivel,matriz);
}

// ------       --------          --------         ---------      ---------
/*
int getCantidadRecXId(NIVEL_INST* nivel, char idPer, char idRec){
	int total = 0;
	T_PERSONAJE* personaje = getPunteroPersonaje(nivel,idPer);
	int cantRec = list_size(personaje->listaRecursos);
	int i=0;
	t_list* listaAux = list_create();
	listaAux = list_take(personaje->listaRecursos,cantRec);
	for (i=0;i<cantRec;i++){
		char* recurso = (char*)list_get(listaAux,i);
		if (*recurso == idRec){
			total++;
		}
	}
	return total;
}
*/ //Descomentar
// ------       --------          --------         ---------      ---------
/*
void cargarCantidadAsignados(NIVEL_INST* nivel,M_RECURSOS* matriz){
	int i=0;
	int j=0;
	int cantPers = matriz->xSize;
	int cantRec = matriz->ySize;
	for (i=0;i<cantPers;i++){
		for (j=0;j<cantRec;j++){
			int rec = getCantidadRecXId(nivel,matriz->personajesId[i],matriz->recursosId[j]);
			(matriz->cantidad)[i][j] = rec;
		}
	}
}
*/ // descomentar cuando se usen matrices
//-------------------------------------------------------------

void cargarMatrizAsignados(NIVEL_INST* nivel,M_RECURSOS* matriz){
	cargarEtiquetasMatriz(nivel,matriz);
	//cargarCantidadAsignados(nivel,matriz);
}
//descomentar cuando se usen matrices
//-------------------------------------------------------------

int getIndiceRecurso(M_RECURSOS* matriz, char idRec){
	int cantRec = matriz->ySize;
	int i=0;
	for (i=0;i<cantRec;i++){
		if (matriz->recursosId[i] == idRec){
			return i;
		}
	}
	return -1;
}

//-------------------------------------------------------------
/*
void cargarMatrizSolicitados(NIVEL_INST* nivel, M_RECURSOS* matriz){
	cargarEtiquetasMatriz(nivel,matriz);
	int cantPers = matriz->xSize;
	int i=0;
	for (i=0;i<cantPers;i++){
		char idPers = matriz->personajesId[i];
		T_PERSONAJE* personaje = getPunteroPersonaje(nivel,idPers);
		char idBloq = personaje->recBloqueo;
		int indice = getIndiceRecurso(matriz,idBloq);
		(matriz->cantidad)[i][indice] ++;
	}
}
*/ //descomentar cuando se use nivel
//-------------------------------------------------------------

//void cargarVectorTotales(NIVEL_INST* nivel){}

//-------------------------------------------------------------

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

void iniciarMatriz(M_RECURSOS* matriz, int m, int n){
	int i=0;
	int j=0;
	for (i=0;i<m;i++){
		for (j=0;j<n;j++){
			(matriz->cantidad)[i][j] = 0;
		}
	}
}

// ------       --------          --------         ---------      ---------

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
	iniciarMatriz(rec_matriz,m,n);
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

int getCantPersonajes(NIVEL_INST* nivel){
	return list_size(nivel->listaPersonajes);
}

//-------------------------------------------------------------

int getCantRecursos(NIVEL_INST* nivel){
	int i=0;
	int totalRec=0;
	t_list* listaAux = list_create();
	int cantElem = list_size(nivel->listaItems);
	listaAux = list_take(nivel->listaItems,cantElem);
	for (i=0;i<cantElem;i++){
		ITEM_NIVEL* item = (ITEM_NIVEL*)list_get(listaAux,i);
		if (item->item_type == RECURSO_ITEM_TYPE){
			totalRec++;
		}
	}
	list_destroy(listaAux);
	return totalRec;
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


