struct DLE { void *next; void *prev; };
struct R { char pad[0x10]; char dl[0xC]; };
struct Q { char pad[0x20]; struct R *pr; char p1[0x3C]; struct DLE dle; };
struct E { int a; int b; int c; int d; char p[0xC]; int x1c; float g; int x24; int x28; float h; };
struct S { char pad[0x1C8]; int c; struct E ae[4]; struct Q *pqFirst; };
void ResetHackSoBase__FP2LO(struct S *p);
void ClearDle__FP3DLE(struct DLE *pdle);
void AppendDlEntry__FP2DLPv(void *pdl, void *pv);
void ClearDl__FP2DL(void *pdl);
void ResetSwarmEnt__FP2LOP5SWENT(struct S *p, struct E *pe);
// name: SafeHouse port (ResetSwarm)
void ResetSwarm__FP2LO(struct S *p)
{
    struct Q *q;
    int i;
    ResetHackSoBase__FP2LO(p);
    q = p->pqFirst;
    while (q) {
        struct Q *qNext = (struct Q *)q->dle.next;
        ClearDle__FP3DLE(&q->dle);
        AppendDlEntry__FP2DLPv(q->pr->dl, q);
        q = qNext;
    }
    ClearDl__FP2DL(&p->pqFirst);
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        pe->d = pe->b;
        ResetSwarmEnt__FP2LOP5SWENT(p, pe);
    }
}
