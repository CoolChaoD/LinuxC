ALL:server

inc_path=./inc



server:./obj/server.o  ./obj/common.o
	gcc  ./obj/server.o ./obj/common.o -o server

./obj/server.o:server.c common.h
	gcc -c server.c

common.o:common.c common.h
	gcc -c common.c

clean:
	rm -rf *.o server

