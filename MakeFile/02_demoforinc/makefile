src=$(wildcard ./src/*.c) #获取src目录下所有的.c文件 存放进src列表下
obj=$(patsubst ./src/%.c, ./obj/%.o,$(src)) #./obj/add.o/ 

inc_path=./inc

myArgs =-Wall -g 
ALL:a.out

a.out:$(obj)
	gcc $^ -o $@ $(myArgs)
$(obj):./obj/%.o:./src/%.c
	gcc -c $< -o $@ $(myArgs) -I $(inc_path)

clean:
	-rm -rf $(obj) a.out

.PHONY: clean ALL
