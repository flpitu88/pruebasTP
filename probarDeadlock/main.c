/*
 * main.c
 *
 *  Created on: 29/07/2013
 *      Author: utnso
 */


#include "detecDeadlock.h"
#include <stdio.h>

int main(void){

	int cantRecursos = 4;
	int cantPersonajes = 5;

	M_RECURSOS* m_asignados = crearMatriz(cantPersonajes,cantRecursos);
	M_RECURSOS* m_solicitados = crearMatriz(cantPersonajes,cantRecursos);
	V_RECURSOS* r_totales = crearVector(cantRecursos);
	V_PERSONAJES* marcados = crearVectorPers(cantPersonajes);

	// cargos matriz de asignados
	(m_asignados->personajesId)[0] = '1';
	(m_asignados->personajesId)[1] = '2';
	(m_asignados->personajesId)[2] = '3';
	(m_asignados->personajesId)[3] = '4';
	(m_asignados->personajesId)[4] = '5';

	m_asignados->recursosId[0] = '1';
	m_asignados->recursosId[1] = '2';
	m_asignados->recursosId[2] = '3';
	m_asignados->recursosId[3] = '4';

	(m_asignados->cantidad)[0][0] = 0;
	(m_asignados->cantidad)[0][1] = 0;
	(m_asignados->cantidad)[0][2] = 0;
	(m_asignados->cantidad)[0][3] = 0;


	(m_asignados->cantidad)[1][0] = 1;
	(m_asignados->cantidad)[1][1] = 0;
	(m_asignados->cantidad)[1][2] = 0;
	(m_asignados->cantidad)[1][3] = 1;

	/*
	printf("item vale: %d\n",(m_asignados->cantidad)[1][0]);
	printf("item vale: %d\n",(m_asignados->cantidad)[1][1]);
	printf("item vale: %d\n",(m_asignados->cantidad)[1][2]);
	printf("item vale: %d\n",(m_asignados->cantidad)[1][3]);
*/
	m_asignados->cantidad[2][0] = 1;
	m_asignados->cantidad[2][1] = 0;
	m_asignados->cantidad[2][2] = 1;
	m_asignados->cantidad[2][3] = 0;

	m_asignados->cantidad[3][0] = 1;
	m_asignados->cantidad[3][1] = 1;
	m_asignados->cantidad[3][2] = 1;
	m_asignados->cantidad[3][3] = 0;

	m_asignados->cantidad[4][0] = 0;
	m_asignados->cantidad[4][1] = 0;
	m_asignados->cantidad[4][2] = 0;
	m_asignados->cantidad[4][3] = 1;

	// cargo matriz de necesidad
	m_solicitados->personajesId[0] = '1';
	m_solicitados->personajesId[1] = '2';
	m_solicitados->personajesId[2] = '3';
	m_solicitados->personajesId[3] = '4';
	m_solicitados->personajesId[4] = '5';

	m_solicitados->recursosId[0] = '1';
	m_solicitados->recursosId[1] = '2';
	m_solicitados->recursosId[2] = '3';
	m_solicitados->recursosId[3] = '4';

	m_solicitados->cantidad[0][0] = 0;
	m_solicitados->cantidad[0][1] = 2;
	m_solicitados->cantidad[0][2] = 0;
	m_solicitados->cantidad[0][3] = 0;

	m_solicitados->cantidad[1][0] = 1;
	m_solicitados->cantidad[1][1] = 2;
	m_solicitados->cantidad[1][2] = 1;
	m_solicitados->cantidad[1][3] = 0;

	m_solicitados->cantidad[2][0] = 0;
	m_solicitados->cantidad[2][1] = 1;
	m_solicitados->cantidad[2][2] = 0;
	m_solicitados->cantidad[2][3] = 0;

	m_solicitados->cantidad[3][0] = 0;
	m_solicitados->cantidad[3][1] = 0;
	m_solicitados->cantidad[3][2] = 1;
	m_solicitados->cantidad[3][3] = 2;

	m_solicitados->cantidad[4][0] = 1;
	m_solicitados->cantidad[4][1] = 0;
	m_solicitados->cantidad[4][2] = 1;
	m_solicitados->cantidad[4][3] = 0;

	//cargo vector de totales
	r_totales->recursosId[0] = '1';
	r_totales->recursosId[1] = '2';
	r_totales->recursosId[2] = '3';
	r_totales->recursosId[3] = '4';
	r_totales->cantidad[0] = 3;
	r_totales->cantidad[1] = 2;
	r_totales->cantidad[2] = 3;
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
	r_disponibles->cantidad[1] = 1;
	r_disponibles->cantidad[2] = 1;
	r_disponibles->cantidad[3] = 0;
/*
	marcarPersonaje(marcados,'3');
	int marcado = estaMarcado(marcados,'1');
	printf("marcado vale %d\n",marcado);

	int cumplida = puedeCumplirDemanda(r_disponibles,m_solicitados,marcados);
	printf("puede cumplir la demanda del %d\n",cumplida);
*/

	detectarDeadlock(m_asignados,m_solicitados,r_totales,r_disponibles,marcados);

/*
	while (puedeCumplirDemanda(r_disponibles,m_solicitados) != -1){
			int posCumple = puedeCumplirDemanda(r_disponibles,m_solicitados);
			char idCumple = m_solicitados->personajesId[posCumple];

			int i=0;
			for (i=0;i<cantRecursos;i++){
				r_disponibles->cantidad[i] = r_disponibles->cantidad[i] + (m_asignados->cantidad)[posCumple][i];
			}
			marcarPersonaje(listaMarcados,idCumple);

		}

		informarBloqueados();
*/
		destruirMatriz(m_asignados);
		destruirMatriz(m_solicitados);
		destruirVector(r_totales);
		destruirVector(r_disponibles);

		return 1;
}

