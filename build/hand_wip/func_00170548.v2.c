/* v2 (Claude agent, 2026-10-17): aligned 25->23. Byte-offset index temps (off = i*4, ppj = ap + j*4) fix loop-top order and addu operand order. Remaining: target keeps returned j in v0 (ours copies to v1, so next/ap[j] regs swap) and p/ppb in s3/s2 (ours s2/s3). */
struct B { int n0; int n4; struct B *next; };
struct S { int n0; int n4; int n8; struct B *ap[8]; int c; struct B ab[1]; };
int func_00170448(int n);
void func_001704B8(struct S *p);
int func_00170548(struct S *p, int cb) {
    unsigned int i;
    int old;
    int mask;
    i = func_00170448(cb - 1) + 1;
    mask = ~0x7F;
    goto test;
loop:
    {
        int off = i * 4;
        struct B **ap = p->ap;
        struct B **ppb = (struct B **)((char *)ap + off);
        struct B *pb = *ppb;
        if (pb) {
            unsigned int j;
            old = pb->n0;
            pb->n0 = old + cb;
            if (pb->n0 == pb->n4) {
                *ppb = pb->next;
            } else {
                j = func_00170448(pb->n4 - pb->n0);
                if (j != i) {
                    struct B **ppj = (struct B **)((char *)ap + j * 4);
                    *ppb = pb->next;
                    pb->next = *ppj;
                    *ppj = pb;
                }
            }
            goto done;
        }
        i++;
    }
test:
    if (i < 8) goto loop;
    if (((p->n4 + cb) & mask) != (p->n4 & mask)) func_001704B8(p);
    old = p->n4;
    p->n4 = old + cb;
done:
    return old;
}
