struct B { char pad[0x40]; float g40; float g44; char pad2[0xC0 - 0x48]; };
int func_001BF3D8(void *a, void *b, void *c, int d, struct B *pb, int f);
int func_001BF900(void *a, void *b, void *c, int f2)
{
    struct B buf;
    int f = func_001BF3D8(a, b, c, 2, &buf, f2 | 2);
    int r = 0;
    if (!f || buf.g40 != 0.0f || buf.g44 != 1.0f) r = 1;
    return r;
}
