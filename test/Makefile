CC = gcc
CFLAGS = -m32 -g -std=c99 -Wall -Wextra -Werror -DDEBUG
VPATH = ..

TESTS = test_string test_sprintf test_fs

.PHONY: clean test
test: $(TESTS)
	for x in $^; do ./$$x; done

test_fs: phony_block_dev.o phony_block_dev.h ../fs/block_dev.h

test_string: string.o ../string.h

test_sprintf: sprintf.o ../sprintf.h

test_%: test_%.o
	$(CC) -m32 -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(TESTS) *.o
