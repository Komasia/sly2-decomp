/* func_001A3B80 (0x1A3B80): inserts a light (its slot bit) into the light set's plane tree: a sphere (pos, sRadius)
 * goes down each side its distance to the node's plane reaches; at a leaf the slot's bit is set in the leaf's 256-bit
 * light mask (+0x4564). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct NODE { qword plane; struct NODE *pnodeBelow; struct NODE *pnodeAbove; int ileafBelow; int ileafAbove; };
struct LIGHTSET { char pad[0x4564]; char *aleaf; };
void func_002564B8(void *p);
struct LEAFMASK { int a[8]; };  /* 256 light bits */
static __inline__ void SetBit(int *a, int bit) { int *pw = &a[bit / 32]; *pw |= 1 << bit; }
void func_001A3B80(struct LIGHTSET *pset, struct NODE *pnode, qword pos, float sRadius, int islot)
{
    U d, one;
    qword plane;
    float dist;
    plane = pnode->plane;
    func_002564B8(&d);
    func_002564B8(&one);
    __asm__("vmul.xyz %1, %3, %4\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddaz.x $ACC, %0, %1z\n\tvmsubw.x %1, %0, %3w\n\tqmfc2.ni %2, %1"
            : "=&j"(one.q), "=&j"(d.q), "=r"(dist) : "j"(plane), "j"(pos));
    if (dist < sRadius) {
        if (pnode->pnodeBelow)
            func_001A3B80(pset, pnode->pnodeBelow, pos, sRadius, islot);
        else
            SetBit(((struct LEAFMASK *)pset->aleaf)[pnode->ileafBelow].a, islot);
    }
    if (-sRadius < dist) {
        if (pnode->pnodeAbove)
            func_001A3B80(pset, pnode->pnodeAbove, pos, sRadius, islot);
        else
            SetBit(((struct LEAFMASK *)pset->aleaf)[pnode->ileafAbove].a, islot);
    }
}
