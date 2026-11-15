/* MarkProjectileSweep: the base contact marking (0x1F5990), then a sweeping projectile adds a contact of kind 9 with
 * the entry at a recorded sweep hit of the entry's root (its point and normal). Layout: SafeHouse port. */
typedef int qword __attribute__((mode(TI)));
struct SWEEP { qword pos; qword normal; float g; int plo; int pad[2]; };   /* a sweep hit */
struct BOMB { char pad[0xE4]; int psoe; char pad2[0x1F4 - 0xE8]; int fSweep; int csweep; struct SWEEP *asweep; };   /* field: SafeHouse port (projectile.cpp) */
struct OXA { char pad[0x60]; int pso; };
struct SO { char pad[0xEC]; struct OXA *poxa; };
struct SOE { int x0; struct SO *pso; };
struct SW { int x; };
extern struct SW g_sw;
void func_001F5990(struct BOMB *pbomb, struct SOE *psoe, int a2, int a3, int a4, int a5);
void PxpAddSw__FP3SOET0P6VECTORG9VU_VECTORT3iiiPvf(struct SW *psw, int n, struct SOE *psoe, qword a, qword b, int k, int x, int y, float g, int z);
// name: SafeHouse port (MarkProjectileSweep)
void MarkProjectileSweep__FP3ALOP3SOEiiii(struct BOMB *pbomb, struct SOE *psoe, int a2, int a3, int a4, int a5)
{
    func_001F5990(pbomb, psoe, a2, a3, a4, a5);
    if (pbomb->fSweep) {
        struct SWEEP *pe;
        for (pe = pbomb->asweep; pe < pbomb->asweep + pbomb->csweep; pe++) {
            if (pe->plo == psoe->pso->poxa->pso) {
                PxpAddSw__FP3SOET0P6VECTORG9VU_VECTORT3iiiPvf(&g_sw, pbomb->psoe, psoe, pe->pos, pe->normal, 9, 0, 0, pe->g, a5);
                return;
            }
        }
    }
}
