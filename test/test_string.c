#include <stdio.h>
#include <assert.h>
#include "../string.h"

void test_memccpy() {
    char *src = "abcdefg";
    char dest[] = "aaaaaaa";
    void *res;
    res = memccpy(dest, src, 'c', 2);
    assert(res == NULL);
    assert(dest[2] == 'a');

    res = memccpy(dest, src, 'c', 6);
    assert(res == dest+3);
    assert(dest[2] == 'c');
    assert(dest[3] == 'a');

    res = memccpy(dest, src, 'x', 6);
    assert(res == NULL);
    assert(dest[5] == 'f');
    assert(dest[6] == 'a');
}

void test_memchr() {
    char *s = "abcdef";
    assert(memchr(s, 'c', 3) == s+2);
    assert(memchr(s, 'c', 2) == NULL);
}

void test_memcmp() {
    char *s1 = "abcdef";
    char *s2 = "abceef";
    char *s3 = "abccef";

    assert(memcmp(s1, s2, 0) == 0);
    assert(memcmp(s1, s2, 3) == 0);
    assert(memcmp(s1, s2, 4) < 0);
    assert(memcmp(s1, s3, 4) > 0);
}

void test_memcpy() {
    char *src = "bcdefg";
    char dest[] = "\0\0\0\0\0\0";
    void *res;

    res = memcpy(dest, src, 0);
    assert(res == dest);
    assert(dest[0] == '\0');

    res = memcpy(dest, src, 1);
    assert(res == dest);
    assert(dest[0] == 'b');
    assert(dest[1] == '\0');

    res = memcpy(dest, src, 6);
    assert(res == dest);
    assert(dest[5] == 'g');
    assert(dest[6] == '\0');
}

void test_memset() {
    char s[] = "aaaaaa";
    void *res;

    res = memset(s, 'b', 0);
    assert(res == s);
    assert(s[0] == 'a');

    res = memset(s, 'b', 3);
    assert(res == s);
    assert(s[2] == 'b');
    assert(s[3] == 'a');
}

int main() {
    test_memccpy();
    test_memchr();
    test_memcmp();
    test_memcpy();
    test_memset();
    return 0;
}
