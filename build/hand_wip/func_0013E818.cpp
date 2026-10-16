// wip (Claude agent): LoadOptionFromBrx-like EOPID reader: grf&0x401 -> CRef arrays via func_13E690/func_200DA0 + pfn8/pfn10; grf&0x90 -> store by type into p+ib; else call PMF setter by type (24 types, 2 jump tables).
// 741/1022 diffs: frame 0x350 matches; stack slot offsets of the spilled args are off by 8 (sp+0x214 vs 0x21C), loop shape in path A, PMF copy slot.
typedef int qword __attribute__((mode(TI)));
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct VECTOR3 { float x, y, z; };
struct VECTOR2 { float x, y; };
struct VECTOR4 { float x, y, z, w; };
struct MATRIX3 { qword r[3]; };
struct OID { int n; };
struct ARR { int c; void *pv; };
struct AREQ { int cb; int align; };
struct FRAME { char pad[4]; FRAME(); ~FRAME(); };
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
typedef void (LO::*PMFV)(VECTOR);
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
void *func_001AE2A0(AREQ *preq);
void *func_001AE378(AREQ *preq);
void *func_00210120(GS *pgs);
DEFQ *func_001A5D58(LO *p);
void func_0013E590(LO *p, DEFER *pd);
void func_0013E5E0(LO *p, DEFERP *pd);
CRef func_0013E690(int w, CBinaryInputStream *pbis);
CRef func_00200DA0(int c, int *aw, void **apv);
void func_0013E818(LO *p, EOPID *peopid, int grf, CBinaryInputStream *pbis);
}

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
                CRef aref2[16];
                int aw[16];
                void *apv[16];
                int n, j;
                w &= ~0x8000;
                n = func_00117BD0(pbis);
                for (j = 0; j < n; j++) {
                    aref2[j] = func_0013E690(w, pbis);
                    apv[j] = &aref2[j].m_tag;
                    aw[j] = w;
                }
                aref[i] = func_00200DA0(n, aw, apv);
                i++;
            } else {
                aref[i++] = func_0013E690(w, pbis);
            }
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
            *(OID *)pv = ReadOid(pbis);
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
            AREQ req;
            pa->c = func_00117C20(pbis);
            req.cb = pa->c * 2;
            req.align = 0x10;
            pa->pv = func_001AE2A0(&req);
            func_00117968(pbis, pa->c * 2, pa->pv);
            break;
        }
        case 7: case 14: case 15: case 16: case 17: case 19: case 20: case 21: case 23:
            *(int *)pv = func_00117D50(pbis);
            break;
        case 8:
        case 18:
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
        PMFI pmf;
        if (grf & 0x2000) {
            PMFGET pmfGet = peopid->pmf20;
            po = (LO *)(p->*pmfGet)(1);
        } else {
            po = p;
        }
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
        case 9:
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
            VECTOR v;
            float x = func_00117E38(pbis);
            float y = func_00117E38(pbis);
            float z = func_00117E38(pbis);
            v.x = x; v.y = y; v.z = z;
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
            VECTOR v;
            float x = func_00117E38(pbis);
            float y = func_00117E38(pbis);
            float z = func_00117E38(pbis);
            float w = func_00117E38(pbis);
            v.x = x; v.y = y; v.z = z; v.w = w;
            (po->*(PMFV)pmf)(v);
            break;
        }
        case 13: {
            OID oid, oid2;
            oid.n = func_00117C80(pbis);
            func_001ED278(&oid);
            oid2 = oid;
            (po->*(PMFP)pmf)(&oid2);
            break;
        }
        case 4: {
            union { qword q; VECTOR3 v; } u;
            MATRIX3 m, m2;
            u.v.x = func_00117E38(pbis);
            u.v.y = func_00117E38(pbis);
            u.v.z = func_00117E38(pbis);
            m = func_0011B570(u.q);
            m2 = m;
            (po->*(PMFP)pmf)(&m2);
            break;
        }
        case 22: {
            FRAME frame;
            ARR a;
            AREQ req;
            a.c = func_00117C20(pbis);
            req.cb = a.c * 2;
            req.align = 0x10;
            a.pv = func_001AE378(&req);
            func_00117968(pbis, a.c * 2, a.pv);
            (po->*(PMFP)pmf)(&a);
            break;
        }
        case 7: case 14: case 15: case 16: case 17: case 19: case 20: case 21: case 23:
            (po->*pmf)(func_00117D50(pbis));
            break;
        case 8:
        case 18:
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
