/* class: ALO (booty; a descriptor at 0x2A5144): the object reparented as booty (ReparentBooty) under the object (or
 * its parent) named by the first entry of its +0xE4 record's +0x8 list. */
typedef struct ALO ALO;
typedef struct REC { char pad0[8]; void **apv; } REC;
typedef struct ALOB {
    /* 0x00 */ char pad0[0xe4];
    /* 0xe4 */ REC *prec;
} ALOB;

ALO *PaloOrParent__FPv(void *pv);
void ReparentBooty__FP3ALOii(ALOB *palo, ALO *paloParent, int n);

void func_00159968(ALOB *palo)
{
    ReparentBooty__FP3ALOii(palo, PaloOrParent__FPv(palo->prec->apv[0]), 0);
}
