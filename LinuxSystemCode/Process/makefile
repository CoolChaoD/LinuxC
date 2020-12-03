src=$(wildcard *c)
target=$(patsubst %.c,%,$(src))


ALL:$(target)

%:%.c
	g++ $< -o $@

clean: 
	-rm -rf $(target)
.PHONY: clean ALL
