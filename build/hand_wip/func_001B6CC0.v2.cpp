/* (Claude agent) v2 (.cpp, 10/57): neg-broadcast union store emitted last via one shared U u (factor store, then u.q = kn at the end) -> target's final sqc2 vf4/vf5 order; volatile lw ReadFactor placed after Negative fixes the factor-word load position. Remaining: lui/addiu of D_002A2DC0 after the barrier, mfc1 -1 into v0 vs a0, sqc2 vf4 vs final vmulx order. */
typedef int qword __attribute__((mode(TI)));
struct VT { short d; short pad; void *pfn; };
struct O { char pad[0x80]; qword v80; };
struct P {
    char pad0[0xC]; struct VT *vt; char pad1[0xE8 - 0x10]; struct O *pE8; char pad1b[0x190 - 0xEC]; qword v190;
    char pad4[0x13D8 - 0x1A0]; int x13D8;
};
extern "C" qword D_002A2DC0;
enum { FACTOR_ADDRESS = 0x002C09A4 };
extern "C" void func_001FAC30(struct P *p, qword v);
typedef union { qword q; float f[4]; } U;
static inline qword Scale(qword a, float g) { U u; qword k, r; __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(g)); u.q = k; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(u.q)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Negative(qword a, qword *pk) {
    register qword k __asm__("vf5"); register qword r __asm__("vf1");
    __asm__("qmtc2.ni %1,%0":"=j"(k):"r"(-1.0f));
    __asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(k));
    *pk = k;
    return r;
}
static inline qword Factor(qword a,int bits,U *pu) {
    U &u=*pu; register qword k __asm__("vf4"); register qword r __asm__("vf3");
    __asm__("qmtc2.ni %1,%0":"=j"(k):"r"(bits));
    u.q=k;
    __asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(u.q));
    return r;
}
static inline qword Projection(qword a,qword b) {
    register qword r __asm__("vf3"),one __asm__("vf4");
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvmulx.xyzw %0,%3,%0x":"=&j"(r),"=&j"(one):"j"(a),"j"(b));
    return r;
}
static inline int ReadFactor(void) {
    register int *page __asm__("$2") = (int *)(FACTOR_ADDRESS & ~0xFFFF);
    register int bits __asm__("$2");
    __asm__ __volatile__("lw %0,%1":"=r"(bits):"m"(page[(FACTOR_ADDRESS & 0xFFFF)/sizeof(int)]));
    return bits;
}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((struct t*)0x10000)->m)-0x10000)
typedef char VT_d_Offset[FIELD_OFFSET(VT,d)==0?1:-1];
typedef char VT_pfn_Offset[FIELD_OFFSET(VT,pfn)==4?1:-1];
typedef char O_v80_Offset[FIELD_OFFSET(O,v80)==128?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_pE8_Offset[FIELD_OFFSET(P,pE8)==232?1:-1];
typedef char P_v190_Offset[FIELD_OFFSET(P,v190)==400?1:-1];
typedef char P_x13D8_Offset[FIELD_OFFSET(P,x13D8)==5080?1:-1];
typedef char VT_PrefixSize[sizeof(struct VT)==8?1:-1];
typedef char O_PrefixSize[sizeof(struct O)==144?1:-1];
typedef char P_PrefixSize[sizeof(struct P)==5088?1:-1];
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char int_Size[sizeof(int)==4?1:-1];
typedef char U_q_Offset[((unsigned int)&(((U*)0x10000)->q)-0x10000)==0?1:-1];
typedef char Factor_Address[FACTOR_ADDRESS==0x002C09A4?1:-1];
extern "C" void func_001B6CC0(struct P *p)
{
    switch (p->x13D8) {
    case 0:
        func_001FAC30(p, Scale(p->pE8->v80, -1.0f));
    case 1: {
        qword v = ((qword (*)(void *))p->vt[33].pfn)((char *)p + p->vt[33].d);
        U u; qword kn;
        qword n = Negative(p->v190, &kn);
        int bits = ReadFactor();
        qword d = Sub(n, v);
        qword up = D_002A2DC0;
        d = Sub(d, Projection(d,up));
        qword f = Factor(d, bits, &u);
        u.q = kn;
        func_001FAC30(p, f);
        break;
    }
    case 2:
        break;
    }
}
