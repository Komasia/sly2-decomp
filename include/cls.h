/* Sly 2 class descriptors: one CLS per class id, a table at 0x2BAAE8 indexed by cid. Every class's virtual
 * slot 5 returns its descriptor; CLS::pfnNew is the class factory (0 for abstract classes). */
#ifndef CLS_H
#define CLS_H

typedef struct CLS {
    /* 0x00 */ struct CLS *pclsSuper;
    /* 0x04 */ int cid;
    /* 0x08 */ int cidMac;          /* ids [cid, cidMac) are this class and its descendants */
    /* 0x0c */ int cb;              /* instance size */
    /* 0x10 */ void *(*pfnNew)(void);
} CLS;

#endif
