/* WIP: structure right; target increments i (s2) separately inside each branch and reloads palo->a / pe->id inside the search loop. */
struct LO;
typedef struct { short d; short pad; void (*pfn)(struct LO *); } VTE;
struct LO { int x0, x4, x8; VTE *vt; };
struct SUB { char pad[0x9C]; int x9C; char pad2[0x100 - 0xA0]; };
struct ALO { char pad[0x50]; int c; struct SUB *a; };
struct E { int grf; int id; int ib; };
extern char D_003DD490[];
void *func_001F6030(struct ALO *p, int id);
void func_001F2AD0(struct ALO *p);
void *func_001F5FF8(struct ALO *p, int id);
void func_001F69F8(struct ALO *p, int id);
struct LO *func_0015E938(void *g, int grf, int id, struct ALO *p);
void func_001A64E8(struct ALO *palo, int c, struct E *ae)
{
    int i;
    for (i = 0; i < c; i++) {
        struct E *pe = &ae[i];
        int grf = pe->grf;
        if (grf & 0x10) {
            int j = palo->c;
            while (--j >= 0) {
                struct SUB *p = &palo->a[j];
                if (p->x9C == pe->id) {
                    *(void **)((char *)palo + pe->ib) = p;
                    break;
                }
            }
        } else if (grf & 0x20) {
            void *p = func_001F6030(palo, pe->id);
            if (p) {
                *(void **)((char *)palo + pe->ib) = p;
                if (pe->grf & 0x200)
                    func_001F2AD0(palo);
            }
        } else if (grf & 0x40) {
            void *p = func_001F5FF8(palo, pe->id);
            if (p) {
                *(void **)((char *)palo + pe->ib) = p;
                if (pe->grf & 0x200)
                    func_001F69F8(palo, pe->id);
            }
        } else {
            int k;
            struct LO *p;
            if (grf & 2)
                k = 4;
            else
                k = (grf & 1) ? 5 : 1;
            p = func_0015E938(D_003DD490, (pe->grf & 0x400) ? k | 0x400 : k, pe->id, palo);
            if (p) {
                if (pe->grf & 0x200)
                    p->vt[9].pfn((struct LO *)((char *)p + p->vt[9].d));
                *(void **)((char *)palo + pe->ib) = p;
            }
        }
    }
}
