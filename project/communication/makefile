server:server.o common.o
	gcc -o server server.o common.o

server.o:server.c common.h
	gcc -c server.c

common.o:common.c common.h
	gcc -c common.c

clean:
	rm -rf *.o server

