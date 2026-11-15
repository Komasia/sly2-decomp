/* EnsureBasicSidebag: an object without a sidebag (its scripts' own bindings, +0x4) gets a new one (handle set by
 * 0x2580A8, then 0x258178 on it). Layout: SafeHouse port (lo.h LO psidebag orig +0x4). */
struct BASIC { int pframe; int psidebag; };
int PsidebagNew__Fv(void);
void func_002580A8(int *ph, int pv);
void func_00258178(int psidebag);
void EnsureBasicSidebag__FP5BASIC(struct BASIC *pbasic)
{
    int *ppsidebag = &pbasic->psidebag;
    if (pbasic->psidebag == 0) {
        func_002580A8(ppsidebag, PsidebagNew__Fv());
        func_00258178(pbasic->psidebag);
    }
}
