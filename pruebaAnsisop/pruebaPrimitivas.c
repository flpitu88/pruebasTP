/*
 * pruebaPrimitivas.c
 *
 *  Created on: 06/05/2014
 *      Author: utnso
 */


#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <commons/log_app.h>
#include <commons/string.h>
#include <commons/shared_strs.h>
#include <commons/collections/dictionary.h>
//#include "/home/utnso/git/tp-2014-1c-alloca2/CPU/cpu.h"
//#include "ansisop_prim.h"
#include <parser/metadata_program.h>


#define MAXVARIABLES 15
static const int POSICION_MEMORIA = 0x10;
static const int CONTENIDO_VARIABLE = 20;

typedef struct dicVariables { // estructura generica, debe estar en todas las estructuras
	char variable[MAXVARIABLES];
	int offset[MAXVARIABLES];
	int ultimo;
	int cursor;
} t_dicVar;

// Variables para la ejecucion
t_stack_c* stack; // Tipo pila para manejo del stack
char stackChar[STACK_SIZE]; // Literal de recepcion de stack segment
t_PCB pcb; // PCB recibido para ejecucion
t_dicVar* diccionario; // Diccionario de variables del stack
char* serEtiquetas; // Sentencia que se ejecutara
char* sentenciaEjec; // Puntero a la sentencia a ejecutar
char log_text[500]; // Variable para logueo de ejecucion
char* codigo = "#!/usr/bin/ansisop\n\n function imprimir\n wait mutexA\n print $0+1\n signal mutexB\n end\n\n begin\n variables f,  A,  g\n A=0\n !Global = 1+A\n print !Global\n jnz !Global Siguiente\n :Proximo\n\n f=8\n g<- doble !Global\n io impresora 20\n :Siguiente\n imprimir A\n textPrint Hola Mundo! \n sumar1 &g\n print g\n\n sinParam\n\n end\n\n function sinParam\n textPrint Bye\n end\n\n #Devolver el doble del\n #primer parametro\n function doble\n variables f\n f=$0+$0\n return f\n end\n\n function sumar1\n *$0 = 1 + *$0\n end\n";




void inicializarDiccionario(t_dicVar* diccionario){
	int i=0;
	for (i=0;i<MAXVARIABLES;i++){
		diccionario->variable[i] = '-';
		diccionario->offset[i] = 0;
	}
	diccionario->ultimo = 0;
	diccionario->cursor = 0;
	log_debug_message("Inicializado el diccionario de variables");
}

/*
 * Agrega una variable con su ubicacion dentro del stack
 * en el diccionario, y aumenta el valor del ultimo lugar
 * disponible para almacenar
 */
void indexarEnDiccionario(t_dicVar* diccionario, char id, int posicion){
	int i = diccionario->ultimo;
	diccionario->offset[i] = posicion;
	diccionario->variable[i] = id;
	diccionario->ultimo++;

	sprintf(log_text,"Se indexa la variable %c ubicada en %i del stack, en posicion %i del diccionario",id,posicion,i);
	log_debug_message(log_text);
}

/*
 * Funcion que retorna la posicion de una variable dentro del stack.
 * Si no existe retorna -1.
 */
int obtenerPosicionDic(t_dicVar* diccionario, char id){
	int max = diccionario->ultimo;
	int i=0;
	int posicion = -1;
	for (i=0;i<max;i++){
		if (diccionario->variable[i] == id){
			posicion = diccionario->offset[i];
		}
	}

	sprintf(log_text,"La posicion de la variable %c en el stack indexada en el diccionario es %i",id,posicion);
	log_debug_message(log_text);

	return posicion;
}

/*
 * Funcion que crea el diccionario de datos
 * a partir de la recepcion del stack por parte
 * del StackSegment procedente del UMV
 */
void cargarDiccionario(t_dicVar* diccionario, t_stack_c* stack){
	//DESARROLLAR
	log_debug_message("Se carga el diccionario de variables en base al stack");
}

