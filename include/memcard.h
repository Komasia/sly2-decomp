/* Sly 1 memcard.h: memory card worker thread state (partial). */
#ifndef MEMCARD_H
#define MEMCARD_H

typedef struct MEMCARD {
    /* 0x00 */ int semaId;
    /* 0x04 */ int threadId;     /* -1 when there is no worker thread */
} MEMCARD;

#endif
