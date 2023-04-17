#include <stdlib.h>

#include "wiki.h"

/* https://github.com/google/sanitizers/wiki/AddressSanitizerExampleUseAfterFree */
int wiki_UseAfterFree(){
    int *array = new int[100];
    delete [] array;
    return array[1];  // BOOM
}

/* https://github.com/google/sanitizers/wiki/AddressSanitizerExampleHeapOutOfBounds */
int wiki_HeapOutOfBounds(){
    int *array = new int[100];
    array[0] = 0;
    int res = array[1 + 100];  // BOOM
    delete [] array;
    return res;
}

/* https://github.com/google/sanitizers/wiki/AddressSanitizerExampleStackOutOfBounds */
int wiki_StackOutOfBounds(){
    int stack_array[100];
    stack_array[1] = 0;
    return stack_array[1 + 100];  // BOOM
}

/* https://github.com/google/sanitizers/wiki/AddressSanitizerExampleGlobalOutOfBounds */
volatile int global_array[100] = {-1};
int wiki_GlobalOutOfBounds(){
    return global_array[1 + 100];  // BOOM
}

/* https://github.com/google/sanitizers/wiki/AddressSanitizerExampleUseAfterReturn
   > By default, AddressSanitizer does not try to detect stack-use-after-return bugs.
   > It may still find such bugs occasionally and report them as a hard-to-explain stack-buffer-overflow.
   > You need to run the test with ASAN_OPTIONS=detect_stack_use_after_return=1
 */
volatile int *ptr;
__attribute__((noinline)) void FunctionThatEscapesLocalObject() {
    int local[100];
    ptr = &local[0];
}
int wiki_UseAfterReturn() {
    FunctionThatEscapesLocalObject();
    return ptr[1];
}

/* https://github.com/google/sanitizers/wiki/AddressSanitizerExampleUseAfterScope */
volatile int *p = 0;
int wiki_UseAfterScope() {
    {
        int x = 0;
        p = &x;
    }
    *p = 5;
    return 0;
}

/* https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer */
void *pp;
int wiki_LeakSanitizer() {
    pp = malloc(7);
    pp = 0; // The memory is leaked here.
    return 0;
}