void stringAStack(char* stackChar,t_stack_c* stack,int tamContex){
	int i=0;
	int size= sizeof(t_variable);
	int offset=0;
	for (i=0;i<tamContex;i++){
		t_variable recVar;
		memcpy(&recVar,stackChar+offset,size);

		sprintf(log_text,"Desserializada variable %i: Id %c ----- Valor %i",i,recVar.id,recVar.valor);
		log_debug_message(log_text);

		offset = offset+size;
		apilarC(stack,&recVar);

		sprintf(log_text,"Agregada la variable %i al stack",i);
		log_debug_message(log_text);
	}
}

void imprimirStack(t_stack_c* stack){
	int i=0;
	int max = stack->cantElem;
	for (i=0;i<max;i++){
		t_variable* variableAux = (t_variable*) desapilarC(stack);
		printf("Desapilo la variable %c, con un valor de %i\n",variableAux->id,variableAux->valor);
		printf("La pila tiene %i elementos y el puntero final es %i\n",stack->cantElem,stack->punteroUlt);
	}
}

void imprimirPCB(t_PCB* pcb){
	printf("Id: %i\n",pcb->id);
	printf("PC: %i\n",pcb->PC);
	printf("codSeg: %i\n",pcb->codSeg);
	printf("cursor Stack: %i\n",pcb->cursorStack);
	printf("IndCod: %i\n",pcb->indCod);
	printf("IndEtiq: %i\n",pcb->indEtiq);
	printf("StackSeg: %i\n",pcb->stackSeg);
	printf("TamContext: %i\n",pcb->tamContext);
}






// --------------------------------- PRIMITIVAS ----------------------------------------------------


/*
 Envía al Kernel una cadena de texto para que este la reenvíe a la correspondiente consola del
Programa en ejecución. No admite parámetros adicionales, secuencias de escape o variables.
Devuelve la cantidad de dígitos impresos.
 */
int imprimirTexto(char* texto){
	printf("----------ImprimirTexto: %s------------\n", texto);
	return 1;
}


/*
 Reserva en el Contexto de Ejecución Actual el espacio necesario para una variable llamada
identificador_variable y la registra tanto en el Stack como en el Diccionario de Variables,
retornando la posición del valor de esta nueva variable del stack
El valor de la variable queda indefinido: no deberá inicializarlo con ningún valor default.
Esta función se invoca una vez por variable, a pesar de que este varias veces en una línea. Por
ejemplo, evaluar "variables a, b, c" llamará tres veces a esta función con los parámetros "a",
"b" y "c"
 */
t_puntero definirVariable(t_nombre_variable identificador_variable ){
	t_variable* variable = malloc(sizeof(t_variable));
	variable->id = identificador_variable;
	int posicion = apilarC(stack,variable);
	indexarEnDiccionario(diccionario,identificador_variable,posicion);
	printf("Se ejecuto definir variable. ID:%c - Posicion:%i\n",identificador_variable,posicion);
	return posicion;
}


/*
 Devuelve el desplazamiento respecto al inicio del segmento Stack en que se encuentra el valor
de la variable identificador_variable del contexto actual. En caso de error, retorna -1.
 */
t_puntero obtenerPosicionVariable(t_nombre_variable identificador_variable ){
	int posicion = obtenerPosicionDic(diccionario,identificador_variable);
	printf("---------Obtengo posicion de la variable %c, que es %i-------\n",identificador_variable,posicion);
	return posicion;
}


/*
 Obtiene el valor resultante de leer a partir de direccion_variable, sin importar cual fuera el
contexto actual
 */
t_valor_variable dereferenciar(t_puntero direccion_variable){
	t_valor_variable valor;
	memcpy(&valor,stack+direccion_variable,sizeof(t_valor_variable));
	printf("---El valor de la variable de la posicion %i es %i\n",direccion_variable,valor);
	return valor;
}


/*
 * Copia un valor en la variable ubicada en direccion_variable
 */
