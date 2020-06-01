CC = gcc
CCFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 
LDFLAGS =  -fopenmp -fsanitize=address

SRC = ejercicio5.c
OBJ = $(SRC:.cc=.o)
EXEC = ejercicio5

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(EXEC)