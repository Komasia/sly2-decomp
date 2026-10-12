typedef int qword __attribute__((mode(TI)));
class VUF {
public:
    VUF();
    qword q;
};
struct NODE { NODE *pnodeLeft; NODE *pnodeRight; qword *pplane; };
extern "C" NODE *func_00118FB0(NODE *pnode, NODE *pnodeMax, qword pos)
{
    NODE *p;
    if (!pnode)
        return 0;
    do {
        qword plane = *pnode->pplane;
        VUF d;
        VUF one;
        qword dq, oq;
        float g;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %0w"
                : "=j"(dq), "=j"(oq) : "j"(plane), "j"(pos));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(dq));
        one.q = oq;
        d.q = dq;
        if (g < 1.0e-4f) {
            p = pnode->pnodeLeft;
            if (!(p < pnodeMax))
                p = 0;
            if (p) {
                pnode = p;
                continue;
            }
            return pnode;
        } else {
            p = pnode->pnodeRight;
            pnode = 0;
            if (p < pnodeMax)
                pnode = p;
        }
    } while (pnode);
    return 0;
}
