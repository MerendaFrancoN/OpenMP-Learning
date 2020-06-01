CC = gcc
CCFLAGS = -Wall -Werror -Wextra -pedantic 
LDFLAGS =  -fopenmp -std=c99 

SRC = ejercicio5.c
OBJ = $(SRC:.cc=.o)
EXEC = ejercicio5

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(EXEC)
