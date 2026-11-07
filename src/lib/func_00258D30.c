// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef struct { char pad[0xE4]; char *xE4; } S;
extern char D_002DE750[];
void SetKind1Payload(S *, int); int *OffKind1(S *, int);
void *func_00258D30(S *p, int x)
{
    int *r;
    if (x == 1) { SetKind1Payload(p, 8); r = (int *)(p->xE4 + 0xC0); }
    else r = OffKind1(p, x);
    if (*r != 8) return D_002DE750;
    return (char *)r + 0x30;
}
