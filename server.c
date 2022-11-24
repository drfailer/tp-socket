#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

void doublement(char str[], char out[]) {
  int i = 0, j = 0;

  while (str[i]) {
    out[j] = str[i];
    out[j + 1] = str[i];
    j += 2;
    ++i;
  }
  out[j] = 0;
}

int valeur(char *str) {
  int i = 0;
  int v = 0;

  while (str[i]) {
    v += str[i] - 'a';
    ++i;
  }

  return v;
}


int main(void) {
  int s_ecoute, scom, lg_app;
  struct sockaddr_in addr;
  struct sockaddr_storage recep;
  char buf[1500], renvoi[1500], host[1024], service[20];

  s_ecoute = socket(AF_INET, SOCK_STREAM, 0);
  printf("creation socket\n");

  addr.sin_family = AF_INET;
  addr.sin_port = htons(9876);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(s_ecoute, (struct sockaddr*) &addr, sizeof(struct sockaddr_in)) != 0) {
    fprintf(stderr, "error bind\n");
    exit(1);
  }

  if (listen(s_ecoute,5) != 0) {
    printf("pb ecoute\n"); exit(1);
  }

  printf("en attente de connexion\n");
  while (1) {
    scom=accept(s_ecoute,(struct sockaddr *)&recep, (unsigned long *)&lg_app);
    getnameinfo((struct sockaddr *)&recep,sizeof (recep), host, sizeof(host),service,
        sizeof(service),0); //optionnelle pour info
    printf("recu de %s venant du port %s\n",host, service); //optionnnelle
    while (1) {
      recv(scom,buf,sizeof(buf),0);
      printf("buf recu %s\n",buf);
      bzero(renvoi,sizeof(renvoi));

      if (buf[strlen(buf) - 1] == '0') {
        buf[strlen(buf) - 1] = 0;
        doublement(buf, renvoi);
        printf("%s", renvoi);
      }
      else if (buf[strlen(buf) - 1] == '1') {
        buf[strlen(buf) - 1] = 0;
        sprintf(renvoi, "%d", valeur(buf));
      }
      else {
        break;
      }

      send(scom,renvoi,strlen(renvoi),0);
      bzero(buf,sizeof(buf));
    }
    close(scom);
  }

  close(s_ecoute);
  return 0;
}
