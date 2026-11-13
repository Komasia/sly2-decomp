// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
typedef struct { char pad[0x10]; int x10; char pad2[0x1C]; void *x30; } E;
typedef struct { char pad[0xE4]; E *xE4; } S;
typedef struct { int a, b; } P;
E *PvAllocSwImpl__Fi(P *); void InitEmitb__FP5EMITB(E *); void LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(S *, int); void LoadEmitmeshFromBrx(void *, int) asm("LoadEmitmeshFromBrx__FP8EMITMESHP18CBinaryInputStream"); void LoadEmitColorsFromBrx__FP7LOXEMITP18CBinaryInputStream(S *, int);
void LoadEmitterFromBrx__FP7EMITTERP18CBinaryInputStream(S *p, int x)
{
    P t;
    t.a = 0x100; t.b = 0x10;
    InitEmitb__FP5EMITB(p->xE4 = PvAllocSwImpl__Fi(&t));
    LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(p, x);
    if (p->xE4->x10 == 3) LoadEmitmeshFromBrx(p->xE4->x30, x);
    LoadEmitColorsFromBrx__FP7LOXEMITP18CBinaryInputStream(p, x);
}
