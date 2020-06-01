CC = gcc
CCFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 
LDFLAGS =  -fopenmp -O2

SRC = ejercicio6.c
OBJ = $(SRC:.cc=.o)
EXEC = ejercicio6

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(EXEC)