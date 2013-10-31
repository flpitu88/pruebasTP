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


	//int cantRecursos = 4;
	//int cantPersonajes = 4;

	M_RECURSOS* m_asignados = crearMatriz(cantPersonajes,cantRecursos); /*
	M_RECURSOS* m_solicitados = crearMatriz(cantPersonajes,cantRecursos);
	V_RECURSOS* r_totales = crearVector(cantRecursos);
	V_PERSONAJES* marcados = crearVectorPers(cantPersonajes); */

	tomarRecurso(nivel,'F','#');
	tomarRecurso(nivel,'C','#');
	tomarRecurso(nivel,'H','#');
	tomarRecurso(nivel,'C','$');
	tomarRecurso(nivel,'H','$');
	tomarRecurso(nivel,'F','@');
	tomarRecurso(nivel,'H','@');


	cargarMatrizAsignados(nivel,m_asignados); // Funciona

	printf("Matriz de asignados----------------\n");
	imprimirMatriz(m_asignados);
	printf("\n");

	/* BORRAR ESTE
	// cargos matriz de asignados
	(m_asignados->personajesId)[0] = '1';
	(m_asignados->personajesId)[1] = '2';
	(m_asignados->personajesId)[2] = '3';
	(m_asignados->personajesId)[3] = '4';
	//(m_asignados->personajesId)[4] = '5';

	m_asignados->recursosId[0] = '1';
	m_asignados->recursosId[1] = '2';
	m_asignados->recursosId[2] = '3';
	m_asignados->recursosId[3] = '4';

	(m_asignados->cantidad)[0][0] = 1;
	(m_asignados->cantidad)[0][1] = 1;
	(m_asignados->cantidad)[0][2] = 0;
	(m_asignados->cantidad)[0][3] = 0;


	(m_asignados->cantidad)[1][0] = 0;
	(m_asignados->cantidad)[1][1] = 0;
	(m_asignados->cantidad)[1][2] = 0;
	(m_asignados->cantidad)[1][3] = 0;

	m_asignados->cantidad[2][0] = 1;
	m_asignados->cantidad[2][1] = 1;
	m_asignados->cantidad[2][2] = 0;
	m_asignados->cantidad[2][3] = 0;

	m_asignados->cantidad[3][0] = 0;
	m_asignados->cantidad[3][1] = 0;
	m_asignados->cantidad[3][2] = 1;
	m_asignados->cantidad[3][3] = 0;

	// cargo matriz de necesidad
	m_solicitados->personajesId[0] = '1';
	m_solicitados->personajesId[1] = '2';
	m_solicitados->personajesId[2] = '3';
	m_solicitados->personajesId[3] = '4';


	m_solicitados->recursosId[0] = '1';
	m_solicitados->recursosId[1] = '2';
	m_solicitados->recursosId[2] = '3';
	m_solicitados->recursosId[3] = '4';

	m_solicitados->cantidad[0][0] = 1;
	m_solicitados->cantidad[0][1] = 1;
	m_solicitados->cantidad[0][2] = 1;
	m_solicitados->cantidad[0][3] = 1;

	m_solicitados->cantidad[1][0] = 2;
	m_solicitados->cantidad[1][1] = 0;
	m_solicitados->cantidad[1][2] = 0;
	m_solicitados->cantidad[1][3] = 2;

	m_solicitados->cantidad[2][0] = 1;
	m_solicitados->cantidad[2][1] = 1;
	m_solicitados->cantidad[2][2] = 0;
	m_solicitados->cantidad[2][3] = 0;

	m_solicitados->cantidad[3][0] = 0;
	m_solicitados->cantidad[3][1] = 0;
	m_solicitados->cantidad[3][2] = 0;
	m_solicitados->cantidad[3][3] = 2;

	//cargo vector de totales
	r_totales->recursosId[0] = '1';
	r_totales->recursosId[1] = '2';
	r_totales->recursosId[2] = '3';
	r_totales->recursosId[3] = '4';
	r_totales->cantidad[0] = 2;
	r_totales->cantidad[1] = 2;
	r_totales->cantidad[2] = 1;
	r_totales->cantidad[3] = 2;

	V_RECURSOS* r_disponibles = crearVector(cantRecursos);

	//cargo vector de disponibles
	marcados->personajeId[0] = '1';
	marcados->personajeId[1] = '2';
	marcados->personajeId[2] = '3';
	marcados->personajeId[3] = '4';
	marcados->personajeId[4] = '5';
	marcados->marcado[0] = 0;
	marcados->marcado[1] = 0;
	marcados->marcado[2] = 0;
	marcados->marcado[3] = 0;
	marcados->marcado[4] = 0;

	//Inicializo marcados
	r_disponibles->recursosId[0] = '1';
	r_disponibles->recursosId[1] = '2';
	r_disponibles->recursosId[2] = '3';
	r_disponibles->recursosId[3] = '4';
	r_disponibles->cantidad[0] = 0;
	r_disponibles->cantidad[1] = 0;
	r_disponibles->cantidad[2] = 0;
	r_disponibles->cantidad[3] = 2;

	printf("Matriz de asignados----------------\n");
	imprimirMatriz(m_asignados);
	printf("\n");

	printf("Matriz de solicitados--------------\n");
	imprimirMatriz(m_solicitados);
	printf("\n");

	printf("Vector de recursos disponibles-----\n");
	imprimirVector(r_disponibles);
	printf("\n");

	printf("Vector de recursos totales---------\n");
	imprimirVector(r_totales);
	printf("\n");



	detectarDeadlock(m_asignados,m_solicitados,r_totales,r_disponibles,marcados);

 HASTA ESTE
*/
	/*	destruirMatriz(m_asignados);
		destruirMatriz(m_solicitados);
		destruirVector(r_totales);
		destruirVector(r_disponibles);
*/
		return 1;
}

