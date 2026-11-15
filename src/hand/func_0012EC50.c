/* AddAmbientFalloffs (the ambient sound object's post-load): PostLoLoad, room for one sound handle per sound record
 * (+0xEC), then each falloff record {target id, falloff start / end, volume} is added to the resident ambience's
 * voice (the sound manager D_003DD040 +0x228). Layout: SafeHouse port (soundglue.cpp AMBREC). */
typedef struct AREQ { int cb; int cbAlign; } AREQ;
typedef struct FALL { int id; float s[2]; float g; } FALL;   /* field: SafeHouse port */
typedef struct AMB {
    char pad[0xE4];
    int csnd;          /* field: SafeHouse port */
    void *asnd;
    void **ah;         /* field: SafeHouse port - the sounds while active */
    int cfall;
    FALL *afall;       /* field: SafeHouse port */
} AMB;
typedef struct SOUNDMGR { char pad[0x228]; void *pvoiceAmbient; } SOUNDMGR;
extern SOUNDMGR D_003DD040;
void PostLoLoad__FP2LO(AMB *pamb);
void **PvAllocSwClearImpl__Fi(AREQ *preq);
void *IvoiceFromTarget__FP8SOUNDMGRi(SOUNDMGR *psoundmgr, int id);
void AddVoiceFalloff__9CSndVoiceiiPvf(float g, void *pvoice, void *ivoice, AMB *pamb, float *ps);
// name: SafeHouse port (AddAmbientFalloffs)
void AddAmbientFalloffs__FP2LO(AMB *pamb)
{
    AREQ req;
    void *pvoice;
    PostLoLoad__FP2LO(pamb);
    req.cb = pamb->csnd * 4;
    req.cbAlign = 0x10;
    pamb->ah = PvAllocSwClearImpl__Fi(&req);
    pvoice = D_003DD040.pvoiceAmbient;
    if (pvoice) {
        int ifall;
        for (ifall = 0; ifall < pamb->cfall; ifall++) {
            FALL *pfall = &pamb->afall[ifall];
            AddVoiceFalloff__9CSndVoiceiiPvf(pfall->g, pvoice, IvoiceFromTarget__FP8SOUNDMGRi(&D_003DD040, pfall->id), pamb, pfall->s);
        }
    }
}
