#include <stdio.h>
#include <stdlib.h>
#include "helpers/sockets.c"

// Defaults
#define DEFAULT_PORT 5000
#define MAX_CONNECTIONS 80
#define MAXDATASIZE 5000

int main(int argc, char const *argv[]) {
	int Socket, Bind, Listen, Coisa;
	int tamanho, NewSocket, out_size, numbytes;
	struct sockaddr_in client_addres;
	char *out;
	char buf[MAXDATASIZE];

	// Create socket
	Socket = start_socket();

	// Bind socket in one port
	Bind = bind_socket(Socket, DEFAULT_PORT);

  // Set Connections limit
	Listen = listen_socket(Socket, MAX_CONNECTIONS);

	printf("%s\n", "It works!");

  while(1) {
    tamanho = sizeof(struct sockaddr_in);

    if ((NewSocket = accept(Socket, (struct sockaddr *)&client_addres,&tamanho)) < 0) {
      perror("accept");
      continue;
    }

    printf("HTTP/1.1 200 OK\r\n",inet_ntoa(client_addres.sin_addr));


    out = "HTTP/1.1 200 OK\r\nContent-Type:text/html; charset=utf-8\r\nConnection: close\r\n\r\n<h1>It works</h1>";

    out_size = strlen(out);

    if (!fork()) {
      memset(&buf[0], 0, sizeof(buf));

      if ((numbytes=read(NewSocket, &buf, sizeof buf)) == -1) {
        perror("read");
        close(NewSocket);
        exit(1);
      }

      buf[numbytes] = '\0';

      printf("%s\n",buf);

      if (send(NewSocket, out, out_size, 0) == -1) {
        perror("send");
        close(NewSocket);
        exit(0);
      }
    }

    close(NewSocket);

    while(waitpid(-1,NULL,WNOHANG) > 0);
  }

	return 0;
};
