/*
 * main.c
 *
 *  Created on: 25/04/2014
 *      Author: utnso
 */

#include <stdio.h>

int main(void){
	int pos = 0;
	char* codigo = "#!/usr/bin/ansisop\n\n function imprimir\n wait mutexA\n print $0+1\n signal mutexB\n end\n\n begin\n variables f,  A,  g\n A=0\n !Global = 1+A\n print !Global\n jnz !Global Siguiente\n :Proximo\n\n f=8\n g<- doble !Global\n io impresora 20\n :Siguiente\n imprimir A\n textPrint Hola Mundo! \n sumar1 &g\n print g\n\n sinParam\n\n end\n\n function sinParam\n textPrint Bye\n end\n\n #Devolver el doble del\n #primer parametro\n function doble\n variables f\n f=$0+$0\n return f\n end\n\n function sumar1\n *$0 = 1 + *$0\n end\n";
	for (pos=0;pos<512;pos++){
		printf("char de la posicion %i es: %c\n",pos,codigo[pos]);
	}
	return 1;
}
