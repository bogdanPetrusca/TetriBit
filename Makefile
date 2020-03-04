CC = gcc
CFLAGS = -Wall -lm
SRC = tema1.c
EXE = tema1
build:
	$(CC) -o $(EXE) $(SRC) $(CFLAGS)
.PHONY : clean
clean :
	rm -f $(EXE) *~
