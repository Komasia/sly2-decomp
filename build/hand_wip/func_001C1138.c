struct LO { char pad[0x124]; int x124; char p1[0x150 - 0x128]; int x150; };
struct AL { int cb; int cbAlign;  };
struct S { char pad[0x10]; int c; int *aid; struct LO **aplo; int x1C; int c2; struct LO **aplo2; int x28; int x2C; };
extern char D_003DD490[];
struct LO *func_0015E938(void *p, int a, int id, int b);
int func_0015E9C8(void *p, int a, int b, int c, int d, struct LO **ap);
struct LO **func_001AE238(struct AL *pal, void *pv);
void func_001C1138(struct S *p)
{
    int i,n;register int c __asm__("$6");
    struct LO *ap[0x400];
    struct AL al;
    struct AL *pal;
    for (i = 0; i < p->c; i++) {
        struct LO *plo = func_0015E938(D_003DD490, 5, p->aid[i], 0);
        plo->x124 = i;
        p->aplo[i] = plo;
    }
    n = func_0015E9C8(D_003DD490, 0x205, 0x7C, 0, 0x400, ap);
    {register int alignment __asm__("$7")=0x10;
    c = 0x400;
    if (n < 0x400) c = n;
    pal = &al;
    pal->cb = c * sizeof(struct LO *);
    pal->cbAlign = alignment;
    p->c2 = c;
    p->aplo2 = func_001AE238(pal, ap);}
    {
        int j;
        for (j = 0; j < p->c2; j++) p->aplo2[j]->x150 = j;
    }
    p->x2C = 1;
}
