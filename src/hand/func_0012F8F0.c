/* PostAsegLoad: PostLoLoad, then an ASEG with apply parameters (+0xB0, EOPID 107) queues ApplyAsegParams as a
 * deferred call (D_002A46C8: its pointer-to-function). Layout: SafeHouse port (sm.h ASEG). */
typedef struct PFN8 { int a, b; } PFN8;   /* a pointer to function, 8 bytes */
extern PFN8 D_002A46C8;                     /* ApplyAsegParams */
extern char g_sw[];
void PostLoLoad__FP2LO(void *plo);
void PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(void *psw, void *pv, PFN8 pfn, int n);
typedef struct ASEG { char pad[0xB0]; int papply; } ASEG;   /* field: SafeHouse port (fApplyParams) */
// name: SafeHouse port (PostAsegLoad)
void PostAsegLoad__FP4ASEG(ASEG *paseg)
{
    PostLoLoad__FP2LO(paseg);
    if (paseg->papply)
        PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(g_sw, paseg, D_002A46C8, paseg->papply);
}
