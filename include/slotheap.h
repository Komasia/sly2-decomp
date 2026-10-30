/* Sly 2 slot heap: a fixed-size pool. Every translation unit that uses CStructTypeFactory<T> gets the template
 * static CStructTypeFactory<T>::s_slotheap, constructed during static initialisation by func_0011CCA8. */
#ifndef SLOTHEAP_H
#define SLOTHEAP_H

typedef struct SLOTHEAP {
    /* 0x00 */ int cb;         /* slot size */
    /* 0x04 */ int cslot;      /* slots per block */
    /* 0x08 */ int cbAlign;
    /* 0x0c */ void *pvFirst;  /* 0 until the first allocation */
} SLOTHEAP;

/* 0x11CCA8: constructor; returns pslotheap */
SLOTHEAP *func_0011CCA8(SLOTHEAP *pslotheap, int cb, int cslot, int cbAlign);

#endif
