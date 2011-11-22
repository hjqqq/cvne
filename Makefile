CC = clang
NAME = cvne
CFLAGS = -g -O0 -Wall -Werror -ansi -pedantic -march=native
LDFLAGS = -lm -lallegro -lallegro_image
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
	rm *.o $(NAME)

test:
	make
	./$(NAME)

