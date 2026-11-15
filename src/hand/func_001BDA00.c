#include "cid.h"
#include "so.h"
typedef struct AREQ { int cb; int align; } AREQ;
/* a navigation path (cid 0x0E, NAVPATH: PATH -> XFM); the merged paths are pooled on D_003E1A40 */
typedef struct NAVPATH {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ int xE0;
    /* 0x0e4 */ int xE4;
    /* 0x0e8 */ int padE8;
    /* 0x0ec */ float *xEC;
    /* 0x0f0 */ void *xF0;
    /* 0x0f4 */ void *xF4;
    /* 0x0f8 */ char padF8[0x1C0 - 0xF8];
    /* 0x1c0 */ int x1C0;
    /* 0x1c4 */ char pad1C4[0x1D8 - 0x1C4];
    /* 0x1d8 */ int x1D8;
    /* 0x1dc */ char pad1DC[0x1E8 - 0x1DC];
    /* 0x1e8 */ int x1E8;
    /* 0x1ec */ void *x1EC;
} NAVPATH;
extern DL D_003E1A40;
NAVPATH *PloNew__F3CIDP2SW3OIDi(int a, int b, int c, int d);
void s1_memset(void *p, int c, int n) asm("memset");
void *PvAllocSwImpl__Fi(AREQ *preq);
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);

// name: SafeHouse port (PpathNewMerged)
NAVPATH *PpathNewMerged__Fv(void)
{
    NAVPATH *p;
    int i, j;
    AREQ req;
    float *pm;

    p = D_003E1A40.head;
    if (!p) {
        for (i = 0; i < 16; i++) {
            NAVPATH *q = PloNew__F3CIDP2SW3OIDi(CID_NAVPATH, 0, 0x2CD, -1);
            q->xE0 = 0;
            q->xE4 = 1;
            q->x1C0 = 1;
            pm = q->xfm.matLocal.mat[0];
            s1_memset(pm, 0, 0x40);
            pm[15] = 1.0f;
            pm[10] = 1.0f;
            pm[5] = 1.0f;
            pm[0] = 1.0f;
            req.cb = 0x80;
            req.align = 0x10;
            q->xEC = (float *)PvAllocSwImpl__Fi(&req);
            for (j = 0; j < 32; j++) q->xEC[j] = (float)j;
            req.cb = 0x80;
            req.align = 0x10;
            q->xF0 = PvAllocSwImpl__Fi(&req);
            req.cb = 0x200;
            req.align = 0x10;
            q->xF4 = PvAllocSwImpl__Fi(&req);
            req.cb = 0x1F0;
            req.align = 0x10;
            q->x1EC = PvAllocSwImpl__Fi(&req);
            ((void (*)(void *))q->xfm.lo.pvt[9].pfn)(VT_THIS(q, &q->xfm.lo.pvt[9]));
            AppendDlEntry__FP2DLPv(&D_003E1A40, q);
        }
        p = D_003E1A40.head;
    }
    RemoveDlEntry__FP2DLPv(&D_003E1A40, p);
    p->x1E8 = -1;
    ((void (*)(void *))p->xfm.lo.pvt[8].pfn)(VT_THIS(p, &p->xfm.lo.pvt[8]));
    p->x1D8 = 0;
    return p;
}
