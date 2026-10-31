/* STACKSCOPE: scoped use of the stack heap (Sly 1 memory.c InitStackImpl / FreeStackImpl, which Sly 1 code called in
 * pairs). Constructing one opens a stack frame, destroying it pops it. The class name comes from Lilly's Sly 2 port;
 * the constructor / destructor are 0x1AE478 / 0x1AE4A0. C++ only. */
#ifndef STACKSCOPE_H
#define STACKSCOPE_H

void InitStackImpl();
void FreeStackImpl();

struct STACKSCOPE {
    STACKSCOPE();
    ~STACKSCOPE();
};

#endif
