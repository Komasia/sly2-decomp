struct LO { char pad[0x28]; unsigned long x28; char p1[0x120 - 0x30]; int x120; int x124; int x128; };
struct G { char pad[0xE94]; int c; int a[(0xFE8 - 0xE98) / 4]; int xFE8; };
static inline int Entry(const struct G*g,int i){int value;__asm__("lw %0,%1":"=r"(value):"m"(g->a[i]));return value;}
int func_001C26E0(void *p, struct LO *plo, struct G *g)
{
    int m, i, f1, f2, c, x1, x2;
    if (!((int)(plo->x28 >> 60) & 1)) return 0;
    m = (plo->x120 == 1) ? 3 : 2;
    if ((m & g->xFE8) != m) return 0;
    c = g->c;
    if (c > 0) {
        f1 = 0;
        f2 = 0;
        x1 = plo->x124;
        x2 = plo->x128;
        for (i = 0; i < c; i++) {
            int value=Entry(g,i);
            if (x1 == value) f1 = 1;
            if (x2 == value) f2 = 1;
            if (f1 && f2) break;
        }
        if (!f1 || !f2) return 0;
    }
    return 1;
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char list_predicate_layout[(sizeof(void*)==0x4 && sizeof(int)==0x4 && sizeof(unsigned long)==0x8 && sizeof(((struct G*)0)->a)==0x150 && OFF(struct LO,x28)==0x28 && OFF(struct LO,x120)==0x120 && OFF(struct LO,x124)==0x124 && OFF(struct LO,x128)==0x128 && OFF(struct G,c)==0xE94 && OFF(struct G,a)==0xE98 && OFF(struct G,xFE8)==0xFE8)?1:-1];
