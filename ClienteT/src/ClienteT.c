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

#define SERVER_NAME_LEN_MAX 255

int main(int argc, char *argv[]) {
    //char server_name[SERVER_NAME_LEN_MAX + 1] = { 0 };
    int puertoServidor, socket_fd;
    //struct hostent *server_host;
    struct sockaddr_in server_address;

	char buffer[1000];

    char* mensaje;

    /* Get server name from command line arguments or stdin.
    if (argc > 1) {
        strncpy(server_name, argv[1], SERVER_NAME_LEN_MAX);
    } else {
        printf("Enter Server Name: ");
        scanf("%s", server_name);
    }*/

    /* Get server port from command line arguments or stdin.
    puertoServidor = argc > 2 ? atoi(argv[2]) : 0;
    if (!puertoServidor) {
        printf("Enter Port: ");
        scanf("%d", &puertoServidor);
    }*/


    /* Get server host from server name. */
    //server_host = gethostbyname(server_name);

    /* Initialise IPv4 server address with server host. */
    memset(&server_address, 0, sizeof server_address);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    //memcpy(&server_address.sin_addr.s_addr, server_host->h_addr, server_host->h_length);

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
    	memset(buffer, 0, sizeof(buffer));
    	printf("Ingrese el mensaje que desea enviar al servidor\n");
    	//nuevalinea
    	fgets(buffer, 1000, stdin);
    	//scanf("%s", buffer);
    	send(socket_fd, buffer, strlen(buffer),0);
    	/*printf("Message from server: ");
    	read(socket_fd, buffer, sizeof(buffer));
    	puts(buffer);*/
    }
    close(socket_fd);
    return 0;
}
