all: webserver.o
	gcc -o webserver webserver.o

webserver: webserver.c
	gcc -c webserver webserver.c

clean:
	rm -f webserver webserver.o