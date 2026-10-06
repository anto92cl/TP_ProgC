CC ?= gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g

SERVER = serveur
CLIENT = client
REPERTOIRE = repertoire

all: $(SERVER) $(CLIENT) $(REPERTOIRE)

$(SERVER): serveur.o
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT): client.o
	$(CC) $(CFLAGS) -o $@ $^

$(REPERTOIRE): repertoire.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER) $(CLIENT) $(REPERTOIRE) *.o

