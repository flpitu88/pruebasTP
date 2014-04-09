/*
 * lector_config.c
 *
 *  Created on: 08/04/2014
 *      Author: utnso
 */

#include <stdio.h>
#include <string.h>
#include "/home/utnso/git/so-commons-library/src/commons/config.c"
#include "/home/utnso/git/so-commons-library/src/commons/string.c"
#include "/home/utnso/git/so-commons-library/src/commons/collections/dictionary.c"
#include "lector_config.h"

// Inicializo la estructura de configuracion
CONFIG_T* crearConfig(){
	CONFIG_T* config = malloc(sizeof(CONFIG_T));
	config->cant_io = 0;
	config->puerto_cpu = 0;
	config->puerto_prog = 0;
	config->quantum = 0;
	config->retardo = 0;
	int i=0;
	for (i=0; i<10; i++){
		config->retardo_io[i] = 0;
	}
	return config;
}

// Funcion que pide el ingreso de un entero por teclado
int leerEnteroxTeclado(char* mensaje){
	int leido = -1;
	printf("Ingrese %s \n",mensaje); //Solicitando al usuario que ingrese un numero
	scanf("%d",&leido); //Leyendo el número solicitado
	printf("El numero que ingreso es %d \n", leido); //Mostrando el número ingresado por teclado
	return leido;
}


void levantarConfig(CONFIG_T* config,char* path){

	t_config* conf = config_create(path);

	//Obtengo el numero de dispositivos de entrada/salida
	if ( config_has_property(conf,"CANT_HIO") ){
		int aux = config_get_int_value(conf,"CANT_HIO");
		config->cant_io = aux;
	} else {
		int cantdisp = leerEnteroxTeclado(" la cantidad de dispositivos");
		config->cant_io = cantdisp;
	}
/*
	//Cargo los retardos de cada dispositivo. Si no esta aclarado, se ingresa por teclado
	int i=0;
	char* clave = "HIO[";
	for (i=0;i<config->cant_io;i++){
		//Armo la clave de busqueda de cada dispositivo
		char* idAux = string_itoa(i);
		string_substring_until(idAux,1);
		strcat(clave,idAux);
		strcat(clave,"]");

		if ( config_has_property(conf,clave) ){
			int aux = config_get_int_value(conf,clave);
			config->retardo_io[i] = aux;
		} else {
			int retardo = leerEnteroxTeclado(clave);
			config->retardo_io[i] = retardo;
		}
	}
*/
	//Obtengo el numero de puerto de programas
	if ( config_has_property(conf,"Puerto_Prog") ){
		int aux = config_get_int_value(conf,"Puerto_Prog");
		config->puerto_prog = aux;
	} else {
		int cantdisp = leerEnteroxTeclado(" el numero de puerto del programa");
		config->puerto_prog = cantdisp;
	}

	//Obtengo el numero de puerto de cpu
	if ( config_has_property(conf,"Puerto_CPU") ){
		int aux = config_get_int_value(conf,"Puerto_CPU");
		config->puerto_cpu = aux;
	} else {
		int puertoCpu = leerEnteroxTeclado(" el numero de puerto de cpu");
		config->puerto_cpu = puertoCpu;
	}

	//Obtengo el numero de quantum
	if ( config_has_property(conf,"Quantum") ){
		int aux = config_get_int_value(conf,"Quantum");
		config->quantum = aux;
	} else {
		int quantum = leerEnteroxTeclado(" la cantidad de dispositivos");
		config->quantum = quantum;
	}

	//Obtengo el retardo
	if ( config_has_property(conf,"Retardo") ){
		int aux = config_get_int_value(conf,"Retardo");
		config->retardo = aux;
	} else {
		int retardo = leerEnteroxTeclado(" el valor del retardo");
		config->retardo = retardo;
	}

	// Elimino la estructura utilizada para leer la configuracion
	config_destroy(conf);

}
