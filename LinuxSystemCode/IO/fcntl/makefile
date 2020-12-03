src=$(wildcard *.c) #将所有.c的文件名取出来放入src当中
target=$(patsubst %.c,%,$(src)) #将参数3中包含参数1的部分转换成参数2

ALL:$(target)

%:%.c
	gcc $< -o $@  #将规则命令中的依赖列表中的依赖依次取出套用模式规则

clean:
	-rm -rf $(target)
.PHONY: clean ALL
