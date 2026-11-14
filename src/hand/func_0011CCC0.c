typedef struct MSG { int cb; int nKind; } MSG;
typedef struct POOL { int cb; int c; int nKind; void *pvFree; int cAlloc; void *pvBlock; } POOL;

void *PvAllocSwImpl__Fi(MSG *pmsg);
void *s1_memset(void *pv, int b, unsigned int cb) asm("memset");

void *func_0011CCC0(POOL *ppool)
{
    void *pv;

    if (ppool->pvFree == 0) {
        MSG msg;
        char *ab;
        int i;

        msg.cb = ppool->c * ppool->cb;
        msg.nKind = ppool->nKind;
        ab = (char *)PvAllocSwImpl__Fi(&msg);
        for (i = 1; i < ppool->c; i++) {
            *(void **)(ab + (i - 1) * ppool->cb) = ab + i * ppool->cb;
        }
        *(void **)(ab + (i - 1) * ppool->cb) = 0;
        ppool->pvFree = ab;
        ppool->pvBlock = ab;
    }

    pv = ppool->pvFree;
    ppool->pvFree = *(void **)pv;
    s1_memset(pv, 0, ppool->cb);
    ppool->cAlloc++;
    return pv;
}
