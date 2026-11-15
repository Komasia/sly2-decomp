/* Sly 1 memcard.h: memory card worker thread state (partial; Sly 2's MC +0xFD5C, include/h5_mc.h). The thread runs
 * one MC method (a pointer to member function) and keeps its result. */
#ifndef MEMCARD_H
#define MEMCARD_H

typedef struct MEMCARD {
    /* 0x00 */ int semaId;
    /* 0x04 */ int threadId;     /* -1 when there is no worker thread */
    /* 0x08 */ int field_0x08;   /* the method to run (a PMF: delta / index, function); Sly 1 names: CreateMemcardThread's two arguments */
    /* 0x0c */ int field_0x0c;
    /* 0x10 */ int nResult;      /* the method's result (0x20 after InitMemcard, 0x21 while it runs) */
} MEMCARD;

#endif
