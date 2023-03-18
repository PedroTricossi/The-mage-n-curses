CC = gcc
CFLAGS = -g -Wall -lncurses -ltinfo
GAME = main.o character.o
DEPS = character.h

all: game

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Create game executavle
game: $(GAME)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@rm -f *.o

purge: clean
	@rm server client

# EOF ----------------------------------------------------------