/* class: JOBHELP, the Job Help HUD widget D_003DA3C0 (SafeHouse shop.cpp): its constructor - the base HUD widget,
 * its vtable D_002D8468, its screen object 0x4E0, then its state reset (func_001DCD08). */
#define OID_SCREENJOBHELP 0x4E0
extern char D_002D8468[];
struct JOBHELP {
    /* 0x00 */ int a, b, c;
    /* 0x0c */ void *pvt;
    /* 0x10 */ char pad10[0x10];
    /* 0x20 */ int oidScreen;
};
struct JOBHELP *func_001DA728(struct JOBHELP *pjobhelp);   /* the base constructor */
void func_001DCD08(struct JOBHELP *pjobhelp);

struct JOBHELP *func_001DCC58(struct JOBHELP *pjobhelp)
{
    func_001DA728(pjobhelp);
    pjobhelp->pvt = D_002D8468;
    pjobhelp->oidScreen = OID_SCREENJOBHELP;
    func_001DCD08(pjobhelp);
    return pjobhelp;
}
