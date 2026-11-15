/* InitActorFields: the actor's parts (step, jump +0x2C0, interaction +0x4C0, +0x9E0, damage +0xDF0, binoculars +0xF00,
 * throw +0x11B0, climb +0xF50, +0xFD0) initialised, then its defaults: height 125, the look times' ranges (1.5..2.5,
 * 3..5), power 100, no targets (-1), and its contact bytes (0 for all, 8 for 0x10FF00). Layout: SafeHouse port
 * (actor.h ACTOR, 0x13FF70). */
struct ACTOR {
    char pad0[0x1020]; float g1020; char pad1[0x103C - 0x1024]; float g103C; char pad2[0x1048 - 0x1040]; float sHeight;
    char pad3[0x10C8 - 0x104C]; int n10C8; char pad4[0x10D4 - 0x10CC]; float g10D4; float g10D8; char pad5[0x10E4 - 0x10DC];
    int n10E4; int plo10E8; int n10EC; int f10F0; char pad6[0x1138 - 0x10F4]; float tLookMin1138; float tLookMax113C; float tLookMin1140; float tLookMax1144;
    char pad7[0x12F0 - 0x1148]; int f12F0; char pad8[0x1300 - 0x12F4]; int nPowerMax; float g1304; char pad9[0x1318 - 0x1308]; int n1318;
};
void InitStep__FP4STEP(struct ACTOR *pactor);
void InitJump__FP4JUMPi(void *pv, struct ACTOR *pactor);
void InitInteract__FP5ACTORi(void *pv, struct ACTOR *pactor);
void func_0019F3E8(void *pv, struct ACTOR *pactor);
void InitDamage__FP5ACTORi(void *pv, struct ACTOR *pactor);
void InitBinoc__FP5BINOC5BLOTK(void *pv, struct ACTOR *pactor);
void InitJtThrow__FP5ACTORUi(void *pv, struct ACTOR *pactor);
void InitClimb__FP5ACTORi(void *pv, struct ACTOR *pactor);
void func_00144638(void *pv, struct ACTOR *pactor);
void SetAloXpBytes__FP3ALOUiUc(struct ACTOR *pactor, int mask, int n);
// name: SafeHouse port (InitActorFields)
void InitActorFields__FP5ACTOR(struct ACTOR *pactor)
{
    InitStep__FP4STEP(pactor);
    InitJump__FP4JUMPi((char *)pactor + 0x2C0, pactor);
    InitInteract__FP5ACTORi((char *)pactor + 0x4C0, pactor);
    func_0019F3E8((char *)pactor + 0x9E0, pactor);
    InitDamage__FP5ACTORi((char *)pactor + 0xDF0, pactor);
    InitBinoc__FP5BINOC5BLOTK((char *)pactor + 0xF00, pactor);
    InitJtThrow__FP5ACTORUi((char *)pactor + 0x11B0, pactor);
    InitClimb__FP5ACTORi((char *)pactor + 0xF50, pactor);
    func_00144638((char *)pactor + 0xFD0, pactor);


    pactor->g103C = 20.0f;
    pactor->f10F0 = 1;
    pactor->sHeight = 125.0f;
    pactor->g10D4 = pactor->g10D8 = 1.0f;
    pactor->tLookMin1138 = 1.5f;
    pactor->tLookMax113C = 2.5f;
    pactor->tLookMin1140 = 3.0f;
    pactor->tLookMax1144 = 5.0f;
    pactor->f12F0 = pactor->f10F0;
    pactor->g1020 = 100.0f;
    pactor->nPowerMax = 100;
    pactor->g1304 = -60.0f;
    pactor->n10EC = -1;
    pactor->n10E4 = -1;
    pactor->n1318 = -1;
    pactor->n10C8 = -1;

    SetAloXpBytes__FP3ALOUiUc(pactor, 0x3FFFFFF, 0);
    SetAloXpBytes__FP3ALOUiUc(pactor, 0x10FF00, 8);
}
