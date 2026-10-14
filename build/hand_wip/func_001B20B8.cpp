typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct VT { short d; short pad; void *pfn; };
struct SMP { float a, b, c; };
union WORD {float value;int bits;};
struct CLOCK { float t; WORD dt; };
extern "C" struct CLOCK D_002DDED0;
struct SPS {qword v; int k;}; struct O;
struct Q { char pad[0xB0]; struct SPS xB0; };
struct P { char pad[0xC]; struct VT *vt; char pad1[0x58 - 0x10]; struct O *x58; char pad2[0xE8 - 0x5C]; struct Q *pE8; char pad3[0x1E8 - 0xEC]; int x1E8;
           char pad4[0x270 - 0x1EC]; float g270; float g274; };
extern "C" void *func_002333B4(void *p, int c, int cb);
extern "C" float func_0011D018(struct SMP *psmp,float *out,float g,float gTarget,float dt);
extern "C" qword func_001FA810(struct SPS *p, struct O *other, qword v);
extern "C" void func_001FAC30(struct P *p, qword v);
static inline float Length(qword v)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
static inline U Bcast(float g) return u { qword q; __asm__("qmtc2.ni %1,%0":"=j"(q):"r"(g));u.q=q; }
static inline U BcastI(int bits) return u {qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));u.q=q;}
static inline qword VDiv(qword v, qword s) { qword r; __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(s), "j"(v)); return r; }
static inline qword VMulX(qword v, qword s) { register qword r __asm__("vf3"); __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s)); return r; }
static inline qword VSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char WORD_value_Offset[FIELD_OFFSET(WORD,value)==0?1:-1];
typedef char WORD_bits_Offset[FIELD_OFFSET(WORD,bits)==0?1:-1];
typedef char VT_d_Offset[FIELD_OFFSET(VT,d)==0?1:-1];
typedef char VT_pfn_Offset[FIELD_OFFSET(VT,pfn)==4?1:-1];
typedef char SMP_a_Offset[FIELD_OFFSET(SMP,a)==0?1:-1];
typedef char SMP_b_Offset[FIELD_OFFSET(SMP,b)==4?1:-1];
typedef char SMP_c_Offset[FIELD_OFFSET(SMP,c)==8?1:-1];
typedef char CLOCK_t_Offset[FIELD_OFFSET(CLOCK,t)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
typedef char SPS_v_Offset[FIELD_OFFSET(SPS,v)==0?1:-1];
typedef char SPS_k_Offset[FIELD_OFFSET(SPS,k)==16?1:-1];
typedef char Q_xB0_Offset[FIELD_OFFSET(Q,xB0)==176?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_x58_Offset[FIELD_OFFSET(P,x58)==88?1:-1];
typedef char P_pE8_Offset[FIELD_OFFSET(P,pE8)==232?1:-1];
typedef char P_x1E8_Offset[FIELD_OFFSET(P,x1E8)==488?1:-1];
typedef char P_g270_Offset[FIELD_OFFSET(P,g270)==624?1:-1];
typedef char P_g274_Offset[FIELD_OFFSET(P,g274)==628?1:-1];
typedef char qword_PrefixSize[sizeof(qword)==16?1:-1];
typedef char U_PrefixSize[sizeof(U)==16?1:-1];
typedef char WORD_PrefixSize[sizeof(WORD)==4?1:-1];
typedef char VT_PrefixSize[sizeof(VT)==8?1:-1];
typedef char SMP_PrefixSize[sizeof(SMP)==12?1:-1];
typedef char CLOCK_PrefixSize[sizeof(CLOCK)==8?1:-1];
typedef char SPS_PrefixSize[sizeof(SPS)==32?1:-1];
typedef char Q_PrefixSize[sizeof(Q)==208?1:-1];
typedef char P_PrefixSize[sizeof(P)==632?1:-1];
extern "C" void func_001B20B8(struct P *p)
{
    qword v, n;
    float len, g;
    if (p->x1E8)
        return;
    v = ((qword (*)(void *))p->vt[33].pfn)((char *)p + p->vt[33].d);
    len = Length(v);
    n = VDiv(v,Bcast(len).q);
    {
        struct SMP smp;
        {
            struct SMP t;
            func_002333B4(&t, 0, sizeof(t));
            t.a = p->g274;
            t.c = 1.0f;
            smp = t;
        }
        float dt=D_002DDED0.dt.value; g=func_0011D018(&smp,0,len,p->g270,dt);
    }
    func_001FAC30(p,func_001FA810(&p->pE8->xB0,p->x58,VDiv(VSub(VMulX(n,Bcast(g).q),v),BcastI(D_002DDED0.dt.bits).q)));
}
