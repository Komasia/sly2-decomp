typedef unsigned long ulong;
struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { struct VTE a[42]; };
struct A { char pad[0xC]; struct VT *pvt; };
struct L { char pad[0x24]; struct L *next; ulong fl; char pad2[0x64 - 0x30]; struct L *first; char pad3[0x70 - 0x68]; struct L *end; };
void PloCloneLo__FP2LOi(struct L *, struct A *);
// name: SafeHouse port (CloneAlo 0x1F66F0) + Sly 1 CloneAlo
void CloneAlo(struct A *pa, struct L *p) asm("CloneAlo__FP3ALOT0");
void CloneAlo(struct A *pa, struct L *p)
{
    struct L *q;
    pa->pvt->a[41].pfn((char *)pa + pa->pvt->a[41].d);
    for (q = p->first; q != p->end; q = q->next)
        if (!(q->fl & (1L << 57))) PloCloneLo__FP2LOi(q, pa);
}
