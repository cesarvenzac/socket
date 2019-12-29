// SERVEUR

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int main(void) {
  int sock;
  struct sockaddr_in sin;
  socklen_t recsize = sizeof(sin);

  int csock;
  struct sockaddr_in csin;
  socklen_t crecsize = sizeof(csin);
  char buffer[32] = "Test !";
  int sock_err;

  sock = socket(AF_INET, SOCK_STREAM, 0);

  sin.sin_addr.s_addr = htonl(INADDR_ANY); // Adresse IP automatique
  sin.sin_family = AF_INET;
  sin.sin_port = htons(1025);
	       
  sock_err = bind(sock, (SOCKADDR*) &sin, recsize); // Initialise la socket avec les infos

  if (sock_err != -1) {
    sock_err = listen(sock, 5); // Attend la connection client (limite : 5)

    if (sock_err != -1) {
      csock = accept(sock, (SOCKADDR*) &csin, &crecsize); // Le client se connecte
      printf("Client connecté avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
      sock_err = send(csock, buffer, 32, 0);
      
      if (sock_err != -1)
	printf("Chaine envoyée : %s\n", buffer);
      else
	printf("Echec de transmission\n");
    }
  }
  close(csock);
  close(sock);
}
