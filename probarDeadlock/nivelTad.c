/*
 * nivelTad.c
 *
 *  Created on: 13/10/2013
 *      Author: utnso
 */

#include "nivelTad.h"
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include "tad_items.h"
#include "log_app.h"
#include <time.h>
#include "./nivel-gui/nivel.h"

#define DERECHA 'r'
#define IZQUIERDA 'l'
#define ARRIBA 'u'
#define ABAJO 'd'

#define ALG_RR 250
#define ALG_SRJF 350


//----------------------------------------------

NIVEL_INST* generarNivel(){

	NIVEL_INST* nivelNuevo = malloc(sizeof(NIVEL_INST));
	nivelNuevo->listaItems = list_create();
	nivelNuevo->listaPersonajes = list_create();
	return nivelNuevo;

}

//---------------------------------------------------------------------------

void cargoConfig(NIVEL_INST* nivel, char* path){

	nivel->configuracion = config_create(path);

	//Cargo nombre de nivel en instancia de nivel
	if ( config_has_property(nivel->configuracion,"Nombre") ){
	       	char *leido = config_get_string_value(nivel->configuracion,"Nombre");
	        memcpy(nivel->nombre,leido,7);
	    }

	//Cargo plataforma de nivel en instancia de nivel
	if ( config_has_property(nivel->configuracion,"Plataforma") ){
			char *leido = config_get_string_value(nivel->configuracion,"Plataforma");
		    memcpy(nivel->plataforma,leido,20);
		}

	//Cargo tiempo de chequeo de deadlock en struct de nivel
	if ( config_has_property(nivel->configuracion,"TiempoChequeoDeadlock") ){
			int leido;
	        leido = config_get_int_value(nivel->configuracion,"TiempoChequeoDeadlock");
	        nivel->deadCheqTime = leido;
	    }

	//Cargo nro recovery en struct de nivel
	if ( config_has_property(nivel->configuracion,"Recovery") ){
			int leido = config_get_int_value(nivel->configuracion,"Recovery");
		    nivel->recovery = leido;
		}

	//Cargo cant de enemigos
	if ( config_has_property(nivel->configuracion,"Enemigos") ){
			int enemigosAux;
			enemigosAux = config_get_int_value(nivel->configuracion,"Enemigos");
			nivel->cantEnemigos = enemigosAux;
		}

	//Cargo tiempo de sleep de enemigos
	if ( config_has_property(nivel->configuracion,"Sleep_Enemigos") ){
			int sleepAux;
			sleepAux = config_get_int_value(nivel->configuracion,"Sleep_Enemigos");
			nivel->sleepEnemigos = sleepAux;
		}

	//Cargo algoritmo de nivel en instancia de nivel
	if ( config_has_property(nivel->configuracion,"algoritmo") ){
		    char *leido = config_get_string_value(nivel->configuracion,"algoritmo");
		    memcpy(nivel->algoritmo,leido,2);
		}

	//Cargo tiempo de quantum para la planificacion
	if ( config_has_property(nivel->configuracion,"quantum") ){
			int quantumAux;
			quantumAux = config_get_int_value(nivel->configuracion,"quantum");
			nivel->quantum = quantumAux;
		}

	//Cargo tiempo de retardo entre turnos
	if ( config_has_property(nivel->configuracion,"retardo") ){
			int retardoAux;
			retardoAux = config_get_int_value(nivel->configuracion,"retardo");
			nivel->retardo = retardoAux;
		}
}

//---------------------------------------------------------------------------


void cargoCajas(NIVEL_INST* nivel){

	char base[] = "Caja";
	char cajaKey[7];
	int cajaNro = 1;
	sprintf(cajaKey, "%s%d", base, cajaNro);
	while ( (config_has_property(nivel->configuracion,cajaKey)) == true ){
		char** caja = config_get_array_value(nivel->configuracion, cajaKey);
		char* idCaja = caja[1];
		int xCaja = atoi(caja[3]);
		int yCaja = atoi(caja[4]);
		int cantRecurso = atoi(caja[2]);
		CrearCaja(nivel->listaItems,*idCaja,xCaja,yCaja,cantRecurso);
		cajaNro++;
		sprintf(cajaKey, "%s%d", base, cajaNro);
	}
}

