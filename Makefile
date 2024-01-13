CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb

heap: customAlloc.c
	$(CC) $(CFLAGS) -o heap customAlloc.c
