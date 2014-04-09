/*
 * main.c
 *
 *  Created on: 08/04/2014
 *      Author: utnso
 */

#include <stdio.h>
#include <stdlib.h>
#include "/home/utnso/workspace/lectorConfig/lector_config.h"

int main(void){

	printf("Inicio carga de archivo de configuracion\n");
	CONFIG_T* config = crearConfig();
	printf("Estructura creada\n");
	levantarConfig(config,"/home/utnso/workspace/lectorConfig/Resource/config.cfg");
	printf("Configuracion cargada \n");
	free(config);
	return 1;
}
