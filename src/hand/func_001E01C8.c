struct S { char pad[0x50]; int n50; int n54; int n58; char pad2[0x80-0x5C]; int n80; };
void func_001E01C8(struct S *p, int n)
{
    if (n > 0) {
        if (n < 0x200 && p->n50 < 2) {
            p->n58 = n;
            p->n80 = 1;
        }
    }
}
