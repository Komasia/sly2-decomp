typedef struct VECTOR { float x, y, z, w; } __attribute__((aligned(16))) VECTOR;
struct E { VECTOR *pv; short a; short b; };
struct S { int c0; struct E *ae; int c8; VECTOR *av; int c10; int *a14; void *x18; };
struct A { int cb; int align; };
int U32Read(void *pbis) asm("U32Read__18CBinaryInputStream");
int U16Read(void *pbis) asm("U16Read__18CBinaryInputStream");
void ReadVector4__18CBinaryInputStreamP7VECTOR4(void *pbis, VECTOR *pv);
int S32Read(void *pbis) asm("S32Read__18CBinaryInputStream");
void *PvAllocSwImpl__Fi(struct A *pa);
void *PvAllocSwClearImpl__Fi(struct A *pa);
void func_001C0F30(struct S *p, int c, void *pbis)
{
    struct A a;
    int i, j;
    p->c0 = c;
    p->c8 = U32Read(pbis);
    p->c10 = U32Read(pbis);
    a.cb = p->c0 * 8;
    a.align = 0x10;
    p->ae = PvAllocSwImpl__Fi(&a);
    a.cb = p->c8 * 16;
    a.align = 0x10;
    p->av = PvAllocSwImpl__Fi(&a);
    a.cb = p->c10 * 4;
    a.align = 0x10;
    p->x18 = PvAllocSwClearImpl__Fi(&a);
    a.cb = p->c10 * 4;
    a.align = 0x10;
    p->a14 = PvAllocSwImpl__Fi(&a);
    for (i = 0; i < p->c0; i++) {
        struct E *pe = &p->ae[i];
        pe->pv = &p->av[U16Read(pbis)];
        pe->a = U16Read(pbis);
        pe->b = U16Read(pbis);
    }
    for (j = 0; j < p->c8; j++)
        ReadVector4__18CBinaryInputStreamP7VECTOR4(pbis, &p->av[j]);
    for (j = 0; j < p->c10; j++)
        p->a14[j] = S32Read(pbis);
}
