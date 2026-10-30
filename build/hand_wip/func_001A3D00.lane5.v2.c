typedef int qword __attribute__((mode(TI)));
struct NODE {qword plane;struct NODE*left,*right;int leftLeaf,rightLeaf;};
struct O { char pad[0xE0]; int xE0; char pad2[0x118 - 0xE4]; int x118; char pad3[0x15C - 0x11C]; int x15C; int x160; int pad4; float x168; };
struct S { char pad[0x4154]; struct O *x4154[0x100]; int x4554;int word4558;struct NODE*x455C;int word4560;void *leaves;int word4568,word456C; int x4570[8]; unsigned int x4590[8]; };
qword func_001A62E8(void *p);
void func_001A3B80(struct S *s, struct NODE*n, qword pos, float r, int bit);
static __inline__ void SetBit(int *a, int bit) { int *pw = &a[bit / 32]; int m = 1 << bit; *pw |= m; }
void func_001A3D00(struct S *s, struct O *o)
{
    if (o->x118 < 0) {
        unsigned int i;
        unsigned int w, b, old;
        int n, n1, n2, n3, n4;
        for (i = 0; ; i++) {
            if (i >= 8)
                return;
            w = s->x4590[i];
            if (!w)
                continue;
            w &= -w; b = w;
            old = s->x4590[i];
            n = i * 32;
            __asm__ __volatile__("" :: "m"(s->x4590[i]) : "memory");
            if (b & 0xAAAAAAAA) n += 1;
            if (b & 0xCCCCCCCC) n += 2;
            if (b & 0xF0F0F0F0) n += 4;
            if (b & 0xFF00FF00) n += 8;
            {
            int slot = (b & 0xFFFF0000U) ? n + 16 : n;
            s->x4590[i] = old & ~b;
            *(struct O**)((char*)s+slot*4+0x4154)=o;
            o->x118=slot;
            }
            break;
        }
    }
    if (s->x4554)
        return;
    if (o->x15C)
        return;
    if (!o->xE0 || o->x160 || !s->x455C)
        SetBit(s->x4570, o->x118);
    else
        func_001A3B80(s, s->x455C, func_001A62E8(o), o->x168, o->x118);
}
