typedef struct OBJ OBJ;
typedef struct { short d; short pad; void (*pfn)(void *, int); } VTE;
typedef struct { char pad[0x103C]; float x; float y; float g; } Q;
struct OBJ {
    char pad[0xC];
    VTE *vt;
    Q *q;
    char pad14[0x28 - 0x14];
    int n;
};
float atan2f(float, float);
// name: SafeHouse port (UpdateShopStick)
void UpdateShopStick__FP4SHOP(OBJ *p)
{
    Q *q = p->q;
    int n;
    float g;
    if (q == 0)
        return;
    n = p->n;
    g = q->g;
    if (n == -1) {
        if (0.8f < g) {
            int k = (int)(atan2f(q->y, q->x) * 1.2732395f + 8.5f);
            p->vt[14].pfn((char *)p + p->vt[14].d, k % 8);
        }
    } else if (g < 0.5f) {
        p->vt[14].pfn((char *)p + p->vt[14].d, -1);
    }
}
