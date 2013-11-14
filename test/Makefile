CC = gcc
CFLAGS = -m32 -g -std=c99 -Wall -Wextra -Werror
VPATH = ..

TESTS = test_string test_sprintf

test_string: string.o ../string.h

test_sprintf: sprintf.o ../sprintf.h

test_%: test_%.o
	$(CC) -m32 -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean test
test: $(TESTS)
	for x in $^; do ./$$x; done

clean:
	rm -f $(TESTS) *.o
