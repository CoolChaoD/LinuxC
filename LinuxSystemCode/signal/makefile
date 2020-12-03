src=$(wildcard *.c) #将所有的.c文件取出存放进入src这个变量中
target=$(patsubst %.c,%,$(src)) #将参数三种包含参数1的部分转换成参数2

ALL:$(target)

%:%.c
	gcc $< -o $@  #模式规则，将%.c中的c文件依次取出转换成%文件

clean:
	-rm -rf $(target)

.PHONY: clean ALL

