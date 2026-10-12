struct S { char pad[0xE8]; int c; };
int func_001BC530(struct S *p, int n)
{
    int c = p->c;
    int r = n % c;
    if (r < 0) r = r + (c - 1);
    else if (r == c - 1) r = 0;
    return r;
}
