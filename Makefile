GCC = gcc -std=c11 -Wall -Werror -Wextra

all:sudoko

sudoko: sudoko_func.c sudoko.c
	$(GCC) $^
	./a.out


clang:
	@clang-format -i *.c *.h
	@clang-format -n *.c *.h

rebuild: clean sudoko

clean:
	rm *.out


