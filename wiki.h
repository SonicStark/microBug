#ifndef HEAD_WIKI_H
#define HEAD_WIKI_H

#ifdef __cplusplus
extern "C"{
#endif

int wiki_UseAfterFree();
int wiki_HeapOutOfBounds();
int wiki_StackOutOfBounds();
int wiki_GlobalOutOfBounds();
int wiki_UseAfterReturn();
int wiki_UseAfterScope();
int wiki_LeakSanitizer();

#ifdef __cplusplus
}
#endif

#endif