typedef struct { unsigned char r, g, b, a; } RGBA;
typedef struct { int n; RGBA ac[1]; } LIST;
typedef struct { char pad[0xC]; int xC; char pad2[0xC]; LIST *x1C; } Y;
typedef struct { char pad[0xC0]; Y y; } T;
typedef struct { char pad[0xE4]; T *xE4; } X;
typedef struct { int cb; int align; } DESC;
int U16Read(void *) asm("U16Read__18CBinaryInputStream");
int U8Read(void *) asm("U8Read__18CBinaryInputStream");
int U32Read(void *) asm("U32Read__18CBinaryInputStream");
void AdjustRgba__FPUi(RGBA *);
void *PvAllocSwImpl__Fi(DESC *);

static inline int Min(int a, int b) { return a < b ? a : b; }

void func_00258F40(X *p, void *ps)
{
    int n = U16Read(ps);
    int i;
    Y *y;
    LIST *l;
    union { DESC d; RGBA c; } u;
    if (n == 0)
        return;
    y = &p->xE4->y;
    u.d.cb = n * 4 + 4;
    u.d.align = 0x10;
    l = PvAllocSwImpl__Fi(&u.d);
    y->x1C = l;
    y->xC = U8Read(ps);
    l->n = Min(n, 32);
    for (i = 0; i < n; i++) {
        *(int *)&u.c = U32Read(ps);
        AdjustRgba__FPUi(&u.c);
        if (i < l->n)
            l->ac[i] = u.c;
    }
}
