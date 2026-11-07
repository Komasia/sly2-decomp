struct O { char pad[0xF40]; struct O *xF40; };
struct G;
extern struct G g_sw;
struct O *PloPlayerPo__FP2SW(struct G *p);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct O *p, int n);
struct O*PloFindSwNearest__FP2LO3OIDii(struct G *p, int a, int b, struct O *po);
static __inline__ struct O *Get(struct O *po) { return (po && FIsBasicDerivedFrom__FP5BASIC3CID(po, 0x34)) ? po->xF40 : po; }
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char O_xF40_Offset[FIELD_OFFSET(struct O,xF40)==3904?1:-1];
typedef char Size_0[sizeof(struct O)==3908?1:-1];
typedef char Size_1[sizeof(unsigned int)==4?1:-1];
typedef char Size_2[sizeof(int)==4?1:-1];
typedef char Size_3[sizeof(void*)==4?1:-1];
// name: SafeHouse port (PvRtgtOwnerOfId)
void PvRtgtOwnerOfId__Fi(int id)
{
    switch (id) {
    case 0x2AE:{
        struct O*object=Get(PloPlayerPo__FP2SW(&g_sw));
        (void)PloFindSwNearest__FP2LO3OIDii(&g_sw,1,id,object);
        break;
    }
    case 0x2AF:
        (void)PloFindSwNearest__FP2LO3OIDii(&g_sw, 1, 0x2AF, PloPlayerPo__FP2SW(&g_sw));
        break;
    default:
        (void)PloFindSwNearest__FP2LO3OIDii(&g_sw, 0x405, id, 0);
        break;
    }
}
