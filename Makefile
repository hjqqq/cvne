CC = clang
NAME = cvne
CFLAGS = -g -O0 -Wall -Werror -ansi -pedantic -march=native 
LDFLAGS = -Llib -lm -lallegro -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf -lallegro_font -lallegro_ttf 
MAKEFLAGS = -j5
objects := $(patsubst %.c,%.o,$(wildcard *.c))

$(NAME) : $(objects)
	$(CC) $(LDFLAGS) *.o -o $(NAME)

%.o : %.c %.h
	$(CC) $(CFLAGS) $< -c

main.o: main.c
	$(CC) $(CFLAGS) $< -c

archive:
	make clean
	tar -jcvf ../$(NAME).tar.bz2 ../$(NAME)

sky:
	make archive
	ompload ../$(NAME).tar.bz2

clean:
	rm -f *.o $(NAME)

test:
	make clean
	make $(MAKEFLAGS)
	./$(NAME)

debug:
	make clean
	make $(MAKEFLAGS)
	gdb -ex run --batch ./$(NAME) -ex bt

push:
	make clean
	git add -A
	git commit -am '.'
	git push

