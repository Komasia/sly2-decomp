struct LO { char pad[0x124]; int x124; char p1[0x150 - 0x128]; int x150; };
struct AL { int cb; int cbAlign;  };
struct S { char pad[0x10]; int c; int *aid; struct LO **aplo; int x1C; int c2; struct LO **aplo2; int x28; int x2C; };
extern char D_003DD490[];
struct LO *func_0015E938(void *p, int a, int id, void *scope);
int func_0015E9C8(void *p, int a, int b, void *scope, int d, struct LO **ap);
void *func_001AE238(const struct AL *pal, const void *pv);
static __inline__ void*QueryScope(void){register void*value __asm__("$7");__asm__("daddu %0,$zero,$zero":"=r"(value));return value;}
void func_001C1138(struct S *p)
{
    int i,n;register int c __asm__("$6");
    struct LO *ap[0x400];
    struct AL al;
    for (i = 0; i < p->c; i++) {
        struct LO *plo = func_0015E938(D_003DD490, 5, p->aid[i], 0);
        plo->x124 = i;
        p->aplo[i] = plo;
    }
    n = func_0015E9C8(D_003DD490, 0x205, 0x7C, QueryScope(), 0x400, ap);
    {register int alignment __asm__("$7")=0x10;
    c = 0x400;
    if (n < 0x400) c = n;
    al.cb = c * sizeof(struct LO *);
    (&al)->cbAlign = alignment;
    p->c2 = c;
    p->aplo2 = (struct LO**)func_001AE238(&al, ap);}
    {
        int j;
        for (j = 0; j < p->c2; j++) p->aplo2[j]->x150 = j;
    }
    p->x2C = 1;
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char actor_layout[(sizeof(void*)==4 && sizeof(int)==4 && sizeof(struct AL)==8 && OFF(struct AL,cb)==0 && OFF(struct AL,cbAlign)==4 && OFF(struct LO,x124)==0x124 && OFF(struct LO,x150)==0x150 && OFF(struct S,c)==0x10 && OFF(struct S,aid)==0x14 && OFF(struct S,aplo)==0x18 && OFF(struct S,c2)==0x20 && OFF(struct S,aplo2)==0x24 && OFF(struct S,x2C)==0x2C)?1:-1];
