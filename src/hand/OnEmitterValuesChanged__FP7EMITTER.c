/* OnEmitterValuesChanged: the emitter's settings block changed - hand it to the particle system and the ripple group
 * again and pick a new emission value from its range (kind 3 counts per second: x60 for frames). */
struct EMITB;
struct PSYS;
struct RIPG;
struct LM { float gMin; float gMax; };
struct EMITTER {
    /* 0x000 */ char pad0[0xe0];
    /* 0x0e0 */ int fValuesChanged;
    /* 0x0e4 */ struct EMITB *pemitb;
    /* 0x0e8 */ char padE8[0xf0 - 0xe8];
    /* 0x0f0 */ int kind;               /* emission kind (PostEmitterLoad picks 0..3) */
    /* 0x0f4 */ int nF4;
    /* 0x0f8 */ struct LM lm;           /* range of the emission value */
    /* 0x100 */ char pad100[0x130 - 0x100];
    /* 0x130 */ float g;                /* the current emission value */
    /* 0x134 */ char pad134[0x14c - 0x134];
    /* 0x14c */ struct RIPG *pripg;
    /* 0x150 */ struct PSYS *ppsys;
};

void SetPsysFromEmitb(struct PSYS *ppsys, struct EMITB *pemitb) asm("SetPsysFromEmitb__FP4PSYSP8EMITTERN");
void SetRipgEmitb(struct RIPG *pripg, struct EMITB *pemitb) asm("SetRipgEmitb__FP4RIPGP5EMITB");
float GRandInRange(float gMin, float gMax) asm("GRandInRange__Fff");

void OnEmitterValuesChanged__FP7EMITTER(struct EMITTER *pemitter)
{
    pemitter->fValuesChanged = 0;
    if (pemitter->ppsys)
        SetPsysFromEmitb(pemitter->ppsys, pemitter->pemitb);
    if (pemitter->pripg)
        SetRipgEmitb(pemitter->pripg, pemitter->pemitb);
    if (pemitter->kind == 3)
        pemitter->g = GRandInRange(pemitter->lm.gMin, pemitter->lm.gMax) * 60.0f;
    else
        pemitter->g = GRandInRange(pemitter->lm.gMin, pemitter->lm.gMax);
}
