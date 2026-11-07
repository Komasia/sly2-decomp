typedef struct { float x, y, z; } VEC3;
struct S { char pad[0x240]; VEC3 v; };
extern char D_002BE990[];
void LoadPoFromBrx__FP2POP18CBinaryInputStream(struct S *p);
void BindLoParts__FP3ALOiPv(struct S *p, int n, void *pv);
void LoadJtFromBrx__FP2JTP18CBinaryInputStream(struct S *p)
{
    VEC3 *pv;
    LoadPoFromBrx__FP2POP18CBinaryInputStream(p);
    pv = &p->v;
    pv->x = 0.0f;
    pv->y = 0.0f;
    pv->z = -75.0f;
    BindLoParts__FP3ALOiPv(p, 0xAD, D_002BE990);
}
