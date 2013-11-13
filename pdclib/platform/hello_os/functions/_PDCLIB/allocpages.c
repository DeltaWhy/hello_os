/* $Id$ */

/* _PDCLIB_allocpages( int const )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is a stub implementation of _PDCLIB_allocpages
*/

#include <stdint.h>
#include <stddef.h>
#include <_PDCLIB_glue.h>
#include <errno.h>
#include "../mem/sbrk.h"

void * _PDCLIB_allocpages( size_t n )
{
    void *res = sbrk(n*_PDCLIB_MALLOC_PAGESIZE);
    if (res == (void *)-1) {
        return NULL;
    } else {
        return res;
    }
}

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    return TEST_RESULTS;
}

#endif
