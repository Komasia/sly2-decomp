/* SetCtrlSourceOffset: the source controller's offset becomes ofsNew; when it drives its record and the offset
 * really changed, both segment end values (+0xC0, +0xE0) move by the change and the record is held in its mode.
 * Layout: SafeHouse port (xf.h CTRLSOURCE, lo.h XF). */
// v3 (Claude agent): MATCHES, but only with an unused duplicate "j"(dofs) input on the first vadd (emits nothing).
// The extra VF-class use makes regclass put dofs in the VU register class, so it is spilled to 0(sp) across the calls
// like the target. Kept here pending a policy decision / a natural source form giving dofs one more "j" use.
// wip (Claude agent): sibling of matched SetCtrlPos__FP7CTRLPOSG9VU_VECTOR. ~60 diff: target spills dofs (vsub result) to the stack
// (sqc2 vf3,0(sp); lq before prot3w/pextuw; lqc2 vf2 for the vadds) and uses only s0-s2; ours keeps dofs in $s1.
typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
int FFloatsNear(float a, float b, float eps) asm("FFloatsNear__Ffff");
void HoldXfMode(void *palo, void *pxf);
struct XF { char pad[0x90]; void *pctrlFirst; char pad2[0xC0 - 0x94]; qword pos0; qword vel0; qword pos1; };
struct CTRLSOURCE { int kind; void *palo; struct XF *pxf; int prio; int pad[4]; qword ofs; };
extern qword D_002A2DD0;
static __inline__ int FVecsNear(qword a, qword b)
{
    return FFloatsNear(GetX(a), GetX(b), 1e-4f) && FFloatsNear(GetY(a), GetY(b), 1e-4f) &&
           FFloatsNear(GetZ(a), GetZ(b), 1e-4f);
}
// name: SafeHouse port (SetCtrlSourceOffset)
void SetCtrlSourceOffset__FP10CTRLSOURCEG9VU_VECTOR(struct CTRLSOURCE *pctrl, qword ofsNew)
{
    qword dofs;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(dofs) : "j"(ofsNew), "j"(pctrl->ofs));
    pctrl->ofs = ofsNew;
    if (pctrl->pxf->pctrlFirst == pctrl && !FVecsNear(D_002A2DD0, dofs)) {
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(pctrl->pxf->pos0) : "j"(pctrl->pxf->pos0), "j"(dofs), "j"(dofs));
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(pctrl->pxf->pos1) : "j"(pctrl->pxf->pos1), "j"(dofs));
        HoldXfMode(pctrl->palo, pctrl->pxf);
    }
}
