CC = gcc
CCFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 
LDFLAGS =  -fopenmp -lm -O0

SRC = ejercicio8.c
OBJ = $(SRC:.cc=.o)
EXEC = ejercicio8

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(EXEC)