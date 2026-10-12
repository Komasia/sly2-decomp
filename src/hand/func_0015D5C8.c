extern int *D_002BE1B8[];
extern int *D_002BE080[];
struct S { char pad[0x110]; int n110; int pad114[2]; int n11C; int n120; int pad124; int n128; };
int func_0015D5C8(struct S *p)
{
    int k = p->n11C;
    if (k == -1)
        return -1;
    if (k == 8 && p->n120 != -1)
        return D_002BE1B8[p->n128][p->n120];
    return D_002BE080[p->n110][p->n11C];
}
