MAKE = make
CC = gcc
CFLAGS = -m32 -std=c99 -Wall -Wextra -Werror

TESTS = test_string

test_string: ../string.o ../string.h

test_%: test_%.o
	$(CC) -m32 -o $@ $^
	./$@
../%.o:
	@$(MAKE) -C .. $*.o
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean test
test: $(TESTS)

clean:
	-rm $(TESTS) *.o