void asignar(t_puntero direccion_variable, t_valor_variable valor ){
	memcpy(stack+direccion_variable,&valor,sizeof(t_valor_variable));
	printf("---------Asigno el valor %i a la variable de la posicion %i------\n",valor,direccion_variable);
}


/*
 Envía al Kernel el contenido de valor_mostrar, para que este le reenvíe a la correspondiente
consola del Programa en ejecución. Devuelve la cantidad de dígitos impresos.
 */
int imprimir(t_valor_variable valor_mostrar){
	printf("---------Imprimo valor de la variable %i------\n",valor_mostrar);
	return CONTENIDO_VARIABLE;
}


/*
 Preserva el contexto de ejecución actual para poder retornar luego. Modifica las estructuras
correspondientes para mostrar un nuevo contexto vacío. Retorna el numero de instrucción a
ejecutar.
Los parámetros serán definidos luego de esta instrucción de la misma manera que una variable
local, con identificadores numéricos empezando por el 0.
 */
t_puntero_instruccion llamarSinRetorno(t_nombre_etiqueta etiqueta,t_puntero_instruccion linea_en_ejecuccion){
	uint32_t offset = 0;
	uint32_t cursor = diccionario->cursor;
	apilarCRef(stack,&cursor); // Apilo el cursor del contexto de ejecucion
//	memcpy(stack+stack->punteroUlt,&cursor,sizeof(int));
//	offset = stack->punteroUlt + sizeof(uint32_t);
	uint32_t proxPC = pcb.PC + 1;
	apilarCRef(stack,&proxPC); // Apilo el PC para la proxima instruccion
//	memcpy(stack+offset,&proxPC,sizeof(uint32_t));
	inicializarDiccionario(diccionario); //Blanqueo el diccionario de variables
	diccionario->cursor = diccionario->ultimo; // Coloco el cursor al final del apilado
	// Pedir instruccion en el indice de etiquetas
	printf("------------Llamo a la funcion sin retorno --------\n");
}


/*
 Preserva el contexto de ejecución actual para poder retornar luego al mismo, junto con la
posicion de la variable entregada por donde_retornar . Modifica las estructuras
correspondientes para mostrar un nuevo contexto vacío. Retorna el número de instrucción a
ejecutar.
Los parámetros serán definidos luego de esta instrucción de la misma manera que una variable
local, con identificadores numéricos empezando por el 0.
No se pretende que se pueda retornar a una variable global. Sí a un parámetro o variable local
 */
t_puntero_instruccion llamarConRetorno(t_nombre_etiqueta etiqueta,t_puntero donde_retornar,t_puntero_instruccion linea_en_ejecuccion){
	uint32_t offset = 0;
	uint32_t cursor = diccionario->cursor;
	apilarCRef(stack,&cursor); // Apilo el cursor del contexto de ejecucion
//	memcpy(stack+stack->punteroUlt,&cursor,sizeof(int));
//	offset = stack->punteroUlt + sizeof(int);
	uint32_t proxPC = pcb.PC + 1;
	apilarCRef(stack,&proxPC); // Apilo el PC para la proxima instruccion
//	memcpy(stack+offset,&proxPC,sizeof(uint32_t));
	inicializarDiccionario(diccionario); // Blanqueo el diccionario de variables
//	offset = offset + sizeof(uint32_t);
	apilarCRef(stack,&donde_retornar); // Apilo la direccion de retorno de la variable
//	memcpy(stack+offset,&donde_retornar,sizeof(t_puntero));
	inicializarDiccionario(diccionario); //Blanqueo el diccionario de variables
	diccionario->cursor = diccionario->ultimo; // Coloco el cursor al final del apilado
	// Pedir instruccion en el indice de etiquetas
	printf("------------Llamo a la funcion con retorno --------\n");
	return 1; //LO AGREGUE A MANO
}


/*
 Cambia el Contexto de Ejecución Actual para volver al Contexto anterior al que se está
ejecutando, recuperando el Cursor de Contexto Actual y el Program Counter previamente
apilados en el Stack. En caso de estar finalizando el Contexto principal (el ubicado al inicio del
Stack), deberá finalizar la ejecución del programa devolviendo el valor -1.
 */
