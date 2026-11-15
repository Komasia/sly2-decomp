/* FDamageImmune (0x1A2230): whether the damage controller ignores a hit kind: always with the actor's authored +0x298;
 * the kinds 0x2000 (water) / 0x4000 by the reaction (3 / 5 / 10 / 11 yes, others no), and without one by the
 * interaction kind (+0x4C8) and, without that, the jump's state (+0x2DC: 8..17 ignore 0x4000); other kinds while
 * reacting or flashing, with D_002E1E00 bit 0, or while the world is hands-off. SafeHouse damage.cpp. */
struct P { char pad[0x298]; int x298; char pad2[0x2DC - 0x29C]; int x2DC; char pad3[0x4C8 - 0x2E0]; int x4C8; char pad4[0xDF4 - 0x4CC]; int xDF4; };
struct DAMAGE { struct P *pactor; int nState; char pad[0x88]; int nFlash; };
extern int D_002E1E00;
struct SW { char pad[0x3D78]; int counter; };
extern struct SW g_sw;
int IsSwHandsOff__FP2SW(struct SW *psw);
#define FIELD_OFFSET(t,m) ((unsigned int)&(((struct t*)0x10000)->m)-0x10000)
typedef char P_x298_Offset[FIELD_OFFSET(P,x298)==664?1:-1];
typedef char P_x2DC_Offset[FIELD_OFFSET(P,x2DC)==732?1:-1];
typedef char P_x4C8_Offset[FIELD_OFFSET(P,x4C8)==1224?1:-1];
typedef char P_xDF4_Offset[FIELD_OFFSET(P,xDF4)==3572?1:-1];
typedef char DAMAGE_pactor_Offset[FIELD_OFFSET(DAMAGE,pactor)==0?1:-1];
typedef char DAMAGE_nState_Offset[FIELD_OFFSET(DAMAGE,nState)==4?1:-1];
typedef char DAMAGE_nFlash_Offset[FIELD_OFFSET(DAMAGE,nFlash)==144?1:-1];
typedef char SW_counter_Offset[FIELD_OFFSET(SW,counter)==15736?1:-1];
typedef char P_PrefixSize[sizeof(struct P)==3576?1:-1];
typedef char DAMAGE_PrefixSize[sizeof(struct DAMAGE)==148?1:-1];
typedef char SW_PrefixSize[sizeof(struct SW)==15740?1:-1];
typedef char int_Size[sizeof(int)==4?1:-1];
// name: SafeHouse port (FDamageImmune)
int FDamageImmune__FP5ACTORi(struct DAMAGE *pdmg, int kind)
{
    if (pdmg->pactor->x298)
        return 1;
    if (kind == 0x2000 || kind == 0x4000) {
        switch (pdmg->pactor->xDF4) {
        case -1:
            switch (pdmg->pactor->x4C8) {
            case -1:
                switch (pdmg->pactor->x2DC) {
                case -1:
                    goto ret0;
                case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17:
                    {
                        register int k __asm__("$3") = 0x4000;
                        register int result __asm__("$2") = 1;
                        if (kind == k) return result;
                        result = 0;
                        return result;
                    }
                }
                return 0;
            case 1: case 2: case 5: case 6: case 9:
                goto ret0;
            }
            goto ret1;
        case 3: case 5: case 10: case 11:
            goto ret1;
        }
        goto ret0;
    }
    if (pdmg->nState != -1)
        return 1;
    if (pdmg->nFlash == 1)
        return 1;
    if (D_002E1E00 & 1)
        return 1;
    if (!IsSwHandsOff__FP2SW(&g_sw))
        goto ret0;
ret1:
    return 1;
ret0:
    return 0;
}
