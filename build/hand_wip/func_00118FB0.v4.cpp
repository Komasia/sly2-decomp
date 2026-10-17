// v4 (Claude agent): aligned 10 (v3: 12). Goto loop (target has no loop-align nop and no hoisted 1e-4), d/one as function-scope unions with explicit ctor calls and VUF *pone = &one after the null check (gives s2), union plane local, mtc1-from-qword, "if (!p) return pnode; pnode = p; goto loop". Left: plane is a memory local (lq/sq GPR at 0x20; target spilled VF pseudo lqc2/sqc2 at 0x30, pos at 0x20), and the target copies p v1->v0 before the bnel.
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
        VUF plane = *(VUF *)pnode->pplane;
        qword dq, oq;
        float g;
        func_002564B8(&d);
        func_002564B8(pone);
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %0w"
                : "=j"(dq), "=j"(oq) : "j"(plane.q), "j"(pos));
        __asm__("mtc1 %1, %0" : "=f"(g) : "r"(dq));
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
