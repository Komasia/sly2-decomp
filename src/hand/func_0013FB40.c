/* LoadSwObjsFromBrx__FP2SWP3ALOP18CBinaryInputStream (Claude agent, laneC11 2026-10-23): matched from wip v3. One commented register pin (pbis in s5). The plo1->x50 = 1 store is written in both arms of `if (cid == 0x84)`: gcc cross-jumps them and leaves the dead `li v1,0x84` the target has. */
struct VT { short d; short pad; void *f; };
struct IF { struct VT *vt; int x4; int x8; };
struct LO { char pad[0xC]; struct VT *vt; char pad2[0x50 - 0x10]; int x50; };
struct G { char pad[0x3F0C]; int x3F0C; int x3F10; };
extern struct VT D_002CBE38[];
extern struct G g_sw;
int S16Read(void *pbis) asm("S16Read__18CBinaryInputStream");
int S8Read(void *pbis) asm("S8Read__18CBinaryInputStream");
int S32Read(void *pbis) asm("S32Read__18CBinaryInputStream");
void Read__18CBinaryInputStreamiPv(void *pbis, int cb, void *pv);
void Skip__18CBinaryInputStreami(void *pbis, int cb);
int func_001C9940(int, int);
int func_001C99D8(int, int, int *);
int PloFindSwNearest__FP2LO3OIDii(struct G *, int, int, int, int);
int func_0015E958(struct G *, int, int, int, int);
int FFilterMatches__FiPs(int c, short *a);
int func_0015E988(int, int);
struct LO *PloNew__F3CIDP2SW3OIDi(int cid, void *psw, int oid, int n);
void LoadProxyFromBrx__FP2SWP3ALO3CID3OIDiP18CBinaryInputStreamP6LOSINK(struct G *, void *psw, int cid, int oid, int n, void *pbis, struct IF *pif);

#define VCALL1(p, n, a) ((void (*)(void *, void *))(void*)(p)->vt[n].f)((char *)(p) + (p)->vt[n].d, a)
#define VCALL2(p, n, a, b) ((void (*)(void *, int, void *))(void*)(p)->vt[n].f)((char *)(p) + (p)->vt[n].d, a, b)

static inline int FList(int k) { return k > 0 || k < -2; }

// name: SafeHouse port (LoadSwObjsFromBrx)
void LoadSwObjsFromBrx__FP2SWP3ALOP18CBinaryInputStream(void *psw, void *pbisArg, struct IF *pifParent)
{
    register void *pbis asm("$21") = pbisArg; /* register pin (Claude agent): target keeps pbis in s5 */
    struct IF obj;
    short as[0x80];
    int cid, oid, cb, n;
    int t;
    struct LO *plo1;
    struct LO *plo2;
    int c;
    int i;
    obj.vt = D_002CBE38;
    obj.x4 = -1;
    obj.x8 = -1;
    c = S16Read(pbis);
    for (i = 0; i < c; i++) {
        int k = S8Read(pbis);
        struct IF *pif;
        if (k > 0)
            goto read;
        if (k < -2) {
        read:
            Read__18CBinaryInputStreamiPv(pbis, k * 2, as);
        }
        pif = pifParent;
        cid = S16Read(pbis);
        oid = S32Read(pbis);
        n = S16Read(pbis);
        cb = S32Read(pbis);
        if (k < -2)
            goto filter;
        if (k >= 0) {
            if (k != 0)
                goto filter;
            goto create;
        }
        {
            struct G *pg = &g_sw;
            int r;
            t = func_001C9940(pg->x3F10, -1);
            r = func_001C99D8(pg->x3F0C, 1, &t);
            if (k == -2) {
                if (PloFindSwNearest__FP2LO3OIDii(pg, 0x405, oid, 0, r)) {
                    goto skip;
                }
                obj.x4 = 1;
            } else {
                if (func_0015E958(pg, 0x805, oid, 0, r)) {
                    goto skip;
                }
                obj.x4 = 0;
            }
            obj.x8 = t;
            pif = &obj;
            goto create;
        }
        {
        filter:
            if (FFilterMatches__FiPs(k, as) == 0) {
                if (cid == 0x84 || cid == 0x85) {
                    plo1 = PloNew__F3CIDP2SW3OIDi(cid, psw, oid, -1);
                    if (cid == 0x84)
                        plo1->x50 = 1;
                    else
                        plo1->x50 = 1;
                    VCALL1(plo1, 14, pbis);
                    if (pifParent)
                        VCALL2(pifParent, 1, 1, &plo1);
                    continue;
                }
                goto skip;
            }
        }
    create:
        if (func_0015E988(cid, 6)) {
            LoadProxyFromBrx__FP2SWP3ALO3CID3OIDiP18CBinaryInputStreamP6LOSINK(&g_sw, psw, cid, oid, n, pbis, pif);
        } else {
            plo2 = PloNew__F3CIDP2SW3OIDi(cid, psw, oid, n);
            VCALL1(plo2, 14, pbis);
            if (pif)
                VCALL2(pif, 1, 1, &plo2);
        }
        continue;
    skip:
        Skip__18CBinaryInputStreami(pbis, cb);
    }
}
