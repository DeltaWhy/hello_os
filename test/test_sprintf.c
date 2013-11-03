#include <assert.h>
#include "sprintf.h"
#include "string.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

void test_basic() {
    char buf[1024];
    char *str = "hello world";
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, str) == (int)strlen(str));
    assert(strcmp(buf, str) == 0);
    memset(buf, 'a', sizeof(buf));
    assert(snprintf(buf, 6, str) == (int)strlen(str));
    assert(strcmp(buf, "hello") == 0);
}

void test_char() {
    char buf[1024];
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%c", (int)'c') == 1);
    assert(strcmp(buf, "c") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%4c", (int)'c') == 4);
    assert(strcmp(buf, "   c") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%-4c", (int)'c') == 4);
    assert(strcmp(buf, "c   ") == 0);
}

void test_string() {
    char buf[1024];
    char *fmt = "hello %s world";
    char *str = "there";
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, fmt, str) == (int)strlen("hello there world"));
    assert(strcmp(buf, "hello there world") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(snprintf(buf, 8, fmt, str) == (int)strlen("hello there world"));
    assert(strcmp(buf, "hello t") == 0);

    // test field width
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%8s", str) == 8);
    assert(strcmp(buf, "   there") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%-8s", str) == 8);
    assert(strcmp(buf, "there   ") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%4s", str) == 5);
    assert(strcmp(buf, "there") == 0);

    // test precision
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%.8s", str) == 5);
    assert(strcmp(buf, "there") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%.4s", str) == 4);
    assert(strcmp(buf, "ther") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%6.4s", str) == 6);
    assert(strcmp(buf, "  ther") == 0);
}

void test_percent() {
    char buf[1024];
    char *fmt = "%%";
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, fmt) == 1);
    assert(strcmp(buf, "%") == 0);
}

void test_signed() {
    char buf[1024];
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%d", -16) == (int)strlen("-16"));
    assert(strcmp(buf, "-16") == 0);

    // test precision
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%d", 0) == (int)strlen("0"));
    assert(strcmp(buf, "0") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%.d", 0) == 0);
    assert(strcmp(buf, "") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%.3d", 0) == (int)strlen("000"));
    assert(strcmp(buf, "000") == 0);

    // test width
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%4d", 0) == (int)strlen("   0"));
    assert(strcmp(buf, "   0") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%-4d", 0) == (int)strlen("0   "));
    assert(strcmp(buf, "0   ") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%4d", 12345) == (int)strlen("12345"));
    assert(strcmp(buf, "12345") == 0);

    // test flags
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%04d", 0) == (int)strlen("0000"));
    assert(strcmp(buf, "0000") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%04d", 0) == (int)strlen("0000"));
    assert(strcmp(buf, "0000") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "% d", 0) == (int)strlen(" 0"));
    assert(strcmp(buf, " 0") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%+d", 0) == (int)strlen("+0"));
    assert(strcmp(buf, "+0") == 0);

    // test length
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%hhd", (char)-1) == (int)strlen("-1"));
    assert(strcmp(buf, "-1") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%hd", (short)-1) == (int)strlen("-1"));
    assert(strcmp(buf, "-1") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%ld", (long)-1) == (int)strlen("-1"));
    assert(strcmp(buf, "-1") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%lld", (long long)-1) == (int)strlen("-1"));
    assert(strcmp(buf, "-1") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%jd", (intmax_t)-1) == (int)strlen("-1"));
    assert(strcmp(buf, "-1") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%zd", (size_t)1) == (int)strlen("1"));
    assert(strcmp(buf, "1") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%td", (ptrdiff_t)-1) == (int)strlen("-1"));
    assert(strcmp(buf, "-1") == 0);
}

void test_unsigned() {
    char buf[1024];
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%u", 16) == (int)strlen("16"));
    assert(strcmp(buf, "16") == 0);

    // TODO - figure out how to test unsigned-ness

    // test precision
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%u", 0) == (int)strlen("0"));
    assert(strcmp(buf, "0") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%.u", 0) == 0);
    assert(strcmp(buf, "") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%.3u", 0) == (int)strlen("000"));
    assert(strcmp(buf, "000") == 0);

    // test width
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%4u", 0) == (int)strlen("   0"));
    assert(strcmp(buf, "   0") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%-4u", 0) == (int)strlen("0   "));
    assert(strcmp(buf, "0   ") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%4u", 12345) == (int)strlen("12345"));
    assert(strcmp(buf, "12345") == 0);
}

void test_octhex() {
    char buf[1024];
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%o", 01234) == (int)strlen("1234"));
    assert(strcmp(buf, "1234") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%x", 0xabcd) == (int)strlen("abcd"));
    assert(strcmp(buf, "abcd") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%X", 0xabcd) == (int)strlen("ABCD"));
    assert(strcmp(buf, "ABCD") == 0);

    // test alternate
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%#o", 01234) == (int)strlen("01234"));
    assert(strcmp(buf, "01234") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%#o", 0) == (int)strlen("0"));
    assert(strcmp(buf, "0") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%#x", 0xabcd) == (int)strlen("0xabcd"));
    assert(strcmp(buf, "0xabcd") == 0);
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%#X", 0xabcd) == (int)strlen("0XABCD"));
    assert(strcmp(buf, "0XABCD") == 0);
} 

void test_ptr() {
    char buf[1024];
    void *p = NULL;
    memset(buf, 'a', sizeof(buf));
    assert(sprintf(buf, "%p", p) == (int)strlen("0x0"));
    assert(strcmp(buf, "0x0") == 0);
}

void test_n() {
    char buf[1024];
    int i = 0;
    sprintf(buf, "hello world%n", &i);
    assert(i == (int)strlen("hello world"));
    i = 0;
    sprintf(buf, "hello %s%n", "there", &i);
    assert(i == (int)strlen("hello there"));
    i = 0;
    sprintf(buf, "%d%n%d", 123, &i, 456);
    assert(i == 3);
}

int main() {
    test_basic();
    test_char();
    test_string();
    test_percent();
    test_signed();
    test_unsigned();
    test_octhex();
    test_ptr();
    test_n();

    return 0;
}