t_puntero_instruccion finalizar(void){
	// DESARROLLAR FUNCION
	printf("----------------  Llamo a finalizar -------------\n");
	return 1; // Esto no va, es para completar
}


/*
 * Modifica el Contexto de Ejecución Actual por el Contexto anterior al que se está ejecutando,
recuperando el Cursor de Contexto Actual, el Program Counter y la direccion donde retornar,
asignando el valor de retorno en esta, previamente apilados en el Stack.
 */
t_puntero_instruccion retornar(t_valor_variable retorno){
	if (stack->cantElem > 2){
		uint32_t* dirRet = (uint32_t*) desapilarCRef(stack); // Desapilo la direccion de retorno
		uint32_t* pcAct = (uint32_t*) desapilarCRef(stack); // Desapilo el PC de la proxima instruccion a ejecutar
		uint32_t* cursorAnt = (uint32_t*) desapilarCRef(stack); // Desapilo el contexto de ejecucion anterior
		diccionario->cursor = *cursorAnt; // Asigno el cursor del contexto al anterior
		pcb.PC = *pcAct; // Asigno el PC con la instruccion apilada anteriormente
		asignar(*dirRet,retorno); // Usando la primitiva asigno el valor de retorno
		inicializarDiccionario(diccionario); //Blanqueo el diccionario de variables
		cargarDiccionario(diccionario,stack); // Vuelvo a obtener los indices del diccionario
	} else {
		// Completar
	}
	return 1; //Esto no va, es para completar
	printf("---------------- Llamo a retornar -------------\n");
}

// --------------------- FUNCIONES DEL PARSER ANSISOP -------------------

AnSISOP_funciones functions = {
		.AnSISOP_definirVariable		= definirVariable,
		.AnSISOP_imprimirTexto			= imprimirTexto,
		.AnSISOP_obtenerPosicionVariable= obtenerPosicionVariable,
		.AnSISOP_dereferenciar			= dereferenciar,
		.AnSISOP_asignar				= asignar,
		.AnSISOP_imprimir				= imprimir,
};
AnSISOP_kernel kernel_functions = { };

// ------------------------- FIN PARSER ANSISOP -------------------------




int main(void){

	diccionario = malloc(sizeof(t_dicVar));
	stack = crearStackC();

	// Limpio el diccionario de variables
	inicializarDiccionario(diccionario);

	// Creo un PCB
	pcb.id = 2;
	pcb.codSeg = 0;
	pcb.cursorStack = 0;
	pcb.PC = 4;
	pcb.indCod = 800;
	pcb.indEtiq = 500;
	pcb.stackSeg = 1024;
	pcb.tamContext = 0;

	// Creo un stack serializado
	t_variable varA;
	varA.id = 'a';
	t_variable varB;
	varB.id = 'b';
	varB.valor = 10;
	int size=0; int offset=0;
	memcpy(stackChar,&varA,sizeof(t_variable));
	size = sizeof(t_variable);
	offset = size;
	memcpy(stackChar+offset,&varB,size);
	// Lo convierto a una pila
	stringAStack(stackChar,stack,pcb.tamContext);

	// Obtengo metadata
	t_medatada_program* programa = metadatada_desde_literal(codigo);
	// Cargo el serializado de instrucciones
	memcpy(serEtiquetas,programa->instrucciones_serializado,programa->instrucciones_size*8);

	char control = 's';

	while (control == 's'){
		printf("Ingrese una cadena: \n");
		gets(sentenciaEjec);
		analizadorLinea(strdup(sentenciaEjec), &functions, &kernel_functions);

		printf("---------------Imprimo PCB-------------------\n");
		imprimirPCB(&pcb);
		printf("---------------Imprimo Stack-------------------\n");
		imprimirStack(stack);

		printf("Desea continuar? S/N\n");
		gets(&control);
	}

	return 1;
}
