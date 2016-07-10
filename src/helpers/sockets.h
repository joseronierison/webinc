#ifndef SOCKETS_H
#define SOCKETS_H

int start_socket();
int bind_socket(int Socket, int port);
int listen_socket(int Socket, int max_connections);
int sum_ab(int a, int b){
  return a+b;
}

#endif
