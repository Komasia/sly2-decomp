// near-miss (Claude agent): 7 diffs (+ branch offsets). Only the on-plane path differs: target computes PnodeCheck(right) as movz v1 / daddu v0,v1 / a0=v0, ours if-converts into a0 (daddu a0,0; movn a0). The qmfc2+mtc1 single asm fixed mtc1 scheduling.
typedef int qword __attribute__((mode(TI)));
class VUF {
public:
    VUF();
    qword q;
};
struct NODE { NODE *pnodeLeft; NODE *pnodeRight; qword *pplane; };
static inline NODE *PnodeCheck(NODE *p, NODE *pnodeMax)
{
    if (!(p < pnodeMax))
        p = 0;
    return p;
}
extern "C" NODE *func_00119090(NODE *pnode, NODE *pnodeMax, qword pos)
{
    while (pnode) {
        qword plane = *pnode->pplane;
        VUF d;
        VUF one;
        qword dq, oq;
        float g;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %0w"
                : "=j"(dq), "=j"(oq) : "j"(plane), "j"(pos));
        int n;
        __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(g) : "j"(dq));
        one.q = oq;
        d.q = dq;
        if (g < -1.0e-4f) {
            NODE *p = PnodeCheck(pnode->pnodeLeft, pnodeMax);
            if (!p)
                return pnode;
            pnode = p;
        } else if (g > 1.0e-4f) {
            NODE *p = PnodeCheck(pnode->pnodeRight, pnodeMax);
            if (!p)
                return 0;
            pnode = p;
        } else {
            NODE *pR = PnodeCheck(pnode->pnodeRight, pnodeMax);
            if (pR) {
                NODE *pr = func_00119090(pR, pnodeMax, pos);
                if (pr)
                    return pr;
            }
            pR = PnodeCheck(pnode->pnodeLeft, pnodeMax);
            if (!pR)
                return pnode;
            pnode = pR;
        }
    }
    return 0;
}
