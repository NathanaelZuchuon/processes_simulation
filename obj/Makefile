### __MAKEFILE___ ###

CC = gcc
CFLAGS = -m32
LDFLAGS = -m32 -L"../lib" -lopengl32 -lglut32
EXEC = ../bin/zuchuon_simulator.exe

all : $(EXEC)
	$(EXEC)

$(EXEC): main.o fcfs.o ps.o rr.o sjf.o
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

main.o: ../src/main.c
	$(CC) -c $< $(CFLAGS)

fcfs.o: ../src/algorithms/fcfs.c
	$(CC) -c $< $(CFLAGS)

ps.o: ../src/algorithms/ps.c
	$(CC) -c $< $(CFLAGS)

rr.o: ../src/algorithms/rr.c
	$(CC) -c $< $(CFLAGS)

sjf.o: ../src/algorithms/sjf.c
	$(CC) -c $< $(CFLAGS)

clean:
	del *.o
