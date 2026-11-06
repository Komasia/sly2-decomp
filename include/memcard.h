/* Sly 1 memcard.h: memory card worker thread state (partial). */
#ifndef MEMCARD_H
#define MEMCARD_H

typedef struct MEMCARD {
    /* 0x00 */ int semaId;
    /* 0x04 */ int threadId;     /* -1 when there is no worker thread */
    /* 0x08 */ int field_0x08;   /* Sly 1 names: CreateMemcardThread's two arguments */
    /* 0x0c */ int field_0x0c;
    /* 0x10 */ int field_0x10;   /* 0x20 after InitMemcard / CreateMemcardThread */
} MEMCARD;

#endif
