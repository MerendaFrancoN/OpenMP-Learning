CC = gcc
CCFLAGS = -Wall -Werror -Wextra -pedantic 
LDFLAGS =  -fopenmp -lm -O0 -std=c99 

SRC = ejercicio8.c
OBJ = $(SRC:.cc=.o)
EXEC = ejercicio8

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(EXEC)
