/*
 * main.c
 *
 *  Created on: 29/07/2013
 *      Author: utnso
 */


#include "detecDeadlock.h"
#include "nivelTad.h"
#include <stdio.h>

#define PATH_CONFIG "./config/nivel1.cfg"

int main(void){

	NIVEL_INST* nivel = generarNivel();
	cargarNivel(nivel,PATH_CONFIG);

	printConfig(nivel);

	agregarPersonajeEnLista(nivel,'#');
	agregarPersonajeEnLista(nivel,'$');
	agregarPersonajeEnLista(nivel,'@');

	int cantRecursos = getCantRecursos(nivel);
	int cantPersonajes = getCantPersonajes(nivel);

	printf("la cantidad de personajes es: %d\n",cantPersonajes);
	printf("la cantidad de recursos es: %d\n",cantRecursos);

	M_RECURSOS* m_asignados = crearMatriz(cantPersonajes,cantRecursos);
	M_RECURSOS* m_solicitados = crearMatriz(cantPersonajes,cantRecursos);
	V_RECURSOS* r_totales = crearVector(cantRecursos);
	V_PERSONAJES* marcados = crearVectorPers(cantPersonajes);
	V_RECURSOS* r_disponibles = crearVector(cantRecursos);

	cargarVectorTotales(nivel,r_totales);

	printf("Vector de recursos totales---------\n");
	imprimirVector(r_totales);
	printf("\n");

	tomarRecurso(nivel,'F','#');
	tomarRecurso(nivel,'C','#');
	tomarRecurso(nivel,'H','#');
	tomarRecurso(nivel,'C','$');
	tomarRecurso(nivel,'H','$');
	tomarRecurso(nivel,'F','@');
	tomarRecurso(nivel,'H','@');

	T_PERSONAJE* personaje1 = getPunteroPersonaje(nivel,'#');
	personaje1->recBloqueo = 'F';
	T_PERSONAJE* personaje2 = getPunteroPersonaje(nivel,'$');
	personaje2->recBloqueo = 'H';
	T_PERSONAJE* personaje3 = getPunteroPersonaje(nivel,'@');
	personaje3->recBloqueo = 'F';

	cargarMatrizAsignados(nivel,m_asignados); // Funciona

	printf("Matriz de asignados----------------\n");
	imprimirMatriz(m_asignados);
	printf("\n");

	cargarMatrizSolicitados(nivel,m_solicitados);

	printf("Matriz de solicitados--------------\n");
	imprimirMatriz(m_solicitados);
	printf("\n");

	cargarVectorDisponibles(m_asignados,r_totales,r_disponibles);

	printf("Vector de recursos disponibles---------\n");
	imprimirVector(r_disponibles);
	printf("\n");

	printf("Vector de personajes marcados---------\n");
	imprimirVectorPers(marcados);
	printf("\n");

	cargarEtiquetasVecPersonajes(nivel,marcados);

	detectarDeadlock(m_asignados,m_solicitados,r_totales,r_disponibles,marcados);

		destruirMatriz(m_asignados);
		destruirMatriz(m_solicitados);
		destruirVector(r_totales);
		destruirVector(r_disponibles);
		destruirVectorPers(marcados);

		return 1;
}