//--------------------------------------------------------------------------

ITEM_NIVEL* getPunteroItem(NIVEL_INST* nivel, char id){
	int i=0;
		int cantElem = list_size(nivel->listaItems);
		for (i=0;i<cantElem;i++){
			ITEM_NIVEL* item = (ITEM_NIVEL*)list_get(nivel->listaItems,i);
			if ( item->id == id ){
				return item;
			}
		}
		return NULL;
}

//--------------------------------------------------------------------------

T_PERSONAJE* getPunteroPersonaje(NIVEL_INST* nivel, char id){
	int i=0;
		int cantElem = list_size(nivel->listaPersonajes);
		for (i=0;i<cantElem;i++){
			T_PERSONAJE* personaje = (T_PERSONAJE*)list_get(nivel->listaPersonajes,i);
			if ( personaje->id == id ){
				return personaje;
			}
		}
		return NULL;
}

//--------------------------------------------------------------------------

/*
 * Funcion que chequea si esta libre la posicion recibida como parametro.
 * Si esta ocupado retorna 1, sino ocupa -1
 */
int estaLibre(NIVEL_INST* nivel, int posx, int posy){
	int i=0;
	int cantElem = list_size(nivel->listaItems);
	for (i=0;i<cantElem;i++){
		ITEM_NIVEL* item = (ITEM_NIVEL*)list_get(nivel->listaItems,i);
		if ( (item->posx == posx) && (item->posy == posy) ){
			return 1;
		}
	}
	return -1;
}

//---------------------------------------------------------------------------

void cargarEnemigos(NIVEL_INST* nivel){
	int filas, columnas;
	nivel_gui_inicializar();
	nivel_gui_get_area_nivel(&filas,&columnas);
	int i;
	filas--;
	columnas--;
	srand(time(0));
	int cantEnem = nivel->cantEnemigos;
	int xEnem, yEnem;
	for (i=0;i<cantEnem;i++){
		xEnem =  rand() % (filas-3);
		yEnem = rand() % columnas;
		while (estaLibre(nivel,xEnem,yEnem) == 1){
			xEnem = rand()%filas;
			yEnem = rand()%columnas;
		}
		CrearEnemigo(nivel->listaItems,'*',xEnem,yEnem);
	}
}

//---------------------------------------------------------------------------

void cargarNivel(NIVEL_INST* nivel,char* path){
	cargoConfig(nivel,path);
	cargoCajas(nivel);
	//cargarEnemigos(nivel);
}

//--------------------------------------------


void imprimirListaItems(t_list* listaItems){
	int i=0;
	t_list* listaAux = list_create();
	int cantElem = list_size(listaItems);
	printf("cantidad de elementos: %d\n",cantElem);
	listaAux = list_take(listaItems,cantElem);
	for (i=0;i<cantElem;i++){
		ITEM_NIVEL* item = (ITEM_NIVEL*)list_get(listaAux,i);
		printf("Caja %d: id:%c,  Pos x:%d, Pos y:%d, Inst:%d\n",i,item->id,item->posx,item->posy,item->quantity);
	}
	list_destroy(listaAux);
}


//-------------------------------------------------------------------------------


void printConfig(NIVEL_INST* nivel){
	printf("Configuracion cargada: \n");
	printf("Nombre: %s\n",nivel->nombre);
	printf("Algoritmo: %s\n",nivel->algoritmo);
	printf("Quantum : %d\n",nivel->quantum);
	printf("Cant. Enemigos: %d\n",nivel->cantEnemigos);
	printf("Tiempo chequeo deadlock: %d\n",nivel->deadCheqTime);
	printf("Plataforma: %s\n",nivel->plataforma);
	printf("Recovery: %d\n",nivel->recovery);
	printf("Retardo: %d\n",nivel->retardo);
	imprimirListaItems(nivel->listaItems);
}

