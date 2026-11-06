struct VTE { short d; short p; void (*pfn)(void *); };
struct X { char pad[0xC]; VTE *pvt; };
struct Ref;
extern "C" void func_00259B48(Ref *, X *);
struct Ref {
    X *px;
    Ref &operator=(X *p) { func_00259B48(this, p); return *this; }
    operator X *() { return px; }
};
struct D { char pad[0x48]; int n48; char pad2[0x54 - 0x4C]; int n54; };
struct P { char pad[0x200]; Ref r200; char pad2[0x22C - 0x204]; X *a[6]; int n244; int n248; int n24C; };
struct G;
extern G g_sw;
extern char D_004435F0[];
extern "C" {
void StopDialog(P *, int) asm("StopDialog__FP8SOUNDMGR");
D *func_001FCFA0(P *, int);
X *PsndNewVoice(D *, int) asm("PsndNewVoice__FP9SNDSTREAMPv");
void SetDialogSubtitle(void *, int, int) asm("SetDialogSubtitle__FP9DIALOGSUBii");
X *func_0015ED78(G *, int, int, int);
int func_001FD0C0(P *, int);
X *func_001F67E0(X *, int);
}
// name: SafeHouse port (PsndStartDialog)
extern "C" X *PsndStartDialog__FP8SOUNDMGRii(P *p, int k, int f)
{
    D *pd;
    StopDialog(p, k);
    pd = func_001FCFA0(p, k);
    if (!pd) return 0;
    p->r200 = PsndNewVoice(pd, 0);
    p->n244 = 0;
    p->n248 = 0;
    p->n24C = 0;
    if (!f) SetDialogSubtitle(D_004435F0, k, pd->n48);
    if (pd->n48 != -1 && pd->n54) {
        register X *po __asm__("$19")=func_0015ED78(&g_sw, 5, pd->n48, 0);
        if (po) {
            register int i __asm__("$18")=0;
            register int primaryRole __asm__("$20")=3;
            register X **slot __asm__("$16")=p->a;
            for(;i<6;i++,slot++) {
                if(i==primaryRole)p->a[3]=po;
                else *slot=func_001F67E0(po,func_001FD0C0(p,i));
                { X *current=*slot;
                  if(current) { VTE &entry=current->pvt[1];
                    entry.pfn((char *)current+entry.d); } }
            }
        }
    }
    return p->r200;
}
