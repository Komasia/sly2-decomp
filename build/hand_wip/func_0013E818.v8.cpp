// v8 (Claude agent, laneC19 2026-10-23): aligned 51 -> 31. The 0x8000 branch body is an inner { } scope holding aref2/aw/apv (the aref2 dtor loop runs at its end), and i++ is ONE statement after the if/else (not in each branch): the dtor-loop pointer now gets s1 = a2 in the func_00200DA0 delay slot, and i is in s1 like the target. Left: spill-slot order (ours i at 0x268 first; target 0x27C after the address pseudos), the 0x13ED88 p reload, the case-22 tail.
// v7 (Claude agent, laneC9 2026-10-23): aligned 52 -> 51, positional 387 -> 107 (instruction count 1023 vs 1022). Case 2/3 (by-value qword pmf): the Make result is ALSO stored to a stack VECTOR4 (`VECTOR4 vv; *(qword *)&vv = v;`), giving the target's sq a1,0x10 in the bltz slot. With that, case 4 as a single `MATRIX3 m; m = func_0011B570(u.q); pmf(&m)` gives ret 0x50 -> 0x20 like the target. Left: i in s2 (target s1), p (0x214) reload inheritance at 0x13ED88 and the case-22 tail (lw a0,0x214 not in the jal slot).
// v6 (Claude agent, laneC8 2026-10-23): 75 -> 52: both case-22 allocations as func_001AE2A0/func_001AE378(AREQ(c * 2, 0x10)) with a ctor'd AREQ temp passed by const ref (a.c stored before the call like the target). Left: i reg s2 (target s1), case 2/3 qword temp sq at 0x10, case 4 (target: ret at 0x50 copied once to 0x20, 0x80-0xAF unused; single m / NRV init / by-value MATRIX3 pmf all worse: 69-163).
// v5 (Claude agent, laneC7 2026-10-23): 102 -> 75: case 13 OIDs as BLKmode char[4] locals (shared temp slots like the target), FRAME as SImode struct {int n} (permanent slot 0x210), else-branch `PMFI pmf` declared AFTER the po block (pmfGet and pmf share sp+0), `default:` with case 8/18 in both switches. Left: i in s2 (target s1), case 2 Make temp, branch offsets.
// wip v2 (Claude agent, 2026-10-17): LoadOptionFromBrx-like EOPID reader. 253 -> 134 aligned: cases 9/11 split, by-value VECTOR via Make/Make4 asm,
// OID copied as char[4] (lwl/lwr). Left: path A inner loop (target counts down, ptr givs), case-local stack slot sharing, case 4/22 temps.
typedef int qword __attribute__((mode(TI)));
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct VECTOR3 { float x, y, z; };
struct VECTOR2 { float x, y; };
struct VECTOR4 { float x, y, z, w; };
struct MATRIX3 { qword r[3]; };
struct OID { int n; };
struct OIDB { char ab[4]; };
struct ARR { int c; void *pv; };
struct AREQ { int cb; int align; AREQ(int c, int a) { cb = c; align = a; } };
struct FRAME { int n; FRAME(); ~FRAME(); };
class CBinaryInputStream;

extern "C" {
void *func_00129658(void *pref, const void *pref2);
void func_00129EC8(void *pref);
}
struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    ~CRef() { func_00129EC8(this); }
    CRef &operator=(const CRef &r) { func_00129658(this, &r); return *this; }
};

class LO {
public:
    int pad[3];
    virtual void Dummy();
};
typedef void *(LO::*PMFGET)(int);
typedef void (LO::*PMFI)(int);
typedef void (LO::*PMFF)(float);
typedef void (LO::*PMFP)(const void *);
typedef void (LO::*PMFV)(qword);
typedef void (LO::*PMFVV)(VECTOR);
typedef void (LO::*PMFO)(OID);
struct DEFER { int n; int ib; };
struct DEFERP { int n; PMFI pmf; };
struct DEFQ { void *pfn; void *pv; };
struct GS;
extern GS D_003DD490;

struct EOPID {
    int k;
    int grf;
    CRef (*pfn8)(LO *p, int c, CRef *aref);
    int pad;
    union { CRef (*pfn10)(LO *p, int c, CRef *aref); PMFI pmf10; int ib10; };
    union { int c18; PMFI pmf18; };
    PMFGET pmf20;
};

