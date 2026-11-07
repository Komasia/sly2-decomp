struct I { int x0; int x4; int x8; int xC; int x10; int x14; };
struct A { char pad[0x158]; struct I *pi; void *p15C; void *p160; };
struct Q { char pad[0x11A8]; struct A *pa; };
struct P { char pad[0x188]; int x188; int x18C; int x190; struct A *pa; };
extern int D_003E0F9C;
extern char D_003DA0C0[];
extern char g_game[];
int FIsBasicDerivedFrom__FP5BASIC3CID(struct Q *q, int k);
void func_001DA4B8(void *pv, int n, float g);
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *pv, int n);
void BroadcastTaskEvent__FP2SWiP2LO(void *pv, int n, struct P *p);
void SaveBootyMove__FP5ACTORiP2LO(struct Q *q, int n, struct P *p);
void SetBootyState__FP2LOi(struct A *pa, int n);
void UseObjectBase__FP2LOi(struct P *p, struct Q *q);
// name: SafeHouse port (FUseBootyStand)
void FUseBootyStand__FP2LOP5ACTOR(struct P *p, struct Q *q)
{
    struct A *pqa, *ppa;
    if (!FIsBasicDerivedFrom__FP5BASIC3CID(q, 0x34))
        return;
    pqa = q->pa;
    ppa = p->pa;
    if (!pqa && !ppa)
        return;
    if (ppa && D_003E0F9C && !ppa->pi->x10) {
        func_001DA4B8(D_003DA0C0, 0x124, 15.0f);
        SetSource__4CSndPv(PsndNewPlain__Fi(0x36), 0);
        return;
    }
    if (p->x190 || (pqa && pqa->pi->x14 != p->x188)) {
        BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x32, p);
        return;
    }
    if (p->pa)
        SetSource__4CSndPv(PsndNewPlain__Fi(0x27), 0);
    SaveBootyMove__FP5ACTORiP2LO(q, 0, p);
    if (q->pa && p->pa) {
        q->pa->p15C = p;
        SetBootyState__FP2LOi(q->pa, 3);
        p->pa->p160 = q;
        SetBootyState__FP2LOi(p->pa, 2);
    } else if (q->pa) {
        q->pa->p15C = p;
        SetBootyState__FP2LOi(q->pa, 3);
    } else {
        p->pa->p160 = q;
        SetBootyState__FP2LOi(p->pa, 2);
    }
    UseObjectBase__FP2LOi(p, q);
}
