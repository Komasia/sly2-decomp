typedef struct { short d; short pad; void *pfn; } VTE;
struct O { char pad[0xC]; VTE *vt; };
struct S { char pad[0xC]; struct O *po; int k; };
struct G { char pad[0x60]; float x; float y; };
extern struct G g_cm;
float atan2f(float y, float x);
#define VCALL31(o) ((float *(*)(void *))(o)->vt[31].pfn)((char *)(o) + (o)->vt[31].d)
// name: SafeHouse port (RadTargetrec)
float RadTargetrec__FP9TARGETREC(struct S *p)
{
    float r = 0.0f;
    switch (p->k) {
    case 0:
        r = atan2f(g_cm.y, g_cm.x);
        break;
    case 1: {
        float *a = VCALL31(p->po);
        float *b = VCALL31(p->po);
        r = atan2f(a[1], b[0]);
        break;
    }
    case -1:
        break;
    }
    return r;
}
