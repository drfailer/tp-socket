#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

void main(void) {
  char buff[200], txt[200];
  int port, rc, sock;
  struct sockaddr_in addr;
  struct hostent *entree;
  int i;
  int opt;
  int cont = 1;
  int len;

  addr.sin_port = htons(9876);
  addr.sin_family = AF_INET;
  entree = (struct hostent *) gethostbyname("turing");
  bcopy((char*) entree->h_addr, (char*) &addr.sin_addr, entree->h_length);

  sock = socket(AF_INET, SOCK_STREAM, 0);

  if (connect(sock, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) < 0) {
    printf(stderr, "connection error !\n");
    exit(1);
  }

  printf("connexion passe\n");

  while (cont) {
    bzero(txt, sizeof(txt));
    bzero(buff, sizeof(buff));

    printf("choisir option\n0 - doublement\n1 - valeur\n2 - exit\nanwer> ");
    scanf("%d", &opt);
    if (opt == 0 || opt == 1) {
      scanf("%s", txt);
      len = strlen(txt);
      txt[len++] = '0' + opt; // add option
    }
    else {
      txt[0] = '3';
      txt[1] = 0;
      cont = 0;
    }
    send(sock, txt, len + 1, 0);
    recv(sock, buff, sizeof(buff), 0);
    printf("recu: %s\n", buff);
  }
  close(sock);
}
