ALL:client

inc_path=./inc



client:./obj/client.o  ./obj/common.o
	gcc  ./obj/client.o ./obj/common.o -o client

./obj/client.o:./src/client.c 
	gcc -c ./src/client.c -o ./obj/client.o -I $(inc_path)
./obj/common.o:./src/common.c 
	gcc -c ./src/common.c -o ./obj/common.o -I $(inc_path)

.PHONY: clean ALL
clean:
	-rm -rf  ./obj/*.o client
