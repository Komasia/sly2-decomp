/* Complete world-slot allocation and spatial-mask update. */
typedef int qword __attribute__((mode(TI)));
struct NODE {qword plane;struct NODE*left,*right;int leftLeaf,rightLeaf;};
typedef union{qword q[2];unsigned words[8];}MASK;
struct O { char pad[0xE0]; int xE0; char pad2[0x118 - 0xE4]; int x118; char pad3[0x15C - 0x11C]; int x15C; int x160; int pad4; float x168; };
struct S { char pad[0x4154]; struct O *x4154[0x100]; int x4554;int word4558;struct NODE*x455C;int word4560;MASK*leaves;int word4568,word456C; int x4570[8]; unsigned int x4590[8]; };
qword func_001A62E8(void *p);
void func_001A3B80(struct S *s, struct NODE*n, qword pos, float r, int bit);
static inline unsigned BitMask(int bit){unsigned value=1;__asm__("sllv %0,%0,%1":"+r"(value):"r"(bit));return value;}
static __inline__ void SetBit(int *a, int bit) { int *pw = &a[bit / 32]; *pw |= BitMask(bit); }
static inline unsigned ReadWord(const unsigned*p){unsigned word;__asm__("lw %0,%1":"=r"(word):"m"(*p));return word;}
void func_001A3D00(struct S *s, struct O *o)
{
    if (o->x118 < 0) {
        unsigned int i;
        unsigned int w, b;
        int n;
        for (i = 0; ; i++) {
            if (i >= 8)
                return;
            w = s->x4590[i];
            if (!w)
                continue;
            w &= -w;b=w;
            n = i * 32;
            if (b & 0xAAAAAAAA) n += 1;
            if (b & 0xCCCCCCCC) n += 2;
            if (b & 0xF0F0F0F0) n += 4;
            if (b & 0xFF00FF00) n += 8;
            {int slot=n+16;if(!(b&0xFFFF0000U))slot=n;
            s->x4590[i]=ReadWord(&s->x4590[i])&~b;
            *(struct O**)((char*)s+slot*4+0x4154)=o;
            o->x118=slot;
            }
            break;
        }
    }
found:
    if (s->x4554)
        return;
    if (o->x15C)
        return;
    if (!o->xE0 || o->x160 || !s->x455C)
        SetBit(s->x4570, o->x118);
    else
        func_001A3B80(s, s->x455C, func_001A62E8(o), o->x168, o->x118);
}

typedef char offset_0_xE0[(unsigned)&((struct O*)0)->xE0==224?1:-1];
typedef char offset_0_x118[(unsigned)&((struct O*)0)->x118==280?1:-1];
typedef char offset_0_x15C[(unsigned)&((struct O*)0)->x15C==348?1:-1];
typedef char offset_0_x160[(unsigned)&((struct O*)0)->x160==352?1:-1];
typedef char offset_0_x168[(unsigned)&((struct O*)0)->x168==360?1:-1];
typedef char offset_1_x4154[(unsigned)&((struct S*)0)->x4154==16724?1:-1];
typedef char offset_1_x4554[(unsigned)&((struct S*)0)->x4554==17748?1:-1];
typedef char offset_1_x455C[(unsigned)&((struct S*)0)->x455C==17756?1:-1];
typedef char offset_1_leaves[(unsigned)&((struct S*)0)->leaves==17764?1:-1];
typedef char offset_1_x4570[(unsigned)&((struct S*)0)->x4570==17776?1:-1];
typedef char offset_1_x4590[(unsigned)&((struct S*)0)->x4590==17808?1:-1];
typedef char offset_2_plane[(unsigned)&((struct NODE*)0)->plane==0?1:-1];
typedef char offset_2_left[(unsigned)&((struct NODE*)0)->left==16?1:-1];
typedef char offset_2_right[(unsigned)&((struct NODE*)0)->right==20?1:-1];
typedef char offset_2_leftLeaf[(unsigned)&((struct NODE*)0)->leftLeaf==24?1:-1];
typedef char offset_2_rightLeaf[(unsigned)&((struct NODE*)0)->rightLeaf==28?1:-1];
typedef char size_0[sizeof(struct O)==364?1:-1];
typedef char size_1[sizeof(struct S)==17840?1:-1];
typedef char size_2[sizeof(struct NODE)==32?1:-1];
typedef char size_3[sizeof(MASK)==32?1:-1];
typedef char size_4[sizeof(int)==4?1:-1];
typedef char size_5[sizeof(unsigned)==4?1:-1];
typedef char size_6[sizeof(void*)==4?1:-1];
typedef char size_7[sizeof(qword)==16?1:-1];
typedef char align_0[__alignof__(struct O)==4?1:-1];
typedef char align_1[__alignof__(struct S)==4?1:-1];
typedef char align_2[__alignof__(struct NODE)==16?1:-1];
typedef char align_3[__alignof__(MASK)==16?1:-1];
typedef char align_4[__alignof__(qword)==16?1:-1];
