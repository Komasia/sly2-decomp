extern char D_002DEB30[];
void func_001331F8(void *p, int n);
void func_001619A0(void *p, int n, void *q);
void func_001A61E0(void *p, int n)
{
    func_001331F8(p, n);
    switch (n) {
    case 5:
        func_001619A0(D_002DEB30, 0x1A, p);
        break;
    case 6:
        func_001619A0(D_002DEB30, 0x1B, p);
        break;
    }
}
