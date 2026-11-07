struct S { char pad[0x84]; int a84[3]; int n90; int n94; int n98; int n9C; };
extern char g_cm[];
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(void *a, int b, int c, void *d, int e, void *f);
// name: SafeHouse port (EndRunCamera)
void EndRunCamera__FP3RUNi(struct S *p, int n)
{
    p->n90 = n;
    p->n9C = 0;
    RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(g_cm, 2, 10, g_cm + 0x500, 0, p->a84);
}
