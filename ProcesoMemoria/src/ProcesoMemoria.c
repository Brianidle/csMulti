/*
 ============================================================================
 Name        : ProcesoMemoria.c
 Author      : Brian Quinteros
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<readline/readline.h>

//--Librerias Commons
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>

//--Librerias Socket
#include <arpa/inet.h>
#include <sys/socket.h>

//--Variables Globales
t_log* logger;
t_config* config;


void inicioProcesoMemoria();
int conectarseAlFileSystem();
int inicializarMemoriaPrincipal();
void inicializarProcesoGossiping();
void inicializarLogger();
void inicializarTablaSegmentos();
void inicializarTablaPaginas();
int inicializarMemoriaPrincipal();

//--Funciones para Paginas

int estaEnEstadoModificado();
int asignarNuevaPagina();

//--Funciones para Segmentos

int segmentoDisponible();//Cuando el segmento tiene espacio para paginas
int segmentoTodasPagModificadas();

int memoriaLlena();


//--Funciones del API que se usan en distintas operaciones

int existeElSegmentoDeLaTabla();//punto 1 Select y Punto 1y 2 de Inset
int buscarKeyDePagina();////punto 1 De Select e Insert.
//Hace 2 cosas dependiendo de la operacion y de si se
//encuentra la key en memoria o no

int solicitarNuevaPagLibre();// Solicita una nueva página libre para almacenar
//la key. En caso de no disponer de una página libre, se debe ejecutar el
//algoritmo de reemplazoy y en caso de no poder efectuarlo por estar la
//memoria full, ejecutar el Journal de la memoria. Punto 1 Select y Punto 2 Insert



//--Journal
void ejecutarJournal();//Si  al momento de realizar el Journaling una tabla no
//exista, deberá informar por archivo de log esta situación, pero el proceso
//deberá actualizar correctamente las tablas que sí existen.
void ejecucionJournalAutomatico();//Journal punto 2
//Hasta que no se realice uno de estos dos procesos, el FileSystem no tendrá
//conocimiento ni actualizará los datos modificados o agregados
//que cada memoria contenga.

//--Select
void ejecutarSelect();//punto 1

void ejecutarAlgoritmoReemplazo();//Se usa en el punto 3 de Select y el punto
//1 de Insert

//--Insert
void ejecutarInsert();//punto 1 y 2

int generarNuevoSegmento();

//--Create
void ejecutarCreate();

//--Describe
void ejecutarDescribe();

//--Drop
int existeSegmentoDeTabla();
void informarAlFsDeDrop();

//--Pool De Memorias/Gossiping

int main(void) {

	//*inicializarLogger();


}

void inicioProcesoMemoria(){
	if(!conectarseAlFileSystem()){
		loggear("No se pudo conectar al File System");
	}
	if(!inicializarMemoriaPrincipal()){
		loggear("No se pudo inicializar la memoria principal");
	}
}

int conectarseAlFileSystem(){

}

int inicializarMemoriaPrincipal(){

}

void inicializarProcesoGossiping(){

}

void inicializarTablaSegmentos(){

}

void inicializarTablaPaginas(){

}


int estaEnEstadoModificado(){

}

int asignarNuevaPagina(){

}

int segmentoDisponible(){

}

int segmentoTodasPagModificadas(){

}

int memoriaLlena(){

}

void ejecutarJournal(){

}

void inicializarLogger(){

	logger = log_create("ProcesoMemoria.log", "Log del Proceso Memoria", 1, LOG_LEVEL_INFO);
}

void loggear(char* mensaje){
	log_info(logger, mensaje);
}

