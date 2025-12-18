NAME = raycaster

CC = gcc

CFLAGS = -Wall -Werror
CFLAGS += -g3 -fsanitize=address

SRC = main.c	\
      vec3.c	\
      ray.c		\
	  camera.c	\
	  sphere.c


INCLUDES = vec3.h	\
		   ray.h	\
		   camera.h	\
		   sphere.h

LINKER = -lm

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) $(INCLUDES) $(SRC) $(LINKER) -o $(NAME)

clean:
	rm $(NAME) || true

re:  clean all
