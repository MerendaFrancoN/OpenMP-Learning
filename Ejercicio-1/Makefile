CC = gcc
CCFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 
LDFLAGS =  -fopenmp -fsanitize=address

SRC = ejercicio1.c
OBJ = $(SRC:.cc=.o)
EXEC = ejercicio1

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(EXEC)