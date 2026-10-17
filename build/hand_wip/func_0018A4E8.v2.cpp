typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct SCALAR{qword q;SCALAR(){}SCALAR(float f){__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));}};
inline void*operator new(unsigned,void*p){return p;}
struct WORK{VU scalar;VU forward,reverse;VU kept;};
typedef struct M { qword r[4]; } M;
struct C;
typedef struct A { char pad[0x1024]; C*x1024; } A;
typedef struct B { char pad[0xE4]; int xE4; char pad1[0x1BC - 0xE8]; int x1BC; } B;
typedef struct C114 { char pad[0x10]; float g10; } C114;
typedef struct C { char pad[0x114]; C114 *p114; } C;
typedef struct S {
    A *p0; int x4; int x8; int pad0c[2]; B *p14; int pad18[2]; float g20; int pad24[2]; int x2C; int pad30[4];
    qword v40; float g50; int pad54[5]; C *p68;
} S;
typedef struct R { unsigned int x0; char pad[0x30 - 4]; float g30; int x34; int pad38; int x3C; } R;
typedef struct CLOCK { float t; float dt; } CLOCK;

extern "C" CLOCK D_002DDED0;
extern "C" char D_002BF348[];

extern "C" float func_00204740(A *p);
extern "C" int func_00132B10(B *p, int n);
extern "C" float func_001E6648(B *p);
extern "C" float func_001E6620(B *p);
extern "C" void func_001E6F10(B *p, qword *pv, qword *direction, float g);
extern "C" qword func_001A62E8(A *p);
extern "C" M *func_001A6318(A *p);
extern "C" float func_0011D018(void *p, float a, float b, float c, float *output);

static __inline__ float GClamp(float g, float lo, float hi) { if (g < lo) return lo; if (g > hi) return hi; return g; }
static __inline__ float GMin(float a,float b){return a<b?a:b;}
static __inline__ float GMax(float a,float b){return a>b?a:b;}

