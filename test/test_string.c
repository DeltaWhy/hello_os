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

void test_strcat() {
    char d[] = "\0aaaaaaaaaaaaaa";
    char *s1 = "foo";
    char *s2 = "bar";
    char *res;

    res = strcat(d, s1);
    assert(res == d);
    assert(d[0] == 'f');
    assert(d[3] == '\0');

    res = strcat(d, s2);
    assert(res == d);
    assert(d[0] == 'f');
    assert(d[3] == 'b');
    assert(d[6] == '\0');
}

void test_strncat() {
    char d[] = "\0aaaaaaaaaaaaaa";
    char *s1 = "foo";
    char *s2 = "bar";
    char *res;

    res = strncat(d, s1, 2);
    assert(res == d);
    assert(d[0] == 'f');
    assert(d[1] == 'o');
    assert(d[2] == '\0');
    assert(d[3] == 'a');

    res = strncat(d, s2, 5);
    assert(res == d);
    assert(d[0] == 'f');
    assert(d[2] == 'b');
    assert(d[5] == '\0');
    assert(d[6] == 'a');
}

void test_strchr(){
    char *s = "abcdefg";

    assert(strchr(s, 'c') == s+2);
    assert(strchr(s, 'x') == NULL);
    assert(strchr(s, '\0') == s+7);
}

void test_strcmp(){
    char *s1 = "abcde\0x";
    char *s2 = "abcde\0y";
    char *s3 = "abcee";
    char *s4 = "abcce";
    char *s5 = "abc";

    assert(strcmp(s1, s2) == 0);
    assert(strcmp(s1, s3) < 0);
    assert(strcmp(s1, s4) > 0);
    assert(strcmp(s1, s5) > 0);
    assert(strcmp(s5, s1) < 0);
}

void test_strncmp(){
    char *s1 = "abcde\0x";
    char *s2 = "abcde\0y";
    char *s3 = "abcee";
    char *s4 = "abcce";
    char *s5 = "abc";

    assert(strncmp(s1, s2, 10) == 0);
    assert(strncmp(s1, s3, 4) < 0);
    assert(strncmp(s1, s4, 4) > 0);
    assert(strncmp(s1, s3, 3) == 0);
    assert(strncmp(s1, s5, 10) > 0);
    assert(strncmp(s5, s1, 10) < 0);
}

void test_strcoll(){
    char *s1 = "abcde\0x";
    char *s2 = "abcde\0y";
    char *s3 = "abcee";
    char *s4 = "abcce";
    char *s5 = "abc";

    assert(strcoll(s1, s2) == 0);
    assert(strcoll(s1, s3) < 0);
    assert(strcoll(s1, s4) > 0);
    assert(strcoll(s1, s5) > 0);
    assert(strcoll(s5, s1) < 0);
}

void test_strcpy(){
    char d[] = "aaaaaaaaaaaaaaa";
    char *s1 = "";
    char *s2 = "abcd";
    char *res;

    res = strcpy(d, s1);
    assert(res == d);
    assert(d[0] == '\0');
    assert(d[1] == 'a');

    res = strcpy(d, s2);
    assert(res == d);
    assert(d[0] == 'a');
    assert(d[3] == 'd');
    assert(d[4] == '\0');
    assert(d[5] == 'a');
}

void test_strncpy(){
    char d[] = "aaaaaaaaaaaaaaa";
    char *s1 = "";
    char *s2 = "abcd";
    char *res;

    res = strncpy(d, s1, 1);
    assert(res == d);
    assert(d[0] == '\0');
    assert(d[1] == 'a');

    res = strncpy(d, s2, 2);
    assert(res == d);
    assert(d[0] == 'a');
    assert(d[2] == 'a');

    res = strncpy(d, s2, 10);
    assert(res == d);
    assert(d[0] == 'a');
    assert(d[3] == 'd');
    assert(d[4] == '\0');
    assert(d[9] == '\0');
}

void test_strcspn(){
    char *s = "abcdefgh";
    char *r1 = "";
    char *r2 = "d";
    char *r3 = "edf";

    assert(strcspn(s, r1) == 8);
    assert(strcspn(s, r2) == 3);
    assert(strcspn(s, r3) == 3);
}

void test_strlen(){
    char *s1 = "abc\0de";
    assert(strlen(s1) == 3);
    char *s2 = "abcde";
    assert(strlen(s2) == 5);
    char *s3 = "";
    assert(strlen(s3) == 0);
}

int main() {
    test_memccpy();
    test_memchr();
    test_memcmp();
    test_memcpy();
    test_memset();
    test_strcat();
    test_strncat();
    test_strchr();
    test_strcmp();
    test_strncmp();
    test_strcoll();
    test_strcpy();
    test_strncpy();
    test_strcspn();
    test_strlen();

    return 0;
}
