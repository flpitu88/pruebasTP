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
	t_queue* listaMarcados;

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
	r_disponibles->recursosId[0] = '1';
	r_disponibles->recursosId[1] = '2';
	r_disponibles->recursosId[2] = '3';
	r_disponibles->recursosId[3] = '4';
	r_disponibles->cantidad[0] = 0;
	r_disponibles->cantidad[1] = 1;
	r_disponibles->cantidad[2] = 1;
	r_disponibles->cantidad[3] = 0;

	listaMarcados = queue_create();

	int mayor = esMayor(r_disponibles,m_solicitados,3);
	printf("es mayor la fila %d:  %d\n",0,mayor);

	marcarPersonaje(listaMarcados,'1');
	int marcado = estaMarcado(listaMarcados,'1');
	printf("marcado vale %d\n",marcado);

	int cumplida = puedeCumplirDemanda(r_disponibles,m_solicitados);
	printf("puede cumplir la demanda del %d\n",cumplida);

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

