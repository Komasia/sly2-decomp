/* BindHackSegs: a hack object's state segments ({oid, ASEG, SM, grfapl}, 0x10 bytes each) get their objects found
 * from the object (PloFindSwNearest kind 4): an ASEG (cid 0x6D) or an SM (cid 0x6F). Source: SafeHouse port
 * (hack.cpp HACKSEG). */
struct LO;
struct HACKSEG {
    /* 0x0 */ int oid;           /* field: SafeHouse port */
    /* 0x4 */ struct LO *paseg;  /* field: SafeHouse port */
    /* 0x8 */ struct LO *psm;    /* field: SafeHouse port */
    /* 0xc */ int grfapl;        /* field: SafeHouse port */
};
extern char g_sw[];
struct LO *PloFindSwNearest__FP2LO3OIDii(void *psw, int kind, int oid, struct LO *plo);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);

// name: SafeHouse port (BindHackSegs)
void BindHackSegs__FP2LOP6HACKSOPv(struct LO *plo, int cseg, struct HACKSEG *aseg)
{
    int i;
    for (i = 0; i < cseg; i++) {
        struct HACKSEG *pseg = &aseg[i];
        if (pseg->oid != -1) {
            struct LO *ploFound = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, pseg->oid, plo);
            if (ploFound != 0) {
                if (FIsBasicDerivedFrom__FP5BASIC3CID(ploFound, 0x6D))
                    pseg->paseg = ploFound;
                else if (FIsBasicDerivedFrom__FP5BASIC3CID(ploFound, 0x6F))
                    pseg->psm = ploFound;
            }
        }
    }
}
