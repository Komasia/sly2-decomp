struct S { char pad[0x4154]; void *a[256]; int x4554; int x4558, x455c; int x4560; void *x4564; int x4568, x456c; char x4570[0x20]; };
void func_002333B4(void *p, int c, int n);
void func_001A3D00(struct S *s, void *p);
void func_001A3EE8(struct S *s)
{
    unsigned int i;
    if (s->x4554) {
        s->x4554 = 0;
        func_002333B4(s->x4570, 0, 0x20);
        func_002333B4(s->x4564, 0, s->x4560 << 5);
        for (i = 0; i < 0x100; i++) {
            if (s->a[i])
                func_001A3D00(s, s->a[i]);
        }
    }
}