//-------------------------------------------------------------------------------

void rnd(int *x, int max){
	*x += (rand() % 3) - 1;
	*x = (*x<max) ? *x : max-1;
	*x = (*x>0) ? *x : 1;
}

//-------------------------

void dibujarNivel(NIVEL_INST* nivel){
	int rows, cols;

	int ex1 = 10, ey1 = 14;
	int ex2 = 20, ey2 = 3;

	//nivel_gui_inicializar();
	nivel_gui_get_area_nivel(&rows, &cols);
	nivel_gui_dibujar(nivel->listaItems, "Level Map");

	rnd(&ex1, cols);
	rnd(&ey1, rows);
	rnd(&ex2, cols);
	rnd(&ey2, rows);
	//nivel_gui_terminar();
}

//--------------------------------------------------------------------------

/*
 * Nacen todos los personajes en la ubicacion (0,0)
 */
void agregarPersonajeEnLista(NIVEL_INST* nivel, char idPers){
	CrearPersonaje(nivel->listaItems,idPers,0+1,0+1);
	T_PERSONAJE* personaje = malloc(sizeof(T_PERSONAJE));
	personaje->id = idPers;
	personaje->listaRecursos = list_create();
	list_add(nivel->listaPersonajes,personaje);
}

//--------------------------------------------------------------------------

/*
 * Funciones que retornan la posicion de un item
 * buscando por su id, en x y en y.
 */
int getPosicionX(NIVEL_INST* nivel, char id){
	ITEM_NIVEL* item = getPunteroItem(nivel,id);
	return item->posx;
}

//-----                ------              -------             -------

int getPosicionY(NIVEL_INST* nivel, char id){
	ITEM_NIVEL* item = getPunteroItem(nivel,id);
	return item->posy;
}

//--------------------------------------------------------------------------

void moverPersonaje(char idPersonaje, NIVEL_INST* nivel, char sentido){

	int actualX = getPosicionX(nivel,idPersonaje);
	int actualY = getPosicionY(nivel,idPersonaje);

	switch (sentido){
			case DERECHA:
				MoverPersonaje(nivel->listaItems,idPersonaje,actualX+1,actualY);
				break;

			case IZQUIERDA:
				MoverPersonaje(nivel->listaItems,idPersonaje,actualX-1,actualY);
				break;

			case ARRIBA:
				MoverPersonaje(nivel->listaItems,idPersonaje,actualX,actualY+1);
				break;

			case ABAJO:
				MoverPersonaje(nivel->listaItems,idPersonaje,actualX+1,actualY-1);
				break;
	}
}

//--------------------------------------------------------------------------

void tomarRecurso(NIVEL_INST* nivel, char idRec, char idPersonaje){
	if (getPunteroPersonaje(nivel,idPersonaje) == NULL){
		log_error_message("El personaje que solicita recurso no esta ingresado en nivel");
		system("error");
	} else {
		agregarRecursoPje(nivel,idRec,idPersonaje);
	}
	restarRecurso(nivel->listaItems,idRec);
}

//--------------------------------------------------------------------------

void devolverRecurso(NIVEL_INST* nivel, char recurso){
	ITEM_NIVEL* item = getPunteroItem(nivel,recurso);
	(item->quantity)++;
}

//--------------------------------------------------------------------------

int getQuantum(NIVEL_INST* nivel){
	return nivel->quantum;
}


//--------------------------------------------------------------------------

int getRetardo(NIVEL_INST* nivel){
	return nivel->retardo;
}

//--------------------------------------------------------------------------

static void recurso_destroy(char* recurso){
        free(recurso);
}

//------------			---------------------		-----------------------

