CC = gcc
CCFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 
LDFLAGS =  -fopenmp -fsanitize=address

SRC = ejercicio2.c
OBJ = $(SRC:.cc=.o)
EXEC = ejercicio2

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(EXEC)