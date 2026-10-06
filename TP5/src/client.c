/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "client.h"

int envoie_operateur_numeros(int socketfd, const char *operateur, int num1, int num2)
{
  char data[1024];
  snprintf(data, sizeof(data), "calcule : %s %d %d", operateur, num1, num2);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  memset(data, 0, sizeof(data));

  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  printf("Résultat reçu: %s\n", data);
  return 0;
}

int envoie_recois_message(int socketfd)
{
  char data[4096];
  char message[1024];

  memset(data, 0, sizeof(data));

  printf("Votre message (max 1000 caractères): ");
  if (fgets(message, sizeof(message), stdin) == NULL) {
    return -1;
  }

  message[strcspn(message, "\r\n")] = '\0';
  snprintf(data, sizeof(data), "message: %s", message);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  memset(data, 0, sizeof(data));

  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  printf("Message reçu: %s\n", data);
  return 0;
}

int main(void)
{
  int socketfd;
  struct sockaddr_in server_addr;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("connection serveur");
    close(socketfd);
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    char choix[16];
    int num1, num2;
    char operateur[4];

    printf("Choisissez une option :\n");
    printf("1. Envoyer un message\n2. Calculer\n3. Quitter\nVotre choix : ");
    if (fgets(choix, sizeof(choix), stdin) == NULL) {
      break;
    }

    switch (choix[0])
    {
      case '1':
        envoie_recois_message(socketfd);
        break;
      case '2':
        printf("Opérateur (+, -, *, /, %%) : ");
        if (fgets(operateur, sizeof(operateur), stdin) == NULL) {
          continue;
        }
        operateur[strcspn(operateur, "\r\n")] = '\0';

        printf("Premier nombre : ");
        if (scanf("%d", &num1) != 1) {
          while (getchar() != '\n') {}
          continue;
        }
        while (getchar() != '\n') {}

        printf("Deuxième nombre : ");
        if (scanf("%d", &num2) != 1) {
          while (getchar() != '\n') {}
          continue;
        }
        while (getchar() != '\n') {}

        envoie_operateur_numeros(socketfd, operateur, num1, num2);
        break;
      case '3':
        close(socketfd);
        return EXIT_SUCCESS;
      default:
        printf("Choix invalide.\n");
        break;
    }
  }

  close(socketfd);
  return EXIT_SUCCESS;
}
