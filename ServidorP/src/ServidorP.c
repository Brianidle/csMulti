/*
 * server.c
 * Version 20161003
 * Written by Harry Wong (RedAndBlueEraser)
 */

#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define cantConecciones 10

typedef struct pthread_arg_t {
    int newClientSocket;
    struct sockaddr_in direccionCliente;
    /* TODO: Put arguments passed to threads here. See lines 116 and 139. */
} pthread_arg_t;

/* Thread routine to serve connection to client. */
void *pthread_routine(void *arg);

void recibir_mensaje(int socket_cliente);
void* recibir_buffer(int* size, int socket_cliente);

int main(int argc, char *argv[]) {

	int socketServidor, nuevoClienteSocket;
    struct sockaddr_in direccionServidor;
    pthread_attr_t pthread_attr;
    pthread_arg_t *pthread_arg;
    pthread_t pthread;
    socklen_t client_address_len;


    /* Initialise IPv4 address. */
    memset(&direccionServidor, 0, sizeof direccionServidor);
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons(8080);
    direccionServidor.sin_addr.s_addr = INADDR_ANY;

    /* Create TCP socket. */
    if ((socketServidor = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("ERROR: socket");
        exit(1);
    }

    /* Bind address to socket. */
    if (bind(socketServidor, (struct sockaddr *)&direccionServidor, sizeof direccionServidor) == -1) {
        perror("ERROR: bind");
        exit(1);
    }

    /* Listen on socket. */
    if (listen(socketServidor, cantConecciones) == -1) {
        perror("ERROR: listen");
        exit(1);
    }
    printf("Estoy escuchando \n");

    /* Initialise pthread attribute to create detached threads. */
    if (pthread_attr_init(&pthread_attr) != 0) {
        perror("pthread_attr_init");
        exit(1);
    }
    if (pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED) != 0) {
        perror("pthread_attr_setdetachstate");
        exit(1);
    }

    while (1) {
        /* Create pthread argument for each connection to client. */
        /* TODO: malloc'ing before accepting a connection causes only one small
         * memory when the program exits. It can be safely ignored.
         */
        pthread_arg = (pthread_arg_t *)malloc(sizeof *pthread_arg);
        if (!pthread_arg) {
            perror("malloc");
            continue;
        }

        /* Accept connection to client. */
        //socklen_t len = sizeof(direccionCliente) es lo mismo
        client_address_len = sizeof pthread_arg->direccionCliente;

        //int cliente= accept(servidor,(void*) &direccionCliente, &len); es lo mismo
        nuevoClienteSocket = accept(socketServidor, (void*)&pthread_arg->direccionCliente, &client_address_len);
        printf("Se conecto el cliente numero %d, estas son sus caracteristicas\n",nuevoClienteSocket);
        printf("Numero Puerto: %d\n",pthread_arg->direccionCliente.sin_port);
        printf("Direccion IP: %d\n",pthread_arg->direccionCliente.sin_addr.s_addr);

        if (nuevoClienteSocket == -1) {
            perror("ERROR: accept");
            free(pthread_arg);
            continue;
        }

        //usleep(3000000);//3 segundo
        /* Initialise pthread argument. Basicamente guardo el socket en una estrucutra
         y lo voy a pasar por parametro en la funcion que va a ejecutar en un thread*/
        pthread_arg->newClientSocket = nuevoClienteSocket;
        /* TODO: Initialise arguments passed to threads here. See lines 22 and
         * 139.
         */

        /* Create thread to serve connection to client. */
        if (pthread_create(&pthread, &pthread_attr, pthread_routine, (void *)pthread_arg) != 0) {
            perror("ERROR: pthread_create");
            free(pthread_arg);
            continue;
        }
        pthread_join(pthread,NULL);
        //Como cerrar el servidor?
    }

    /* close(socket_fd);*/

    return 0;
}

void *pthread_routine(void *arg) {
    pthread_arg_t *pthread_arg = (pthread_arg_t *)arg;
    int newClienteSocket = pthread_arg->newClientSocket;//sino lo declaro en un nuevo int newCLientSocket me devuelve 0
    struct sockaddr_in client_address = pthread_arg->direccionCliente;
    /* TODO: Get arguments passed to threads here. See lines 22 and 116. */
    free(arg);

    while(1){
    	recibir_mensaje(newClienteSocket);
    }

    /* TODO: Put client interaction code here. For example, use
     * write(new_socket_fd,,) and read(new_socket_fd,,) to send and receive
     * messages with the client.
     */

    close(newClienteSocket);
    return NULL;
}

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), 0);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, 0);

	return buffer;
}

void recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	printf("Me llego el mensaje %s", buffer);
	free(buffer);
}
