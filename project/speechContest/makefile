ALL:main


inc_path=./inc

main:./src/main.o ./src/speechManger.o
	g++ ./obj/main.o ./obj/speechManger.o -o main -I $(inc_path)
main.o:./src/main.cpp
	g++ -c ./src/main.cpp -o ./obj/main.o	  -I ./inc
speechManger.o:./src/speechManger.cpp
	g++ -c ./src/speechManger.cpp -o ./obj/speechManger.o -I $(inc_path)


clean:
	-rm -rf *.o main
.PHOMY: clean ALL
