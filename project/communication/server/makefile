ALL:server

inc_path=./inc



server:./obj/server.o  ./obj/common.o
	gcc  ./obj/server.o ./obj/common.o -o server

./obj/server.o:./src/server.c 
	gcc -c ./src/server.c -o ./obj/server.o -I $(inc_path)
./obj/common.o:./src/common.c 
	gcc -c ./src/common.c -o ./obj/common.o -I $(inc_path)

clean:
	-rm -rf  ./obj/*.o server
.PHONY: clean ALL

