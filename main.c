#include <stdio.h>
#include <stdlib.h>
#include "helpers/sockets.c"

// Defaults
#define DEFAULT_PORT 5000
#define MAX_CONNECTIONS 80
#define MAXDATASIZE 5000

int main(int argc, char const *argv[])
{
	int Socket, Bind, Listen, Coisa;
	int tamanho, NewSocket, out_size, numbytes;
	struct sockaddr_in endereco_dele;
	char *out;
	char buf[MAXDATASIZE];

	// Create socket
	Socket = start_socket();

  	// Bind socket in one port
  	Bind = bind_socket(Socket, DEFAULT_PORT);

  	// Set Connections limit
	Listen = listen_socket(Socket, MAX_CONNECTIONS);

	printf("%s\n", "Está funcionando!");


	  while(1) {
	    tamanho = sizeof(struct sockaddr_in);
	    if ((NewSocket = accept(Socket, (struct sockaddr *)&endereco_dele,&tamanho)) < 0){
	      perror("accept");
	      continue;
	    }
	    
	    printf("HTTP/1.1 200 OK\r\n",inet_ntoa(endereco_dele.sin_addr));


	    out = "HTTP/1.1 200 OK\r\nContent-Type:text/html; charset=utf-8\r\nConnection: close\r\n\r\n<input name='outro' />";

	    out_size = strlen(out);

	    if (!fork()) {
	      if (send(NewSocket, out, out_size, 0) == -1)
	      {

	        perror("send");
	        close(NewSocket);
	        exit(0);
	      }
	    }

	    if ((numbytes=recv(NewSocket, buf, sizeof buf, MSG_DONTWAIT)) == -1) 
	    {
	        perror("recv");
	        exit(1);
	    }
	    buf[numbytes] = '\0';
	    printf("%s",buf);
	    close(NewSocket);

	    while(waitpid(-1,NULL,WNOHANG) > 0); /* Limpa o processo crianca.fork() */
	  }	

	return 0;
};
