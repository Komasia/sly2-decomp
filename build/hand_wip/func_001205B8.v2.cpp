// v2 (Claude agent, 2026-10-17): aligned 19 -> 11. Case 0x20 as `else if (pa->n8 != pb->n8) f = 0; else {calls}` plus case 0x22 as `else { f = 0; if (n8 == n8) f = nC == nC; }` gives the target outer-mismatch -> 0x20 f=0 merge. Left: case 0x15 xor/sltiu tail is cross-jumped into 0x22 (target keeps it separate).
// CRef equal? (recursive). 62 diff, but all from branch/cross-jump layout: target merges the outer tagk-mismatch f=0 with
// case 0x20 n8-mismatch f=0 block and does NOT cross-jump case 0x15 xor/sltiu tail into case 0x22; ours does the opposite.
// Everything else (frame, temps, ctor/dtor order) is identical.
struct NODE;
struct CRef {
    int m_tagk;
    union { int n; void *pv; NODE *pnode; struct W *pw; struct X *px; } u;
    CRef() { m_tagk = -1; }
    CRef(int n, int tagk) { u.n = n; m_tagk = tagk; }
    CRef(NODE *p);                  /* 0x129480 */
    CRef(const CRef &r);            /* 0x1291A8 */
    void Decref();                  /* 0x129EC8 */
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r); /* 0x129658 */
};
struct NODE { int cref; int n4; CRef ref; NODE *pnext; };
struct W { int cref; int n4; int n8; CRef ref; int n14; NODE *pnext; };
struct X { int cref; int n4; int n8; int nC; };

extern "C" CRef func_001205B8(const CRef &a, const CRef &b);
CRef func_001205B8(const CRef &a, const CRef &b)
{
    int f;
    if (a.m_tagk != b.m_tagk) {
        f = 0;
    } else {
        switch (a.m_tagk) {
        case 0x1F: {
            NODE *pa = a.u.pnode;
            NODE *pb = b.u.pnode;
            if (pa == pb) {
                f = 1;
            } else if ((pa->pnext == 0) != (pb->pnext == 0)) {
                f = 0;
            } else {
                CRef r;
                r = func_001205B8(pa->ref, pb->ref);
                if (r.u.n == 0) {
                    f = 0;
                } else if (pa->pnext == 0) {
                    f = 1;
                } else {
                    CRef ra(pa->pnext);
                    CRef rb(pb->pnext);
                    r = func_001205B8(ra, rb);
                    f = r.u.n;
                }
            }
            break;
        }
        case 0x20: {
            W *pa = a.u.pw;
            W *pb = b.u.pw;
            if (pa == pb) {
                f = 1;
            } else if (pa->ref.m_tagk != pb->ref.m_tagk) {
                f = 0;
            } else if (pa->ref.u.n != pb->ref.u.n) {
                f = 0;
            } else if (pa->n8 != pb->n8) {
                f = 0;
            } else {
                CRef ra(pa->pnext);
                CRef rb(pb->pnext);
                f = func_001205B8(ra, rb).u.n;
            }
            break;
        }
        case 0x15: case 0x17: case 0x18: case 0x19: case 0x21:
            f = a.u.n == b.u.n;
            break;
        case 0x22: {
            X *pa = a.u.px;
            X *pb = b.u.px;
            if (pa == pb) {
                f = 1;
            } else {
                f = 0;
                if (pa->n8 == pb->n8)
                    f = pa->nC == pb->nC;
            }
            break;
        }
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
        case 19: case 20: case 0x24:
            f = 1;
            break;
        }
    }
    return CRef(f, 0x17);
}
