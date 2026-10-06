COBJS ?= client.o bmp.o couleur.o
SOBJS ?= serveur.o

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SOBJS)
	gcc -o $(SERVER) $(SOBJS) -lm

$(CLIENT): $(COBJS)
	gcc -o $(CLIENT) $(COBJS)

clean:
	rm -f $(SERVER) $(CLIENT) *.o

.c.o:
	gcc -Wall -Werror -std=c11 -ggdb3 -c $*.c

