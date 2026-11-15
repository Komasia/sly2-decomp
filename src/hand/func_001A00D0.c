/* func_001A00D0 (0x1A00D0): removes every reference to an object (plo) or a floor entry (psoe) from the safe-ground
 * histories (ACTOR +0x9E0) of the three heroes, then clears the "referenced by a safe-ground history" bits
 * (LO +0x28 bit 59, SOE +0x10 bit 51). SafeHouse damage.cpp RemoveSafeGroundReferences (0x1A0048 / 0x1A00D0). */
struct A { char pad[0x28]; unsigned long x28; };
struct B { char pad[0x10]; unsigned long x10; };

#define IB_SAFEGROUND 0x9E0                        /* ACTOR +0x9E0: the SAFEGROUND history */
#define GRF_LO_SAFEGROUND_REF 0x0800000000000000UL /* LO grf bit 59 */
#define GRF_SOE_SAFEGROUND_REF 0x0008000000000000UL /* SOE bit 51 */

extern char *g_psly __asm__("D_002E1E40");     /* Sly */
extern char *g_pbentley __asm__("D_002DD5BC"); /* Bentley */
extern char *g_pmurray __asm__("D_002F7900");  /* Murray */
void RemoveSafeGroundReferences__FP2LOP3SOEPv(void *psafe, struct A *plo, struct B *psoe);

void func_001A00D0(void *pv, struct A *plo, struct B *psoe)
{
    if (g_psly)
        RemoveSafeGroundReferences__FP2LOP3SOEPv(g_psly + IB_SAFEGROUND, plo, psoe);
    if (g_pbentley)
        RemoveSafeGroundReferences__FP2LOP3SOEPv(g_pbentley + IB_SAFEGROUND, plo, psoe);
    if (g_pmurray)
        RemoveSafeGroundReferences__FP2LOP3SOEPv(g_pmurray + IB_SAFEGROUND, plo, psoe);
    if (plo)
        plo->x28 &= ~GRF_LO_SAFEGROUND_REF; /* LO grf */
    if (psoe)
        psoe->x10 &= ~GRF_SOE_SAFEGROUND_REF;
}
