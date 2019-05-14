/*
 * client.c
 * Version 20161003
 * Written by Harry Wong (RedAndBlueEraser)
 */

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdint.h>

typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;


void* serializar_paquete(t_paquete* paquete, int bytes);
void crear_buffer(t_paquete* paquete);
void enviar_mensaje(char* mensaje, int socket_cliente);
void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);
void eliminar_paquete(t_paquete* paquete);
void enviar_paquete(t_paquete* paquete, int socket_cliente);


int main(int argc, char *argv[]) {

    int puertoServidor, socket_fd;
    struct sockaddr_in server_address;

    memset(&server_address, 0, sizeof server_address);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    /*Variables para el cliente*/
    char* mensaje;

    /* Create TCP socket. */
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("ERROR: socket");
        exit(1);
    }

    /* Connect to socket with server address. */
    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof server_address) == -1) {
		perror("ERROR: connect");
        exit(1);
	}

    printf("Se establecio la conexion con el servidor\n");


    	/* TODO: Put server interaction code here. For example, use
    	 * write(socket_fd,,) and read(socket_fd,,) to send and receive messages
    	 * with the client.
    	 */
    while(1){
    	enviar_mensaje("Maestro", socket_fd);
    }

    close(socket_fd);
    return 0;
}

void enviar_mensaje(char* mensaje, int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = 100;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = strlen(mensaje) + 1;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, mensaje, paquete->buffer->size);

	int bytes = paquete->buffer->size + 2*sizeof(int);//los dos sizeof(int) son para
	//despues

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
	eliminar_paquete(paquete);
}

void* serializar_paquete(t_paquete* paquete, int bytes)
{
	void * paqueteAEnviar = malloc(bytes);
	int desplazamiento = 0;
	//creo un espacio en memoria que tiene como tamaño maximo "bytes" y
	//voy llenando el espacio con..
	/*memcpy(paqueteAEnviar + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento+= sizeof(int);*/
	memcpy(paqueteAEnviar + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(paqueteAEnviar + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento+= paquete->buffer->size;

	return paqueteAEnviar;
}

/*
void crear_buffer(t_paquete* paquete)
{
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = 0;
	paquete->buffer->stream = NULL;
}

void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio)
{
	paquete->buffer->stream = realloc(paquete->buffer->stream, paquete->buffer->size + tamanio + sizeof(int));

	memcpy(paquete->buffer->stream + paquete->buffer->size, &tamanio, sizeof(int));
	memcpy(paquete->buffer->stream + paquete->buffer->size + sizeof(int), valor, tamanio);

	paquete->buffer->size += tamanio + sizeof(int);
}

void enviar_paquete(t_paquete* paquete, int socket_cliente)
{
	int bytes = paquete->buffer->size + 2*sizeof(int);
	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
}*/

void eliminar_paquete(t_paquete* paquete)
{
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}
