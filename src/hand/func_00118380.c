typedef struct VTE { short d; short pad; void *(*pfn)(void *, int, int); } VTE;
typedef struct ALLOC { VTE *pvt; } ALLOC;
typedef struct CBinaryInputStream CBinaryInputStream;

int U16Read(CBinaryInputStream *pbis) asm("U16Read__18CBinaryInputStream");
void Read__18CBinaryInputStreamiPv(CBinaryInputStream *pbis, int cb, void *pv);

void func_00118380(CBinaryInputStream *pbis, char **ppchz, ALLOC *palloc, int nKind)
{
    int cch = U16Read(pbis);
    char *pchz;
    if (cch == 0) {
        *ppchz = 0;
        return;
    }
    pchz = (char *)palloc->pvt[1].pfn((char *)palloc + palloc->pvt[1].d, cch + 1, nKind);
    Read__18CBinaryInputStreamiPv(pbis, cch, pchz);
    pchz[cch] = 0;
    *ppchz = pchz;
}
