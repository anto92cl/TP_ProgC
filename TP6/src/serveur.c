/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#define _GNU_SOURCE
#include <math.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "serveur.h"

int socketfd;
const char *svg_file_path = "pie_chart.svg";

static int visualiser_plot(void)
{
  const char *browser = "xdg-open";

  if (access("/usr/bin/firefox", X_OK) == 0)
  {
    browser = "firefox";
  }
  else if (access("/usr/bin/google-chrome", X_OK) == 0)
  {
    browser = "google-chrome";
  }

  char command[256];
  snprintf(command, sizeof(command), "%s %s", browser, svg_file_path);

  int result = system(command);
  if (result == 0)
  {
    printf("SVG file opened in %s.\n", browser);
  }
  else
  {
    printf("Failed to open the SVG file.\n");
  }

  return 0;
}

double degreesToRadians(double degrees)
{
  return degrees * M_PI / 180.0;
}

static void extraire_couleurs_json(const char *data, char *result, size_t result_size)
{
  const char *array_start = strstr(data, "\"valeurs\"");
  result[0] = '\0';
  if (array_start == NULL)
  {
    return;
  }

  array_start = strchr(array_start, '[');
  if (array_start == NULL)
  {
    return;
  }

  const char *cursor = array_start + 1;
  size_t index = 0;
  while ((cursor = strchr(cursor, '"')) != NULL)
  {
    cursor++;
    const char *end = strchr(cursor, '"');
    if (end == NULL)
    {
      break;
    }

    char color[32];
    size_t color_len = (size_t)(end - cursor);
    if (color_len >= sizeof(color))
    {
      color_len = sizeof(color) - 1;
    }
    memcpy(color, cursor, color_len);
    color[color_len] = '\0';

    if (index > 0)
    {
      strncat(result, ",", result_size - strlen(result) - 1);
    }
    strncat(result, color, result_size - strlen(result) - 1);
    index++;
    cursor = end + 1;
  }
}

int plot(char *data)
{
  char *saveptr = NULL;
  char *token = NULL;
  int count = 0;
  char *copy = strdup(data);
  if (copy == NULL)
  {
    perror("strdup");
    return 1;
  }

  for (token = strtok_r(copy, ",", &saveptr); token != NULL; token = strtok_r(NULL, ",", &saveptr))
  {
    count++;
  }

  FILE *svg_file = fopen(svg_file_path, "w");
  if (svg_file == NULL)
  {
    perror("Error opening file");
    free(copy);
    return 1;
  }

  fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
  fprintf(svg_file, "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(svg_file, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#ffffff\" />\n");

  double center_x = 200.0;
  double center_y = 200.0;
  double radius = 150.0;
  double start_angle = -90.0;

  if (count > 0)
  {
    char *str = data;
    int i = 0;
    while ((token = strtok_r(str, ",", &saveptr)) != NULL)
    {
      str = NULL;
      double angle = 360.0 / count;
      double end_angle = start_angle + angle;

      double start_angle_rad = degreesToRadians(start_angle);
      double end_angle_rad = degreesToRadians(end_angle);

      double x1 = center_x + radius * cos(start_angle_rad);
      double y1 = center_y + radius * sin(start_angle_rad);
      double x2 = center_x + radius * cos(end_angle_rad);
      double y2 = center_y + radius * sin(end_angle_rad);

      fprintf(svg_file, "  <path d=\"M%.2f,%.2f A%.2f,%.2f 0 0,1 %.2f,%.2f L%.2f,%.2f Z\" fill=\"%s\" />\n",
              x1, y1, radius, radius, x2, y2, center_x, center_y, token);

      start_angle = end_angle;
      i++;
      if (i >= count)
      {
        break;
      }
    }
  }

  fprintf(svg_file, "</svg>\n");
  fclose(svg_file);
  free(copy);

  visualiser_plot();
  return 0;
}

int renvoie_message(int client_socket_fd, char *data)
{
  int data_size = write(client_socket_fd, (void *)data, strlen(data));

  if (data_size < 0)
  {
    perror("erreur ecriture");
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

int recois_envoie_message(int client_socket_fd, char data[1024])
{
  printf("Message recu: %s\n", data);

  if (strstr(data, "\"code\":\"message\"") != NULL)
  {
    renvoie_message(client_socket_fd, data);
    return (EXIT_SUCCESS);
  }

  if (strstr(data, "\"code\":\"couleurs\"") != NULL)
  {
    char couleurs[1024];
    extraire_couleurs_json(data, couleurs, sizeof(couleurs));
    if (couleurs[0] != '\0')
    {
      plot(couleurs);
    }
    return (EXIT_SUCCESS);
  }

  char code[16];
  sscanf(data, "%15s", code);
  if (strcmp(code, "message:") == 0)
  {
    renvoie_message(client_socket_fd, data);
  }
  else
  {
    plot(data);
  }

  return (EXIT_SUCCESS);
}

void gestionnaire_ctrl_c(int signal)
{
  (void)signal;
  printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");
  close(socketfd);
  exit(0);
}

int main(void)
{
  int bind_status;
  struct sockaddr_in server_addr;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("Unable to open a socket");
    return -1;
  }

  int option = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_status < 0)
  {
    perror("bind");
    return (EXIT_FAILURE);
  }

  signal(SIGINT, gestionnaire_ctrl_c);

  while (1)
  {
    listen(socketfd, 10);

    struct sockaddr_in client_addr;
    char data[1024];

    unsigned int client_addr_len = sizeof(client_addr);

    int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket_fd < 0)
    {
      perror("accept");
      return (EXIT_FAILURE);
    }

    memset(data, 0, sizeof(data));
    int data_size = read(client_socket_fd, (void *)data, sizeof(data));

    if (data_size < 0)
    {
      perror("erreur lecture");
      return (EXIT_FAILURE);
    }

    recois_envoie_message(client_socket_fd, data);
  }

  return 0;
}
