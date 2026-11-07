struct S { char pad[0x110]; unsigned char ab[26]; };
// name: SafeHouse port (SetAloXpBytes)
void SetAloXpBytes__FP3ALOUiUc(struct S *p, int f, int b)
{
    int i; int m;
    for (i = 0, m = 1; i < 26; i++) { if (m & f) p->ab[i] = b; m <<= 1; }
}
