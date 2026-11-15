/* Remove an object's entry from the render sphere tree (the inverse of func_001D6378): the entry's kind becomes
 * free (0xF = -1), the object forgets it, and update flag 0x80 is cleared (in the update record when +0x40 holds a
 * pointer, else in the flags word itself). */
#define GRFUPD_RENDER 0x80

struct RENDER {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ unsigned long grf;     /* bits 32..35: kind (see func_001D6508) */
};
struct LO_RENDER {
    /* 0x000 */ char pad0[0x40];
    /* 0x040 */ int grfupd;           /* update flags, or (bit 0 clear) a pointer to them */
    /* 0x044 */ char pad44[0x140 - 0x44];
    /* 0x140 */ int irender;
    /* 0x144 */ struct RENDER *prender;
};

void func_001D6310(struct LO_RENDER *plo)
{
    if (plo->prender) {
        int grfupd;
        plo->prender->grf |= 0xF00000000UL;   /* kind = -1: free */
        plo->irender = -1;
        plo->prender = 0;
        grfupd = plo->grfupd;
        if ((grfupd ^ 1) & 1)
            *(int *)grfupd &= ~GRFUPD_RENDER;
        else
            plo->grfupd = grfupd & ~GRFUPD_RENDER;
    }
}