static __inline__ qword OffsetAdd(const M*m,const VU*scalar,const VU*base){
 register qword value __asm__("vf1"),row __asm__("vf2");
 __asm__("lqc2 %1,%2\n\tlqc2 %0,%3\n\tvmulx.xyzw %0,%1,%0x\n\tlqc2 %1,%4\n\tvadd.xyzw %0,%1,%0":"=&j"(value),"=&j"(row):"m"(m->r[1]),"m"(scalar->q),"m"(base->q));return value;
}
static __inline__ qword OffsetSub(const M*m,const VU*scalar,const VU*base){
 register qword value __asm__("vf1"),row __asm__("vf2");
 __asm__("lqc2 %1,%2\n\tlqc2 %0,%3\n\tvmulx.xyzw %0,%1,%0x\n\tlqc2 %1,%4\n\tvsub.xyzw %0,%1,%0":"=&j"(value),"=&j"(row):"m"(m->r[1]),"m"(scalar->q),"m"(base->q));return value;
}
extern "C" void func_0018A4E8(S *ps, R *pr)
{
    float g;
    WORK w;

    if (ps->x8 != 0)
        return;
    pr->g30 = func_00204740(ps->p0);
    if (ps->p0->x1024 != ps->p68)
        return;
    pr->x34 = 0;
    if (ps->x2C >= 3) goto tail;
    if (ps->x2C > 0) goto a12;
    if (ps->x2C == 0) goto c0;
    goto tail;
    {
    a12:
        if (func_00132B10(ps->p14, 0xC)) {
            B *pb = ps->p14;
            if (ps->x2C == 1) {
                g = ps->g20 + (ps->g50*125.0f)*ps->g50;
                if (pb->xE4 == 0) {
                    float h = func_001E6648(pb);
                    if (pb->x1BC & 2)
                        h += 100.0f;
                    g = GMin(g, h);
                }
            } else {
                g = ps->g20 - (ps->g50*125.0f)*ps->g50;
                if (pb->xE4 == 0) {
                    float h = func_001E6620(pb);
                    if (pb->x1BC & 1)
                        h -= 100.0f;
                    g = GMax(g, h);
                }
            }
            func_001E6F10(pb, &ps->v40, 0, g);
            ((float *)&ps->v40)[2] += 125.0f;
        } else if (ps->x2C == 1) {
            w.forward.q=func_001A62E8(ps->p0);
            { float f = (ps->g50*125.0f)*ps->g50; qword t; __asm__("qmtc2.ni %1,%0":"=j"(t):"r"(f)); w.kept.q = t; w.scalar.q = t; }
            ps->v40 = OffsetAdd(func_001A6318(ps->p0),(VU*)&w.kept,&w.forward);
            goto lift50;
        } else {
            w.reverse.q=func_001A62E8(ps->p0);
            { float f = (ps->g50*125.0f)*ps->g50; qword t; __asm__("qmtc2.ni %1,%0":"=j"(t):"r"(f)); w.kept.q = t; w.scalar.q = t; }
            ps->v40 = OffsetSub(func_001A6318(ps->p0),(VU*)&w.kept,&w.reverse);
            goto lift50;
        }
    }
    goto tail;
c0:
        ps->v40 = func_001A62E8(ps->p0);
        lift50:
        ((float *)&ps->v40)[2] += 50.0f;
tail:
    if (func_00132B10(ps->p14, 0xC) && ps->p14->xE4 == 0) {
        float k;
        float c = 30.0f;
        float h = func_001E6648(ps->p14) - c;
        float d = GMin((h - c) * 0.5f, 300.0f);
        float e = d + c;
        float x = ps->g20;
        h = h - d;
        if (x < e) {
            float t = GClamp((e - x) / d, 0.0f, 1.0f);
            k=(-t*t)*150.0f;
        } else if (h < x) {
            float t = GClamp((x - h) / d, 0.0f, 1.0f);
            k=(t*t)*150.0f;
        } else {
            k = 0.0f;
        }
        ps->p68->p114->g10 = func_0011D018(D_002BF348, ps->p68->p114->g10, k, D_002DDED0.dt, 0);
    }
    switch (ps->x8) {
    case 0:
    case 0xD:
        pr->x3C = 1;
        break;
    case 1:
    case 3:
    case 4:
        break;
    default:
        pr->x0 |= 1;
        break;
    }
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char Pointer_Size[(sizeof(void*)==4)?1:-1];
typedef char VU_Size[(sizeof(VU)==16)?1:-1];
typedef char SCALAR_Size[(sizeof(SCALAR)==16)?1:-1];
typedef char WORK_Size[(sizeof(WORK)==0x40)?1:-1];
typedef char M_Size[(sizeof(M)==0x40)?1:-1];
typedef char CLOCK_Size[(sizeof(CLOCK)==8)?1:-1];
typedef char S_Size[(sizeof(S)==0x70)?1:-1];
typedef char R_Size[(sizeof(R)==0x40)?1:-1];
typedef char A_x1024_Offset[((unsigned)&((A*)0)->x1024==4132)?1:-1];
typedef char B_xE4_Offset[((unsigned)&((B*)0)->xE4==228)?1:-1];
typedef char B_x1BC_Offset[((unsigned)&((B*)0)->x1BC==444)?1:-1];
typedef char C114_g10_Offset[((unsigned)&((C114*)0)->g10==16)?1:-1];
typedef char C_p114_Offset[((unsigned)&((C*)0)->p114==276)?1:-1];
typedef char S_p0_Offset[((unsigned)&((S*)0)->p0==0)?1:-1];
typedef char S_x8_Offset[((unsigned)&((S*)0)->x8==8)?1:-1];
typedef char S_p14_Offset[((unsigned)&((S*)0)->p14==20)?1:-1];
typedef char S_g20_Offset[((unsigned)&((S*)0)->g20==32)?1:-1];
typedef char S_x2C_Offset[((unsigned)&((S*)0)->x2C==44)?1:-1];
typedef char S_v40_Offset[((unsigned)&((S*)0)->v40==64)?1:-1];
typedef char S_g50_Offset[((unsigned)&((S*)0)->g50==80)?1:-1];
typedef char S_p68_Offset[((unsigned)&((S*)0)->p68==104)?1:-1];
typedef char R_x0_Offset[((unsigned)&((R*)0)->x0==0)?1:-1];
typedef char R_g30_Offset[((unsigned)&((R*)0)->g30==48)?1:-1];
typedef char R_x34_Offset[((unsigned)&((R*)0)->x34==52)?1:-1];
typedef char R_x3C_Offset[((unsigned)&((R*)0)->x3C==60)?1:-1];
typedef char CLOCK_t_Offset[((unsigned)&((CLOCK*)0)->t==0)?1:-1];
typedef char CLOCK_dt_Offset[((unsigned)&((CLOCK*)0)->dt==4)?1:-1];
typedef char WORK_scalar_Offset[((unsigned)&((WORK*)0)->scalar==0)?1:-1];
typedef char WORK_forward_Offset[((unsigned)&((WORK*)0)->forward==16)?1:-1];
typedef char WORK_reverse_Offset[((unsigned)&((WORK*)0)->reverse==32)?1:-1];
typedef char WORK_kept_Offset[((unsigned)&((WORK*)0)->kept==48)?1:-1];
