ALL:main


inc_path=./inc

main:./obj/main.o ./obj/speechManger.o
	g++ ./obj/main.o ./obj/speechManger.o -o main 
./obj/main.o:./src/main.cpp
	g++ -c ./src/main.cpp -o ./obj/main.o	  -I  $(inc_path) 
./obj/speechManger.o:./src/speechManger.cpp
	g++ -c ./src/speechManger.cpp -o ./obj/speechManger.o -I $(inc_path)


clean:
	-rm -rf ./obj/*.o main
.PHOMY: clean ALL
