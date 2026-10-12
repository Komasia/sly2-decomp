typedef struct ALLOC ALLOC;
typedef struct CBinaryInputStream CBinaryInputStream;
typedef struct HEAPHOLDER { ALLOC *palloc; } HEAPHOLDER;
typedef struct X { HEAPHOLDER *pheap; } X;

void func_00118380(CBinaryInputStream *pbis, char **ppchz, ALLOC *palloc, int nKind);

void func_00119C08(X *px, char **ppchz, CBinaryInputStream *pbis)
{
    func_00118380(pbis, ppchz, px->pheap->palloc, 7);
}
