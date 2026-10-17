/* v3 (Claude agent nonvu10): aligned 23->19. Natural p->ap[i]/p->ap[j] indexing in a goto loop, `j != i`, and ONE `next` temp reused for both pb->next and p->ap[j] (removes the j copy). Left: p/ppb s3/s2 swap, j-path regs (target j*4 v1, next a0, ap[j] v0). */
struct B { int n0; int n4; struct B *next; };
struct S { int n0; int n4; int n8; struct B *ap[8]; };
int func_00170448(int n);
void func_001704B8(struct S *p);
int func_00170548(struct S *p, int cb)
{
    unsigned int i;
    int old;
    struct B *pb;
    int mask;
    i = func_00170448(cb - 1) + 1;
    mask = ~0x7F;
    goto test;
loop:
    pb = p->ap[i];
    if (pb) {
        old = pb->n0;
        pb->n0 = old + cb;
        if (pb->n0 == pb->n4) {
            p->ap[i] = pb->next;
        } else {
            unsigned int j = func_00170448(pb->n4 - pb->n0);
            if (j != i) {
                struct B *next = pb->next;
                p->ap[i] = next;
                next = p->ap[j];
                pb->next = next;
                p->ap[j] = pb;
            }
        }
        goto done;
    }
    i++;
test:
    if (i < 8) goto loop;
    if (((p->n4 + cb) & mask) != (p->n4 & mask)) func_001704B8(p);
    old = p->n4;
    p->n4 = old + cb;
done:
    return old;
}
