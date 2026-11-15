/* func_001A2160 (0x1A2160): the damage controller's camera adjustment while reacting (SafeHouse actor.cpp, called when
 * ACTOR +0xDF4 != -1): reactions 5 and 8..12 zero the camera's adjustment distance (CPDEFI +0x34); every reaction sets
 * grfcpd bit 0 (the camera keeps its pan). */
struct CPDEFI { unsigned int grfcpd; char pad[0x30]; int sAdjust; };
struct DAMAGE { int pactor; int nState; };
#define GRFCPD_KEEP_PAN 1
void func_001A2160(struct DAMAGE *pdmg, struct CPDEFI *pcpdefi)
{
    switch (pdmg->nState) {
    case 5: case 8: case 9: case 10: case 11: case 12: pcpdefi->sAdjust = 0; break; case 4: break;
    }
    pcpdefi->grfcpd |= GRFCPD_KEEP_PAN;
}
