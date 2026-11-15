/* func_0020A518 (0x20A518, option 301): adds a region the guard may go in (at most 8). */
struct GUARD { char pad[0xE94]; unsigned int cRegion; int aRegion[8]; };
void func_0020A518(struct GUARD *pguard, int region) { if (pguard->cRegion < 8) pguard->aRegion[pguard->cRegion++] = region; }
