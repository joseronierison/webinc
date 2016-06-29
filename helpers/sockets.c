#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>

// interface methods
int start_socket();
int bind_socket(int Socket, int port);
int listen_socket(int Socket, int max_connections);

// Create websocket
int start_socket()
{
	int Socket;

	Socket = socket(AF_INET, SOCK_STREAM, 0);

	if (Socket == -1) {
	    perror("socket");
	    exit(1);
  	}

	return Socket;
}

// Assign websocket to port
int bind_socket(int Socket, int port)
{
	int Bind;
	struct sockaddr_in address;

	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;
	bzero(&(address.sin_zero), 8);  

	Bind = bind(Socket,(struct sockaddr *)&address, sizeof(struct sockaddr));

	if (Bind == -1) {
		perror("bind");
		exit(1);
  	}

	return Bind;
}

int listen_socket(int Socket, int max_connections)
{
	int Listen;

	Listen = listen(Socket, max_connections);

	if (Listen < 0) {
		perror("listen");
		exit(1);
	}	

	return Listen;
}

