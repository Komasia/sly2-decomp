struct S { int n0; unsigned char b4; unsigned char b5; };
// name: SafeHouse port (CclutPass)
int CclutPass__FP3SHD(struct S *p)
{
    switch (p->b4) {
    case 1:
        return 2;
    case 7:
        if (!(p->b5 & 0x20)) return 3;
        return 2;
    }
    return 1;
}
