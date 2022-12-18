WIDTH ?= 40
HEIGHT ?= 30
CC ?= gcc
SDL_CFLAGS = -Wall -Wextra -std=c99 $(shell pkg-config --cflags sdl2)
SDL_LDFLAGS = $(shell pkg-config --libs sdl2)
CFLAGS = -Wall -Wextra -std=c99 -g3
SANDWICH_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
SRCS = \
	src/world.c \
	src/queue.c \
	src/rule.c

all: project sdl

project: $(SRCS) src/main.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) $(SRCS) src/main.c -o project

test: tst/test.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) $(SRCS) tst/test.c -o test_project

sdl: sdl_dir/sdl.c
	$(CC) $(SDL_CFLAGS) sdl_dir/sdl.c $(SDL_LDFLAGS) -o sdl

clean:
	rm -f project test_project sdl *~ *.o
