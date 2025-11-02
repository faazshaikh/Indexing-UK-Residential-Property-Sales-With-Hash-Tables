CC = gcc
CFLAGS = -Wall -Wextra -std=c99
EXECUTABLE = runprogram
SRC = main.c myDSlib.c
OBJ = main.o myDSlib.o

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(EXECUTABLE) $(OBJ)
