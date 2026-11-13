/* CPLOOKAT::Deactivate: the look-at camera policy loses its camera object pv: when the object asks for a cut, the
 * camera cuts; then the base policy's deactivate. Layout: SafeHouse port (cplcy.h CPLOOKAT, cm.h CMOBJ). */
struct LO;
struct CM;
struct CMOBJ {
    /* 0x000 */ char pad0[0x120];
    /* 0x120 */ int fCut;              /* SafeHouse: cut the camera */
};
struct CPLOOKAT {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct CMOBJ *pcmobj;   /* field: SafeHouse port */
};
extern struct CM g_cm;
void CutCm(struct CM *pcm) asm("CutCm__FP2CM");
void Deactivate__5CPLCYP2LOPv(struct CPLOOKAT *pcplcy, struct LO *psoFocus, void *pv);

// name: SafeHouse port (CPLOOKAT::Deactivate)
void Deactivate__8CPLOOKATP2LOPv(struct CPLOOKAT *pcplcy, struct LO *psoFocus, struct CMOBJ *pcmobj)
{
    if (pcplcy->pcmobj == pcmobj) {
        if (pcmobj->fCut)
            CutCm(&g_cm);
        pcplcy->pcmobj = 0;
    }
    Deactivate__5CPLCYP2LOPv(pcplcy, psoFocus, pcmobj);
}
