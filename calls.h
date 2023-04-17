#ifndef HEAD_CALLS_H
#define HEAD_CALLS_H

#ifdef __cplusplus
extern "C"{
#endif

void call_sprintf (char* pBuf);
void call_strftime(char* pBuf);
void call_assign  (char* pBuf, unsigned int wlen);
void call_memset  (char* pBuf, unsigned int wlen);
void call_memcpy  (char* pBuf, unsigned int wlen);

#ifdef __cplusplus
}
#endif

#endif