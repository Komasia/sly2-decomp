struct CRef;
extern "C" void Decref(CRef *) asm("Decref__4CRef");
struct CRef {
    int tagk; int tag;
    CRef(int k, int n) { tagk = k; tag = n; }
    ~CRef() { Decref(this); }
};
struct VTE { short d; short pad; void *(*pfn)(void *); };
struct E { int id; int a; float g; };
struct P { char pad[0xC]; VTE *vt; char pad2[0x1180 - 0x10]; E ae[3]; };
struct CLOCK { float t; float dt; };
extern "C" {
extern CLOCK g_clock;
extern char D_002A4D50[];
extern char D_002A4D58[];
void SetAbilityState(P *p, E *pe, int n) asm("SetAbilityState__FP5ACTORP6ABSLOTi");
int fiprintf(char *pch, const char *fmt, ...) asm("fiprintf");
}
CRef SetProgressPoCurrent(const CRef &ref, void *o, const char *fmt, ...) asm("SetProgressPoCurrent__FP4CRefPci");
// name: SafeHouse port (SetActorAbilitySlot)
extern "C" void SetActorAbilitySlot__FP5ACTORii(P *p, unsigned int i, int id)
{
    if (i < 3) {
        E *pe = &p->ae[i];
        SetAbilityState(p, pe, -1);
        pe->id = id;
        pe->a = 0;
        pe->g = g_clock.t;
        for (int j = 0; j < 3; j++) {
            char ach[16];
            E *pe2 = &p->ae[j];
            if (j != i && pe2->id == id) {
                SetAbilityState(p, pe2, -1);
                pe2->id = -1;
            }
            fiprintf(ach, D_002A4D50, j);
            VTE *e = &p->vt[103];
            SetProgressPoCurrent(CRef(0x15, p->ae[j].id), e->pfn((char *)p + e->d), D_002A4D58, ach, 0);
        }
        VTE *e = &p->vt[105];
        ((void (*)(void *))e->pfn)((char *)p + e->d);
    }
}