extern "C" {
unsigned int func_00117BD0(CBinaryInputStream *pbis);   /* U8Read */
unsigned int func_00117C20(CBinaryInputStream *pbis);   /* U16Read */
int func_00117DB8(CBinaryInputStream *pbis);
float func_00117E38(CBinaryInputStream *pbis);
int func_00117C80(CBinaryInputStream *pbis);
int func_00117D50(CBinaryInputStream *pbis);
void func_00117968(CBinaryInputStream *pbis, int cb, void *pv);
void func_001ED278(OID *poid);
MATRIX3 func_0011B570(qword v);
void *func_001AE2A0(const AREQ &req);
void *func_001AE378(const AREQ &req);
void *func_00210120(GS *pgs);
DEFQ *func_001A5D58(LO *p);
void func_0013E590(LO *p, DEFER *pd);
void func_0013E5E0(LO *p, DEFERP *pd);
CRef func_0013E690(int w, CBinaryInputStream *pbis);
CRef func_00200DA0(int c, int *aw, void **apv);
void func_0013E818(LO *p, EOPID *peopid, int grf, CBinaryInputStream *pbis);
}

static __inline__ qword Make(float x, float y, float z) { qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z)); return q; }
static __inline__ VECTOR MakeV(qword q) { union { qword q; VECTOR v; } u; u.q = q; return u.v; }
static __inline__ qword Make4(float x, float y, float z, float w) { qword q, t, u;
    __asm__("mfc1 %0,%3\n\tmfc1 %1,%4\n\tpextlw %0,%1,%0\n\tmfc1 %1,%5\n\tmfc1 %2,%6\n\tpextlw %1,%2,%1\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t), "=&r"(u) : "f"(x), "f"(y), "f"(z), "f"(w)); return q; }

static inline OID ReadOid(CBinaryInputStream *pbis)
{
    OID oid;
    oid.n = func_00117C80(pbis);
    func_001ED278(&oid);
    return oid;
}

void func_0013E818(LO *p, EOPID *peopid, int grf, CBinaryInputStream *pbis)
{
    if (grf & 0x401) {
        CRef aref[32];
        int fAlt = grf & 0x400;
        int c = peopid->c18;
        int i;
        for (i = 0; i < c;) {
            int w = func_00117C20(pbis);
            if (w & 0x8000) {
              {
                CRef aref2[16];
                int aw[16];
                void *apv[16];
                int n, j;
                w &= ~0x8000;
                n = func_00117BD0(pbis);
                for (j = 0; j < n; j++) {
                    CRef *pr = &aref2[j];
                    *pr = func_0013E690(w, pbis);
                    apv[j] = &pr->m_tag;
                    aw[j] = w;
                }
                CRef *pr = &aref[i];
                *pr = func_00200DA0(n, aw, apv);
              }
            } else {
                CRef *pr = &aref[i];
                *pr = func_0013E690(w, pbis);
            }
            i++;
        }
        if (fAlt)
            peopid->pfn8(p, c, aref);
        else
            peopid->pfn10(p, c, aref);
    } else if (grf & 0x90) {
        char *pv;
        if (grf & 0x2000) {
            PMFGET pmf = peopid->pmf20;
            pv = (char *)(p->*pmf)(1) + peopid->c18;
        } else {
            pv = (char *)p + peopid->c18;
        }
        switch (peopid->k) {
        case 0:
            *(unsigned char *)pv = func_00117BD0(pbis);
            break;
        case 5:
        case 6:
            *(int *)pv = func_00117DB8(pbis);
            break;
        case 1:
            *(float *)pv = func_00117E38(pbis);
            break;
        case 10:
            ((float *)pv)[0] = func_00117E38(pbis);
            ((float *)pv)[1] = func_00117E38(pbis);
            break;
        case 2:
        case 9:
        case 11:
            ((float *)pv)[0] = func_00117E38(pbis);
            ((float *)pv)[1] = func_00117E38(pbis);
            ((float *)pv)[2] = func_00117E38(pbis);
            break;
        case 3:
        case 12:
            ((float *)pv)[0] = func_00117E38(pbis);
            ((float *)pv)[1] = func_00117E38(pbis);
            ((float *)pv)[2] = func_00117E38(pbis);
            ((float *)pv)[3] = func_00117E38(pbis);
            break;
        case 13:
        {
            OIDB oid;
            *(int *)&oid = func_00117C80(pbis);
            func_001ED278((OID *)&oid);
            *(int *)pv = *(int *)&oid;
        }
            break;
        case 4: {
            union { qword q; VECTOR3 v; } u;
            u.v.x = func_00117E38(pbis);
            u.v.y = func_00117E38(pbis);
            u.v.z = func_00117E38(pbis);
            *(MATRIX3 *)pv = func_0011B570(u.q);
            break;
        }
        case 22: {
            ARR *pa = (ARR *)pv;
            pa->c = func_00117C20(pbis);
            pa->pv = func_001AE2A0(AREQ(pa->c * 2, 0x10));
            func_00117968(pbis, pa->c * 2, pa->pv);
            break;
        }
        case 7: case 14: case 15: case 16: case 17: case 19: case 20: case 21: case 23:
            *(int *)pv = func_00117D50(pbis);
            break;
        case 8:
        case 18:
        default:
            switch ((peopid->k & ~0x8000) >> 12) {
            case 1:
                *(int *)pv = func_00117C80(pbis);
                break;
            case 2:
                if (grf & 0x80) {
                    int n = func_00117DB8(pbis);
                    DEFER *pd = (DEFER *)func_00210120(&D_003DD490);
                    DEFQ *pq;
                    pd->n = n;
                    pd->ib = pv - (char *)p;
                    pq = func_001A5D58(p);
                    pq->pv = pd;
                    pq->pfn = (void *)func_0013E590;
                } else {
                    DEFER d;
                    d.n = func_00117DB8(pbis);
                    d.ib = peopid->ib10;
                    func_0013E590(p, &d);
                }
                break;
            }
            break;
        }
    } else {
        LO *po;
        if (grf & 0x2000) {
            PMFGET pmfGet = peopid->pmf20;
            po = (LO *)(p->*pmfGet)(1);
        } else {
            po = p;
        }
        PMFI pmf;
        if (grf & 0x100)
            pmf = peopid->pmf18;
        else
            pmf = peopid->pmf10;
        switch (peopid->k) {
        case 0:
            (po->*pmf)(func_00117BD0(pbis));
            break;
        case 5:
        case 6:
            (po->*pmf)(func_00117DB8(pbis));
            break;
        case 1:
            (po->*(PMFF)pmf)(func_00117E38(pbis));
            break;
        case 10: {
            VECTOR2 v;
            v.x = func_00117E38(pbis);
            v.y = func_00117E38(pbis);
            (po->*(PMFP)pmf)(&v);
            break;
        }
        case 9: {
            VECTOR3 v;
            float x = func_00117E38(pbis);
            float y = func_00117E38(pbis);
            float z = func_00117E38(pbis);
            v.x = x; v.y = y; v.z = z;
            (po->*(PMFP)pmf)(&v);
            break;
        }
        case 11: {
            VECTOR3 v;
            float x = func_00117E38(pbis);
            float y = func_00117E38(pbis);
            float z = func_00117E38(pbis);
            v.x = x; v.y = y; v.z = z;
            (po->*(PMFP)pmf)(&v);
            break;
        }
        case 2: {
            float x = func_00117E38(pbis);
            float y = func_00117E38(pbis);
            float z = func_00117E38(pbis);
            qword v = Make(x, y, z);
            VECTOR4 vv;
            *(qword *)&vv = v;
            (po->*(PMFV)pmf)(v);
            break;
        }
        case 12: {
            VECTOR4 v;
            float x = func_00117E38(pbis);
            float y = func_00117E38(pbis);
            float z = func_00117E38(pbis);
            float w = func_00117E38(pbis);
            v.x = x; v.y = y; v.z = z; v.w = w;
            (po->*(PMFP)pmf)(&v);
            break;
        }
        case 3: {
            float x = func_00117E38(pbis);
            float y = func_00117E38(pbis);
            float z = func_00117E38(pbis);
            float w = func_00117E38(pbis);
            qword v = Make4(x, y, z, w);
            VECTOR4 vv;
            *(qword *)&vv = v;
            (po->*(PMFV)pmf)(v);
            break;
        }
        case 13: {
            OIDB oid, oid2;
            *(int *)&oid = func_00117C80(pbis);
            func_001ED278((OID *)&oid);
            oid2 = oid;
            (po->*(PMFP)pmf)(&oid2);
            break;
        }
        case 4: {
            union { qword q; VECTOR3 v; } u;
            MATRIX3 m;
            u.v.x = func_00117E38(pbis);
            u.v.y = func_00117E38(pbis);
            u.v.z = func_00117E38(pbis);
            m = func_0011B570(u.q);
            (po->*(PMFP)pmf)(&m);
            break;
        }
        case 22: {
            FRAME frame;
            ARR a;
            a.c = func_00117C20(pbis);
            a.pv = func_001AE378(AREQ(a.c * 2, 0x10));
            func_00117968(pbis, a.c * 2, a.pv);
            (po->*(PMFP)pmf)(&a);
            break;
        }
        case 7: case 14: case 15: case 16: case 17: case 19: case 20: case 21: case 23:
            (po->*pmf)(func_00117D50(pbis));
            break;
        case 8:
        case 18:
        default:
            switch ((peopid->k & ~0x8000) >> 12) {
            case 1:
                (po->*pmf)(func_00117C80(pbis));
                break;
            case 2:
                if (grf & 0x100) {
                    int n = func_00117DB8(pbis);
                    DEFERP *pd = (DEFERP *)func_00210120(&D_003DD490);
                    DEFQ *pq;
                    pd->n = n;
                    pd->pmf = peopid->pmf18;
                    pq = func_001A5D58(p);
                    pq->pv = pd;
                    pq->pfn = (void *)func_0013E5E0;
                } else {
                    DEFERP d;
                    d.n = func_00117DB8(pbis);
                    d.pmf = peopid->pmf10;
                    func_0013E5E0(p, &d);
                }
                break;
            }
            break;
        }
    }
}
