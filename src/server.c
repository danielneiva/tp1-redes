#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(){

  char *ip = "::1";
  int port = 5713;

  int server_sock, client_sock;

  struct sockaddr_in6 server_address, client_address;
  socklen_t addr_size;

  char buffer[1024];
  int n;

  server_sock = socket(AF_INET6, SOCK_STREAM, 0);

  if (server_sock < 0){
    perror("[-] Socker error");
    exit(1);
  }

  printf("[+] TCP server socket created. \n");

  memset(&server_address, '\0', sizeof(server_address));

  server_address.sin6_family = AF_INET6;
  server_address.sin6_port = port;
  server_address.sin6_addr = in6addr_any;


  n = bind(server_sock, (struct sockaddr*)&server_address, sizeof(server_address));

  if (n < 0){
    perror("[-] Bind error");
    exit(1);
  }

  printf("[+] Bind to the port number: %d\n", port);

  listen(server_sock, 5);
  printf("Listening...\n");

  while(1){
    addr_size = sizeof(client_address);
    client_sock = accept(server_sock, (struct sockaddr*)&client_address, &addr_size);
    printf("[+] Client connected.\n");

    bzero(buffer, 1024);
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    bzero(buffer, 1024);
    strcpy(buffer, "Hello back");
    printf("Server: %s\n", buffer);
    send(client_sock, buffer, strlen(buffer), 0);

    close(client_sock);
    printf("[+] Client disconnected. \n\n");


  }


  return 0;
}