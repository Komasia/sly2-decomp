struct B { int a[20]; };
void func_001ABB10(void *a, void *b, struct B *pb);
void func_001AC900(void *a, struct B *pb, void *b, int n);
void FUN_0018d2e8(void *a, void *b)
{
    struct B buf;
    func_001ABB10(a, b, &buf);
    func_001AC900(a, &buf, b, 0x5408);
}
