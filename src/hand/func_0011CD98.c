/* class: SLOTHEAP (slotheap.h; 0x11CCC0 allocates): a slot freed - pushed on the free list, the live count lowered. */
typedef struct SLOTHEAP {
    /* 0x00 */ int cb;
    /* 0x04 */ int cslot;
    /* 0x08 */ int cbAlign;
    /* 0x0c */ void *pvFirst;   /* the free list */
    /* 0x10 */ int cAlloc;      /* slots in use */
} SLOTHEAP;

void func_0011CD98(SLOTHEAP *pslotheap, void **pv)
{
    pslotheap->cAlloc--;
    *pv = pslotheap->pvFirst;
    pslotheap->pvFirst = pv;
}
