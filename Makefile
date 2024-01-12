OBJS = main.o button.o
EXE = exe 
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAG = -Wall $(DEBUG)
INCFLAG = -I/opt/homebrew/include
LIB = -L/opt/homebrew/lib -lSDL2

$(EXE): $(OBJS)
	$(CC) $(LFLAG) $(INCFLAG) $(LIB) $(OBJS) -o $(EXE)

main.o: button.h
	$(CC) -v main.c $(CFLAGS) $(INCFLAG) $(LIB) $ main.c

button.o:
	$(CC)  -v button.c $(CFLAGS) $(INCFLAG) $(LIB) button.c

clean:
	rm *.o $(EXE) -v
