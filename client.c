// CLIENT

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int main(void) {
  int sock;
  struct sockaddr_in sin;
  char buffer[32];

  sock = socket(AF_INET, SOCK_STREAM, 0);

  sin.sin_addr.s_addr = inet_addr("127.0.0.1");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(1025);

  if (connect(sock, (SOCKADDR*) &sin, sizeof(sin)) != -1) { // Connecte le client vers serveur
    printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
    
    if (recv(sock, buffer, 32, 0) != -1)
      printf("Recu : %s\n", buffer);
  } else
    printf("Connexion impossible\n");
  close(sock);
}
