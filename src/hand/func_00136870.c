/* MATCH (Claude agent laneB13, 2026-10-23), from v4 (4). One register pin (f in v1) plus commented empty asms that emulate the original toolchain's reorg/cross-jump state: case 12 has its own `return 0` (with an empty asm so it isn't merged with the shared fail), the shared fail has one too, the 1CADE0 path ends in `return 0`, and an empty asm using pabil in the pv != 0 block keeps v0 live so reorg annuls the beql slot. */
/* FBentleyAbilityOk (vt slot 99): may Bentley start the action k: not with abilities off (+0x1818) or the binocucom
 * up; by state: the ground states, the jump / interaction / climb when they allow it, the throw (12) only for the
 * selected gadget's own kind; then the gadget abilities (4, 5, 7, 9, 11, 13) when the thrown one is flying or landed
 * (0x224590) or its proxy has a free row, the binocucom (3) when the pad allows it and no default camera is on top,
 * and 1, 2, 8, 10, 12, 14 always. Layout: SafeHouse port (gang.cpp FBentleyCanDo, gang.h BENTLEY / ABILITY). */
/* v4 (Claude agent laneB12, 2026-10-23): aligned 10 -> 4. f pinned to v1 (one commented pin) and used for case 12's kind and the IrowProxyChoose__FP2SWi result; cases 2/3/13 test their call results directly; an empty volatile asm "+r"(f) after the 1CADE0 call keeps the target's `daddu v1,v0; bnez v1` (cse otherwise tests v0). Left: reorg fill choices: case 12 beq slot (target steals li v0,1 from `one`, ours takes li v0,0 from the fallthrough; `if (f != k) goto fail` flips the layout: 4), and the pv == 0 test (target beql, ours beqz). */
/* v3 (Claude agent, 2026-10-17): aligned 10. Shared function-scope `void *pv` for case 12 pcarrySelected and pabil->plo4 puts pa in a0 like the target. Left: target loads kind into v1 and copies the 1CADE0 result to v1 (daddu v1,v0; bnez v1). */
struct CARRY { char pad[0x15C]; int kind; };   /* field: SafeHouse port (CARRY kind) */
struct ABILITY { int id; void *plo4; void *plo8; };   /* field: SafeHouse port */
struct BENTLEY { char pad[0x2C0]; char jump[0x200]; char interact[0xF50 - 0x4C0]; char climb[0x11B4 - 0xF50]; int nJtthrowState; int pad1[2];
    struct CARRY *pcarrySelected; char pad2[0x12F0 - 0x11C4]; int f12F0; char pad3[0x13D0 - 0x12F4]; int state; char pad4[0x1818 - 0x13D4];
    long f1818; };
extern int g_grfjoyt;
extern char D_002DE2E0[];
int func_001443D8();
int func_0019C8D0(void *pv, int k);
int FInteractCanDo__FP5ACTORi(void *pv, int k);
int func_0019EEF0(void *pv, int k);
struct ABILITY *CbFromSaak(struct BENTLEY *pbentley, int k) asm("CbFromSaak__F4SAAK");
int func_00224590(void *pv);
int IrowProxyChoose__FP2SWi(void *pv, int n);
int func_0014FD50(void *pv);
// name: SafeHouse port (FBentleyAbilityOk)
int FBentleyAbilityOk__FP7BENTLEYi(struct BENTLEY *pbentley, int k)
{
    register int f __asm__("$3");  /* register pin: target keeps kind and the IrowProxyChoose__FP2SWi result in v1 */
    void *pv;
    if (pbentley->f1818 != 0)
        goto fail;
    if (func_001443D8())
        return 0;
    switch (pbentley->state) {
    case 2:
        if (func_0019C8D0(pbentley->jump, k))
            goto inner;
        goto fail;
    case 3:
        if (FInteractCanDo__FP5ACTORi(pbentley->interact, k))
            goto inner;
        goto fail;
    case 13:
        if (func_0019EEF0(pbentley->climb, k))
            goto inner;
    default:
    fail:
        __asm__ __volatile__("");  /* keeps the shared return 0 apart from case 12's */
        return 0;
    case 12:
        if ((unsigned int)(pbentley->nJtthrowState - 4) < 3) {
            switch (k) {
            case 4: case 7: case 9: case 11: case 13:
                pv = pbentley->pcarrySelected;
                f = ((struct CARRY *)pv)->kind;
                if (f == k)
                    goto one;
                __asm__ __volatile__("");  /* keeps case 12's return 0 from being merged with the shared one */
                return 0;
            }
        }
        goto fail;
    case 0: case 1: case 5: case 7:
    inner:
        switch (k) {
        case 4: case 5: case 7: case 9: case 11: case 13: {
            struct ABILITY *pabil = CbFromSaak(pbentley, k);
            if (pabil->plo8) {
                if (func_00224590(pabil->plo8))
                    return 1;
                goto fail;
            }
            if ((pv = pabil->plo4)) {
                __asm__ __volatile__("" : : "r"(pabil));  /* keeps pabil (v0) live into this block, so reorg annuls the beql slot */
                f = IrowProxyChoose__FP2SWi(pv, 2);
                __asm__ __volatile__("" : "+r"(f));  /* keeps the copy in v1 that the target tests */
                if (f)
                    goto one;
            }
            return 0;
        }
        case 3: {
            int fCan = 0;
            if (pbentley->f12F0 && (g_grfjoyt & 2))
                fCan = func_0014FD50(D_002DE2E0) == 0;
            return fCan;
        }
        case 1: case 2: case 8: case 10: case 12: case 14:
        one:
            return 1;
        }
        goto fail;
    }
}
