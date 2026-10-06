/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"
#include "bmp.h"

int envoie_recois_message(int socketfd)
{
  char data[4096];
  memset(data, 0, sizeof(data));

  char message[1024];
  printf("Votre message (max 1000 caracteres): ");
  if (fgets(message, sizeof(message), stdin) == NULL)
  {
    return -1;
  }

  message[strcspn(message, "\r\n")] = '\0';
  snprintf(data, sizeof(data), "{\"code\":\"message\",\"valeurs\":[\"%s\"]}", message);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  memset(data, 0, sizeof(data));
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }

  printf("Message recu: %s\n", data);
  return 0;
}

static void ajouter_couleur_json(char *buffer, size_t buffer_size, size_t *offset, const couleur_compteur *cc, int index, int *first_color)
{
  if (cc->compte_bit == BITS24)
  {
    snprintf(buffer + *offset, buffer_size - *offset, "%s\"#%02x%02x%02x\"",
             (*first_color) ? "" : ",",
             cc->cc.cc24[index].c.rouge,
             cc->cc.cc24[index].c.vert,
             cc->cc.cc24[index].c.bleu);
  }
  else if (cc->compte_bit == BITS32)
  {
    snprintf(buffer + *offset, buffer_size - *offset, "%s\"#%02x%02x%02x\"",
             (*first_color) ? "" : ",",
             cc->cc.cc32[index].c.rouge,
             cc->cc.cc32[index].c.vert,
             cc->cc.cc32[index].c.bleu);
  }
  *first_color = 0;
  *offset = strlen(buffer);
}

void analyse(char *pathname, char *data, size_t data_size, int nb_couleurs)
{
  couleur_compteur *cc = analyse_bmp_image(pathname);
  if (cc == NULL)
  {
    snprintf(data, data_size, "{\"code\":\"erreur\",\"message\":\"Impossible de lire le fichier BMP\"}");
    return;
  }

  int total_couleurs = (nb_couleurs < cc->size) ? nb_couleurs : cc->size;
  if (total_couleurs < 1)
  {
    total_couleurs = 1;
  }

  size_t offset = 0;
  int first_color = 1;
  int written = snprintf(data, data_size, "{\"code\":\"couleurs\",\"n\":%d,\"valeurs\":[", total_couleurs);
  if (written < 0 || (size_t)written >= data_size)
  {
    return;
  }
  offset = (size_t)written;

  for (int i = 0; i < total_couleurs; i++)
  {
    int index = i;
    ajouter_couleur_json(data, data_size, &offset, cc, index, &first_color);
  }

  snprintf(data + offset, data_size - offset, "]}");
}

int envoie_couleurs(int socketfd, char *pathname, int nb_couleurs)
{
  char data[4096];
  memset(data, 0, sizeof(data));
  analyse(pathname, data, sizeof(data), nb_couleurs);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  return 0;
}

int main(int argc, char **argv)
{
  int socketfd;
  struct sockaddr_in server_addr;
  int nb_couleurs = 10;

  if (argc < 2)
  {
    printf("usage: ./client chemin_bmp_image [nombre_couleurs]\n");
    return (EXIT_FAILURE);
  }

  if (argc >= 3)
  {
    nb_couleurs = atoi(argv[2]);
    if (nb_couleurs < 1 || nb_couleurs > 30)
    {
      nb_couleurs = 10;
    }
  }

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  if (argc == 2)
  {
    envoie_couleurs(socketfd, argv[1], nb_couleurs);
  }
  else
  {
    envoie_couleurs(socketfd, argv[1], nb_couleurs);
  }

  close(socketfd);
  return 0;
}
