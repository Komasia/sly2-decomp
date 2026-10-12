struct O { char pad[0xF40]; struct O *xF40; };
struct G { int a; };
extern struct G D_003DD490;
struct O *func_001C4840(struct G *p);
int func_00132B10(struct O *p, int n);
void func_0015E938(struct G *p, int a, int b, struct O *po);
static __inline__ struct O *Get(struct O *po) { return (po && func_00132B10(po, 0x34)) ? po->xF40 : po; }
void func_001BEED8(int id)
{
    switch (id) {
    case 0x2AE:
        func_0015E938(&D_003DD490, 1, id, Get(func_001C4840(&D_003DD490)));
        break;
    case 0x2AF:
        func_0015E938(&D_003DD490, 1, 0x2AF, func_001C4840(&D_003DD490));
        break;
    default:
        func_0015E938(&D_003DD490, 0x405, id, 0);
        break;
    }
}
