src=$(wildcard *.cpp) #将所有的.c文件名取出来存放进入src中
target=$(patsubst %.cpp,%,$(src))

ALL:$(target)


%:%.c
	g++ $< -o $@ 

clean:
	-rm -rf $(target)
.PHONY:clean ALL

