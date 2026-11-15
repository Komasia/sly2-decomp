/* SetCtrlPos: the position controller's resting value moves to pos; when the controller drives its record and
 * the value really changed, the record's segment value (+0xC0) follows and the record is held in its mode.
 * Layout: SafeHouse port (xf.h CTRLPOS, lo.h XF). */
typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
int FFloatsNear(float a, float b, float eps) asm("FFloatsNear__Ffff");
void HoldXfMode(void *palo, void *pxf);
struct XF { char pad[0x90]; void *pctrlFirst; char pad2[0xC0 - 0x94]; qword pos0; };   /* field: SafeHouse port */
struct CTRLPOS { int kind; void *palo; struct XF *pxf; int prio; int pad[4]; qword pos; };   /* field: SafeHouse port */
extern qword D_002A2DD0;   /* the zero vector */
static __inline__ int FVecsNear(qword a, qword b)
{
    return FFloatsNear(GetX(a), GetX(b), 1e-4f) && FFloatsNear(GetY(a), GetY(b), 1e-4f) &&
           FFloatsNear(GetZ(a), GetZ(b), 1e-4f);
}
// name: SafeHouse port (SetCtrlPos)
void SetCtrlPos__FP7CTRLPOSG9VU_VECTOR(struct CTRLPOS *pctrl, qword pos)
{
    qword dpos;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(dpos) : "j"(pos), "j"(pctrl->pos));
    pctrl->pos = pos;
    if (pctrl->pxf->pctrlFirst == pctrl && !FVecsNear(D_002A2DD0, dpos)) {
        pctrl->pxf->pos0 = pos;
        HoldXfMode(pctrl->palo, pctrl->pxf);
    }
}
