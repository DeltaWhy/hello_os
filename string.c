#include "string.h"

/**
 * Copies no more than n bytes from src to dest, stopping when the character c
 * is found
 * @return A pointer to the next character in dest after c, or NULL if c was not
 * found in the first n characters of src.
 */
void *memccpy(void *dest, const void *src, int c, size_t n) {
    const unsigned char *s = (const unsigned char *)src;
    unsigned char *d = (unsigned char *)dest;
    while (n != 0 && *s != (unsigned char)c) {
        *d = *s;
        d++;
        s++;
        n--;
    }
    if (n != 0 && *s == (unsigned char)c) {
        *d = *s;
        return d+1;
    } else {
        return NULL;
    }
}

/**
 * Scans the initial n bytes of s for the first instance of c, interpreted as
 * unsigned char.
 * @return A pointer to the matching byte or NULL
 */
void *memchr(const void *s, int c, size_t n) {
    const unsigned char *ss = (const unsigned char *)s;
    while (n != 0 && *ss != (unsigned char)c) {
        ss++;
        n--;
    }
    if (n != 0 && *ss == (unsigned char)c) {
        return (void *)ss;
    } else {
        return NULL;
    }
}

/**
 * Compares the first n bytes of s1 and s2.
 * @return An integer less than, equal to, or greater than zero if the first n
 * bytes of s1 is found, respectively, to be less than, to match, or be greater
 * than the first n bytes of s2.
 */
int memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *ss1 = (const unsigned char *)s1;
    const unsigned char *ss2 = (const unsigned char *)s2;
    while (n != 0) {
        if (*ss1 < *ss2) return -1;
        if (*ss1 > *ss2) return 1;
        ss1++;
        ss2++;
        n--;
    }
    return 0;
}

/**
 * Copies n bytes from src to dest. Memory areas must not overlap.
 * @return A pointer to dest.
 */
void *memcpy(void *dest, const void *src, size_t n) {
    const unsigned char *s = (const unsigned char *)src;
    unsigned char *d = (unsigned char *)dest;
    while (n != 0) {
        *d = *s;
        d++;
        s++;
        n--;
    }
    return dest;
}

/**
 * Copies n bytes from src to dest, memory areas may overlap.
 */
//void *memmove(void *dest, const void *src, size_t n);

/**
 * Fills the first n bytes of s with the constant byte c.
 * @return pointer to s
 */
void *memset(void *s, int c, size_t n) {
    unsigned char *ss = (unsigned char *)s;
    while (n != 0) {
        *ss = (unsigned char)c;
        ss++;
        n--;
    }
    return s;
}
