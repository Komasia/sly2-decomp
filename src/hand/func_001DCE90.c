/* class: JOBHELP, the Job Help HUD widget (SafeHouse shop.cpp): select row irow (clamped; -1 with no rows) and clear
 * the message. */
struct JOBHELP {                      /* field: SafeHouse port (shop.cpp JOBHELP) */
    /* 0x000 */ char pad0[0x48];
    /* 0x048 */ int crow;
    /* 0x04c */ char pad4C[0x118 - 0x4C];
    /* 0x118 */ int isel;
};
void func_001DA9E8(struct JOBHELP *pjobhelp);   /* no message */
static inline int Clamp(int n, int nMin, int nMax)
{
    if (n < nMin) return nMin;
    if (n > nMax) return nMax;
    return n;
}

void func_001DCE90(struct JOBHELP *pjobhelp, int irow)
{
    int crow = pjobhelp->crow;
    int isel;
    if (crow == 0)
        isel = -1;
    else
        isel = Clamp(irow, 0, crow - 1);
    pjobhelp->isel = isel;
    func_001DA9E8(pjobhelp);
}
