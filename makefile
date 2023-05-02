CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

all: main

main.o: main.c
	gcc $(CFLAGS) -c main.c

highlow.o: highlow.c
	gcc $(CFLAGS) -c highlow.c

gui.o: gui.c
	gcc $(CFLAGS) -c gui.c

main: main.o highlow.o gui.o
	gcc -o main main.o highlow.o gui.o $(LIBS)

clean:
	rm -f main *.o
