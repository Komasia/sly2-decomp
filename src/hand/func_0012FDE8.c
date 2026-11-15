/* The ASEG's EOPID 107 option (SafeHouse sm.h: 0x12FDE8): its apply parameters {t, svt, grfapl} on the world heap
 * (+0xB0), applied by PostAsegLoad. */
typedef struct AREQ { int cb; int cbAlign; } AREQ;
typedef struct APPLY { float t; float svt; int grfapl; } APPLY;
typedef struct ASEG { char pad[0xB0]; APPLY *papply; } ASEG;
APPLY *PvAllocSwImpl__Fi(AREQ *preq);
void func_0012FDE8(ASEG *paseg, int grfapl, float t, float svt)
{
    AREQ req;
    APPLY *papply;
    req.cb = 0xC;
    req.cbAlign = 0x10;
    papply = PvAllocSwImpl__Fi(&req);
    paseg->papply = papply;
    papply->t = t;
    papply->svt = svt;
    papply->grfapl = grfapl;
}
