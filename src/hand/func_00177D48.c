/* func_00177D48: whether the guard's +0xF68 object is in the world (LO flag bit 60). */
struct LO { char pad[0x28]; unsigned long grf; };
struct GUARD { char pad[0xF68]; struct LO *plo; };
struct AIJOB { char pad[0x10]; struct GUARD *pguard; };
int func_00177D48(struct AIJOB *pjob) { struct LO *plo = pjob->pguard->plo; int fInWorld = 0; if (plo) fInWorld = (int)(plo->grf >> 60) & 1; return fInWorld; }
