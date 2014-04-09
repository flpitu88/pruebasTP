/*
 * lector_config.h
 *
 *  Created on: 08/04/2014
 *      Author: utnso
 */

#ifndef LECTOR_CONFIG_H_
#define LECTOR_CONFIG_H_

#define MAXIO 10
#include "/home/utnso/git/so-commons-library/src/commons/config.h"

struct configTad{
	int cant_io;
	int retardo_io[MAXIO];
	int puerto_prog;
	int puerto_cpu;
	int quantum;
	int retardo;
};
typedef struct configTad CONFIG_T;

CONFIG_T* crearConfig();
void levantarConfig(CONFIG_T* config,char* path);

#endif /* LECTOR_CONFIG_H_ */
