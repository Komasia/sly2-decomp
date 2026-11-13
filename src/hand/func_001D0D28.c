typedef int qword __attribute__((mode(TI)));
typedef struct VT { struct { short d; short pad; void (*pfn)(void *, float, qword, int); } a[4]; } VT;
typedef struct {
    char pad[0x18];
    float x18;
    int x1C;
    float x20;
    float x24;
    char pad28[0xEC - 0x28];
    VT *vt;
} EMIT;
typedef struct { char pad[0xE0]; int c; char *a; } Q;
typedef struct {
    char pad[0x70];
    qword x70;
    qword x80;
    char pad90[0xE0 - 0x90];
    Q *q;
    char pade4[0xF4 - 0xE4];
    int xF4;
} OBJ;
extern struct G g_sw;
typedef struct { qword pos; char rest[0x50]; } HIT;
int ClipSegmentSoe__FP3SOEG9VU_VECTORT1iP3LSG(void *, qword, qword, int, HIT *);
EMIT *FLaunchHudRip__FP2LOP6VECTORP7MATRIX3(struct G *, int, int);
void TouchRip(OBJ *, int) asm("TouchRip__FP3RIPi");
// name: SafeHouse port (TouchRipKind1)
void TouchRipKind1__FP4RIPNi(OBJ *p, int n)
{
    HIT hit;
    int i;
    EMIT *pe;
    if (n == 0 || p->xF4 == 0)
        goto done;
    hit.pos = p->x70;
    for (i = 0; i < p->q->c; i++) {
        if (ClipSegmentSoe__FP3SOEG9VU_VECTORT1iP3LSG(p->q->a + i * 0xB0, p->x80, p->x70, 1, &hit))
            goto found;
    }
found:
    pe = FLaunchHudRip__FP2LOP6VECTORP7MATRIX3(&g_sw, 7, 0);
    if (pe) {
        pe->vt->a[1].pfn((char *)pe + pe->vt->a[1].d, 40.0f, hit.pos, 0);
        pe->x18 = 0.75f;
        pe->x20 = 40.0f;
        pe->x24 = 30.0f;
        pe->x1C = p->xF4;
    }
done:
    TouchRip(p, n);
}
