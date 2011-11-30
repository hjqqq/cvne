C_INCLUDE_PATH=include
CPATH=include
CC = clang
NAME = cvne
CFLAGS = -g -O0 -Wall -Werror -ansi -pedantic -march=native 
LDFLAGS = -Llib -lm -lallegro -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf -lallegro_font -lallegro_ttf 
objects := $(patsubst %.c,%.o,$(wildcard *.c))

$(NAME) : $(objects)
	$(CC) $(LDFLAGS) *.o -o $(NAME)

%.o : %.c %.h
	$(CC) $(CFLAGS) $< -c

main.o: main.c
	$(CC) $(CFLAGS) $< -c

archive :
	tar -jcvf ../$(NAME).tar.bz2 ../$(NAME)

sky :
	ompload ../$(NAME).tar.bz2

clean:
	rm -f *.o $(NAME)

test:
	make
	./$(NAME)

debug:
	gdb -ex run --batch ./$(NAME) -ex bt

push:
	make clean
	git add -A
	git commit -am '.'
	git push

