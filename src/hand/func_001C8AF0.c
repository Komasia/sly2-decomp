struct G { char pad[0x4764]; int a; int b; };
extern struct G g_sw;
struct H;
extern struct H D_003DD040;
struct S { char pad[0x190]; int n190; char pad2[0x64]; int n1f8; };
void SetVaultState__FP2LOi(struct S *p, int n);
void ShowClueCounter(struct G *pg) asm("ShowClueCounter__FP2SW");
void PsndStartDialog__FP8SOUNDMGRii(struct H *ph, int n, int m);
// name: SafeHouse port (UseVault)
void UseVault__FP2LOi(struct S *p, int n)
{
    struct G *pg = &g_sw;
    if (pg->a >= pg->b) {
        p->n190 = n;
        SetVaultState__FP2LOi(p, 1);
    } else {
        ShowClueCounter(pg);
        if (p->n1f8 != -1) PsndStartDialog__FP8SOUNDMGRii(&D_003DD040, p->n1f8, 1);
    }
}
