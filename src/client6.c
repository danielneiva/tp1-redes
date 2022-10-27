#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(){

  char *ip = "::1";
  int port = 5714;
  
  int sock;

  struct sockaddr_in6 addr;
  socklen_t addr_size;

  char buffer[1024];
  int n;

  sock = socket(AF_INET6, SOCK_STREAM, 0);

  if (sock < 0){
    perror("[-] Socker error");
    exit(1);
  }

  printf("[+] TCP server socket created. \n");

  //memset(&addr, '\0', sizeof(addr));

  addr.sin6_family = AF_INET6;
  addr.sin6_port = port;
  addr.sin6_addr = in6addr_any;

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the server.\n");

  bzero(buffer, 1024);
  strcpy(buffer, "HELLO WORLD");
  printf("Client: %s\n", buffer);
  send(sock, buffer, strlen(buffer), 0);

  bzero(buffer, 1024);
  recv(sock, buffer, sizeof(buffer), 0);
  printf("Server: %s\n", buffer);

  close(sock);
  printf("Disconnected from the server.\n");

  return 0;
}