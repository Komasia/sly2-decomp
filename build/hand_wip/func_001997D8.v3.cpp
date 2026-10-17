/* (Claude agent) 55/126: both outer loops written with goto (no loop.c loop) give the target's per-iteration recompute of apt+1+(i<<4) (sll; addiu sp,0x80; addu). Left: saved-reg numbering (target l=s4,i=s2,cursor=s3 with an s6 copy), cursor init hoisted in ours, M4::Init row copy order, loop-header nop. */
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];int i[4];};
struct M3 {U r[3];M3(){}M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];}M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;}};
struct M4 {M3 m;U pos;void Init(const M3&,qword);};
struct PLANE {qword q;};
struct HIT {U point[2];U plane[2];float parameter[2];int kind;PLANE*face[2];int pad[5];};
struct BSP;
struct S0 {char pad[0x10];long x10;char pad2[0x60-0x18];S0*x60;char pad64[0x10];BSP*tree;};
struct EC2 { char pad[0x34]; struct S0 *x34; char pad2[0x70-0x38]; long x70; };
struct C { char pad[0xEC]; struct EC2 *xec; };
struct L { int x0; struct L *x4; int x8; struct C *xc; };
struct EC { char pad[0x64]; struct L *x64; };
struct O { char pad[0xEC]; struct EC *xec; };
struct P { struct O *x0; };
extern qword D_002A2DC0;
extern qword D_002A2DB0;
extern "C" void func_0011E2D8(qword a, qword b, qword c, qword *pm);
extern "C" qword *func_00256D18(qword *pq, qword q);
extern "C" void func_001995D8(struct P *p, const M4 *pm, int n, U *apt);
inline void M4::Init(const M3&a,qword v){(void)func_00256D18(&pos.q,v);m=a;m.r[0].i[3]=m.r[1].i[3]=m.r[2].i[3]=0;pos.f[3]=1.0f;}
extern "C" int func_0014C6A0(struct S0 *s, qword a, qword b, int n, HIT *ph);
extern "C" int func_001997D8(struct P *p, qword q1, qword q2)
{
    register qword point __asm__("$17")=q1;
    M3 m;
    M4 m4;
    qword apt[22];
    HIT hit;
    struct L *l;
    int c = 0;
    m.r[0].q = q2;
    func_0011E2D8(q2, D_002A2DC0, D_002A2DB0, &m.r[1].q);
    m4.Init(m,point);
    func_001995D8(p, &m4, 22, (U*)apt);
    l = p->x0->xec->x64;
    if (!l) goto done;
ltop:
    {
        int i;
        if (l->xc->xec->x70 & 4)
            goto next;
        qword *cursor = apt;
        i = 0;
    top:
        {
            struct S0 *s;
            for (s = l->xc->xec->x34; s; s = s->x60) {
                if (s->x10 & (1L << 48))
                    continue;
                if (func_0014C6A0(s, *cursor, *(qword *)((int)(apt + 1) + (i << 4)), 1, &hit) <= 0)
                    continue;
                if (i < 4)
                    return 0;
                if (hit.parameter[0] == 0.0f)
                    return 0;
                if (hit.plane[0].f[2] > 0.7f)
                    c++;
            }
        }
        i += 2;
        cursor += 2;
        if (i < sizeof apt / sizeof *apt)
            goto top;
        }
next:
    l = l->x4;
    if (l) goto ltop;
done:
    return c >= 2;
}

typedef char guard_S0_x10[(unsigned)&((S0*)0)->x10==16?1:-1];
typedef char guard_S0_x60[(unsigned)&((S0*)0)->x60==96?1:-1];
typedef char guard_S0_tree[(unsigned)&((S0*)0)->tree==116?1:-1];
typedef char guard_EC2_x34[(unsigned)&((EC2*)0)->x34==52?1:-1];
typedef char guard_EC2_x70[(unsigned)&((EC2*)0)->x70==112?1:-1];
typedef char guard_C_xec[(unsigned)&((C*)0)->xec==236?1:-1];
typedef char guard_L_x4[(unsigned)&((L*)0)->x4==4?1:-1];
typedef char guard_L_xc[(unsigned)&((L*)0)->xc==12?1:-1];
typedef char guard_EC_x64[(unsigned)&((EC*)0)->x64==100?1:-1];
typedef char guard_O_xec[(unsigned)&((O*)0)->xec==236?1:-1];
typedef char guard_P_x0[(unsigned)&((P*)0)->x0==0?1:-1];
typedef char guard_M3_r[(unsigned)&((M3*)0)->r==0?1:-1];
typedef char guard_M4_m[(unsigned)&((M4*)0)->m==0?1:-1];
typedef char guard_M4_pos[(unsigned)&((M4*)0)->pos==48?1:-1];
typedef char guard_HIT_point[(unsigned)&((HIT*)0)->point==0?1:-1];
typedef char guard_HIT_plane[(unsigned)&((HIT*)0)->plane==32?1:-1];
typedef char guard_HIT_parameter[(unsigned)&((HIT*)0)->parameter==64?1:-1];
typedef char guard_HIT_kind[(unsigned)&((HIT*)0)->kind==72?1:-1];
typedef char guard_HIT_face[(unsigned)&((HIT*)0)->face==76?1:-1];
typedef char guard_size_0[sizeof(qword)==16?1:-1];
typedef char guard_size_1[sizeof(U)==16?1:-1];
typedef char guard_size_2[sizeof(M3)==48?1:-1];
typedef char guard_size_3[sizeof(M4)==64?1:-1];
typedef char guard_size_4[sizeof(HIT)==112?1:-1];
typedef char guard_size_5[sizeof(PLANE)==16?1:-1];
typedef char guard_size_6[sizeof(S0)==120?1:-1];
typedef char guard_size_7[sizeof(EC2)==120?1:-1];
typedef char guard_size_8[sizeof(C)==240?1:-1];
typedef char guard_size_9[sizeof(L)==16?1:-1];
typedef char guard_size_10[sizeof(EC)==104?1:-1];
typedef char guard_size_11[sizeof(O)==240?1:-1];
typedef char guard_size_12[sizeof(P)==4?1:-1];
typedef char guard_size_13[sizeof(long)==8?1:-1];
typedef char guard_size_14[sizeof(int)==4?1:-1];
typedef char guard_size_15[sizeof(void*)==4?1:-1];
typedef char guard_align_0[__alignof__(qword)==16?1:-1];
typedef char guard_align_1[__alignof__(U)==16?1:-1];
typedef char guard_align_2[__alignof__(M3)==16?1:-1];
typedef char guard_align_3[__alignof__(M4)==16?1:-1];
typedef char guard_align_4[__alignof__(HIT)==16?1:-1];
typedef char guard_align_5[__alignof__(long)==8?1:-1];
typedef char guard_align_6[__alignof__(void*)==4?1:-1];
