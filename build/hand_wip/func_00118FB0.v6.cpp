// v6 (Claude agent, lane A7, 2026-10-23): v5 plus ONE pin (oq in vf2) -> aligned 5. Left: mtc1/sqc2 order after the qmfc2 and the v1->v0 copy of p before the left-branch bnel.
// v5 (Claude agent, 2026-10-23): aligned 13 (v4 is 10) but positional 19 vs 26: an alternative base. plane as a plain qword loaded with an lqc2 asm (spilled by gcc to 0x30 with sqc2, pos at 0x20, same as the target) plus the dot output tied to plane, and a qmfc2 "=r"(float) asm, which gives the target sqc2 d store. Left: plane reload/dq vf2 and oq vf1 (target vf1/vf2: 7 instrs), mtc1/sqc2 order, and the v1->v0 p copy before the bnel.
typedef int qword __attribute__((mode(TI)));
union VUF { qword q; float f[4]; };
struct NODE { NODE *pnodeLeft; NODE *pnodeRight; qword *pplane; };
extern "C" void *func_002564B8(void *p);
extern "C" NODE *func_00118FB0(NODE *pnode, NODE *pnodeMax, qword pos)
{
    NODE *p;
    VUF d;
    VUF one;
    if (!pnode)
        return 0;
    VUF *pone = &one;
loop:
    {
        qword plane;
        __asm__("lqc2 %0, %1" : "=j"(plane) : "m"(*pnode->pplane));
        qword dq;
        register qword oq __asm__("vf2"); /* pin: the target allocates the one-vector to vf2 (the dot result then gets vf1) */
        float g;
        func_002564B8(&d);
        func_002564B8(pone);
        __asm__("vmul.xyz %0, %0, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %0w"
                : "=j"(dq), "=j"(oq) : "0"(plane), "j"(pos));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(dq));
        one.q = oq;
        d.q = dq;
        if (g < 1.0e-4f) {
            p = pnode->pnodeLeft;
            if (!(p < pnodeMax))
                p = 0;
            if (!p)
                return pnode;
            pnode = p;
            goto loop;
        } else {
            p = pnode->pnodeRight;
            pnode = 0;
            if (p < pnodeMax)
                pnode = p;
        }
    }
    if (pnode) goto loop;
    return 0;
}
