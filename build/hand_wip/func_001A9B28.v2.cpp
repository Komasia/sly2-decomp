/* (Claude agent, 2026-10-17) aligned 5 -> 2: dependency-only "m"(r) on the qmfc2 puts it after `lq a3` like the target, but the stack-arg `sw s4,0(sp)` then sinks below it. */
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; U(); };
struct S0 { char pad[0x70]; qword x70; };
struct LO;struct CONTACT;struct NODE;
struct S { struct S0 *x0; struct LO *x4; float x8; };
union DETAIL {void*pointer;int word;};
struct E {qword x0,x10;int x20;DETAIL detail;};
extern "C" int func_001A93C8(qword pos, struct S*b,int c,int d,struct NODE*e,int n, struct E *buf, float f);
extern "C" U*func_002564B8(U*p);
extern "C" void func_001A7C18(void *a, struct S*s,struct S*b,qword p, qword q, int x20, int z, int x24,struct CONTACT**g,float f);
inline U::U() { (void)func_002564B8(this); }
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char Offset_0[FIELD_OFFSET(U,q)==0?1:-1];
typedef char Offset_1[FIELD_OFFSET(U,f)==0?1:-1];
typedef char Offset_2[FIELD_OFFSET(DETAIL,pointer)==0?1:-1];
typedef char Offset_3[FIELD_OFFSET(DETAIL,word)==0?1:-1];
typedef char Offset_4[FIELD_OFFSET(S0,x70)==112?1:-1];
typedef char Offset_5[FIELD_OFFSET(S,x0)==0?1:-1];
typedef char Offset_6[FIELD_OFFSET(S,x4)==4?1:-1];
typedef char Offset_7[FIELD_OFFSET(S,x8)==8?1:-1];
typedef char Offset_8[FIELD_OFFSET(E,x0)==0?1:-1];
typedef char Offset_9[FIELD_OFFSET(E,x10)==16?1:-1];
typedef char Offset_10[FIELD_OFFSET(E,x20)==32?1:-1];
typedef char Offset_11[FIELD_OFFSET(E,detail)==36?1:-1];
typedef char Size_0[sizeof(U)==16?1:-1];
typedef char Size_1[sizeof(DETAIL)==4?1:-1];
typedef char Size_2[sizeof(S0)==128?1:-1];
typedef char Size_3[sizeof(S)==12?1:-1];
typedef char Size_4[sizeof(E)==48?1:-1];
typedef char Size_5[sizeof(qword)==16?1:-1];
typedef char Size_6[sizeof(void*)==4?1:-1];
typedef char Size_7[sizeof(int)==4?1:-1];
typedef char Size_8[sizeof(float)==4?1:-1];
extern "C" void func_001A9B28(void *a, struct S*s,struct S*b,int d,struct NODE*e,struct CONTACT**g)
{
    struct E buf[64];

    int i;
    struct E *pe;
    i = func_001A93C8(s->x0->x70, b, 0x7FFFFFFF, d, e, 0x40, buf, s->x8) - 1;
    if (i >= 0) {
        pe = &buf[i];
        do {
            float dist;
            int word;
            qword A, B;
            i--;
            A = pe->x0;
            B = pe->x10;
            U r,one;
            qword scalar,product;
            __asm__("vmul.xyz %1, %2, %3\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddaz.x $ACC, %0, %1z\n\tvmsubw.x %1, %0, %2w"
                    : "=&j"(scalar), "=&j"(product) : "j"(B), "j"(A));
            one.q=scalar;r.q=product;
            __asm__("qmfc2.ni %0,%1":"=r"(word):"j"(r.q),"m"(r)); /* "m"(r): dependency-only operand */
            __asm__("mtc1 %1,%0":"=f"(dist):"r"(word));
            func_001A7C18(a, s, b, A, B, pe->x20, 0, pe->detail.word, g, dist);
            pe--;
        } while (i >= 0);
    }
}
