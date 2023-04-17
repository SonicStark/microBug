#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "calls.h"

void call_sprintf(char* pBuf)
{
#ifndef BUG_KEEP_QUIET
    printf(" => call_sprintf"); fflush(stdout);
#endif
    sprintf(pBuf, "abcdefghijklmnopqrstuvwxyz");
}

void call_strftime(char* pBuf)
{
#ifndef BUG_KEEP_QUIET
    printf(" => call_strftime"); fflush(stdout);
#endif
    time_t rawtime;
    time(&rawtime);
    struct tm *info;
    info = localtime(&rawtime); 
    strftime(pBuf, 64, "%Y%m%d%H%M%S0123456789abcdefg", info);
}

void call_assign(char* pBuf, unsigned int wlen)
{
#ifndef BUG_KEEP_QUIET
    printf(" => call_assign_L%d", wlen); fflush(stdout);
#endif
    char *p = pBuf;
    for (int i__=0; i__<wlen; i__++)
        { *p = 0x88; p++; }
}

void call_memset(char* pBuf, unsigned int wlen)
{
#ifndef BUG_KEEP_QUIET
    printf(" => call_memset_L%d", wlen); fflush(stdout);
#endif
    memset(pBuf, 0x88, wlen*sizeof(char));
}

void call_memcpy(char* pBuf, unsigned int wlen)
{
#ifndef BUG_KEEP_QUIET
    printf(" => call_memcpy_L%d", wlen); fflush(stdout);
#endif
    char *d = (char*) malloc(wlen*sizeof(char));//maybe OOM
    if (!d) { return; }
    memcpy(d, pBuf, wlen*sizeof(char));
    free(d);
}