void desconectarPersonaje(NIVEL_INST* nivel, char pje){
	int tamanio = list_size(nivel->listaPersonajes);
		int i=0;
		int j=0;
		for (i=0;i<tamanio;i++){
			T_PERSONAJE* personaje = (T_PERSONAJE*) list_get(nivel->listaPersonajes,i);
			if (personaje->id == pje){
				j=i;
			}
		}
		list_remove(nivel->listaPersonajes,j);
	BorrarItem(nivel->listaItems,pje);
}

//--------------------------------------------------------------------------

void printListaPersonajes(t_list* listaItems){
	int i=0;
		t_list* listaAux = list_create();
		int cantElem = list_size(listaItems);
		printf("cantidad de elementos: %d\n",cantElem);
		listaAux = list_take(listaItems,cantElem);
		for (i=0;i<cantElem;i++){
			ITEM_NIVEL* item = (ITEM_NIVEL*)list_get(listaAux,i);
			if (item->item_type == PERSONAJE_ITEM_TYPE){
			printf("Personaje %d: id:%c,  Pos x:%d, Pos y:%d, \n",i,item->id,item->posx,item->posy);
			}
		}
		list_destroy(listaAux);
}

//--------------------------------------------------------------------------

int getAlgoritmo(NIVEL_INST* nivel){
	if ((nivel->algoritmo)[0] == 'R'){
		return ALG_RR;
	} else if ((nivel->algoritmo[0]) == 'S'){
		return ALG_SRJF;
	}
	return -1;
}

//--------------------------------------------------------------------------

int getRecovery(NIVEL_INST* nivel){
	return nivel->recovery;
}

//--------------------------------------------------------------------------

int getTiempoChequeo(NIVEL_INST* nivel){
	return nivel->deadCheqTime;
}

//--------------------------------------------------------------------------

int getSleep(NIVEL_INST* nivel){
	return nivel->sleepEnemigos;
}

//--------------------------------------------------------------------------

int getIndiceListaRecursos(t_list* listaRec, char idRec){
	int tamanio = list_size(listaRec);
	int i=0;
	for (i=0;i<tamanio;i++){
		char* recurso = (char*) list_get(listaRec,i);
		if (*recurso == idRec){
			return i;
		}
	}
	return -1;
}

//--------------------------------------------------------------------------

void agregarRecursoPje(NIVEL_INST* nivel, char idRec, char idPers){
	int tamanio = list_size(nivel->listaPersonajes);
	int i=0;
	for (i=0;i<tamanio;i++){
		T_PERSONAJE* personaje = (T_PERSONAJE*) list_get(nivel->listaPersonajes,i);
		if (personaje->id == idPers){
			char* recurso = malloc(sizeof(char));
			strcpy(recurso,&idRec);
			list_add(personaje->listaRecursos,recurso);
		}
	}
}

//--------------------------------------------------------------------------

void sacarRecursoPersonaje(NIVEL_INST* nivel, char idPersonaje, char idRec){
	T_PERSONAJE* personaje = getPunteroPersonaje(nivel,idPersonaje);
	int indice = getIndiceListaRecursos(personaje->listaRecursos,idRec);
	if (indice == -1){
		log_error_message("El personaje no posee el item a sacarle");
		system("error");
	} else {
		list_remove_and_destroy_element(personaje->listaRecursos,indice,(void*) recurso_destroy);
		list_remove(personaje->listaRecursos,indice);
		log_debug_message("Se le quita un recurso al personaje");
	}
}

//--------------------------------------------------------------------------

void printRecursosPersonaje(NIVEL_INST* nivel, char personaje){
	int i=0;
	t_list* listaAux = list_create();
	printf("Lista de recursos del personaje %c :\n",personaje);
	T_PERSONAJE* persAux = getPunteroPersonaje(nivel,personaje);
	int cantElem = list_size(persAux->listaRecursos);
	listaAux = list_take(persAux->listaRecursos,cantElem);
	for (i=0;i<cantElem;i++){
		char* recurso = (char*)list_get(listaAux,i);
		printf("%c - ",*recurso);
	}
	printf("\n");
	list_destroy(listaAux);
}

//--------------------------------------------------------------------------
