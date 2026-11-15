/* Doubly-linked lists (Sly 1 include/dl.h; same layout in Sly 2): a list head DL and the entry DLE embedded in each
 * item at the list's ibDle offset. */
#ifndef DL_H
#define DL_H

typedef struct DLE {
    /* 0x0 */ void *next;
    /* 0x4 */ void *prev;
} DLE;   /* doubly-linked list entry */

typedef struct DL {
    /* 0x0 */ void *head;
    /* 0x4 */ void *tail;
    /* 0x8 */ int ibDle;   /* offset of the DLE in an item */
} DL;    /* list head */

#endif
