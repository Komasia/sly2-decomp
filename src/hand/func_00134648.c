/* InitBentley (cid 0x37): the actor fields, then Bentley's: no state (-1) in either state machine, no mine / carried
 * state, his height 125, the walk and run gaits, the jump's +0x118, the reach values (+0x1098..+0x10B4), the six abilities'
 * ids {5, 7, 9, 11, 13, 4} (+0x1824 + 0xC i) and triangle's ability 5; the world's Bentley D_002DD5BC.
 * Field names: SafeHouse port (gang.h BENTLEY); g/n + offset where SafeHouse has no meaning yet. */
struct S10A8 { float g0; int n4; float g8; float gC; };   /* +0x10A8 (SafeHouse: part of the reach, 250 0 1 4500) */
struct BENTLEY {
    char pad0[0x3D8]; float gJump118;
    char pad1[0x1000 - 0x3DC]; int n1000;
    char pad2[0x103C - 0x1004]; float g103C; int n1040; int x1044; float sHeight;
    char pad3[0x1098 - 0x104C]; float g1098; float g109C; float g10A0; float g10A4; struct S10A8 s10A8;
    char pad4[0x1320 - 0x10B8]; char gaitWalk[0x13D0 - 0x1320]; int state;
    char pad5[0x1600 - 0x13D4]; char gaitRun[0x16B0 - 0x1600]; int n16B0; int pad6[2]; int n16BC;
    char pad7[0x1800 - 0x16C0]; int n1800;
    char pad8[0x1824 - 0x1804]; int idAbil0; int pad9[2]; int idAbil1; int padA[2]; int idAbil2; int padB[2]; int idAbil3;
    int padC[2]; int idAbil4; int padD[2]; int idAbil5; int padE[3]; int n1870;
};
extern struct BENTLEY *D_002DD5BC;
void InitActorFields__FP5ACTOR(struct BENTLEY *pbentley);
void InitGait__FP4GAITii(void *pv, struct BENTLEY *pbentley, int n);
// name: SafeHouse port (InitBentley)
void InitBentley__FP7BENTLEY(struct BENTLEY *pbentley)
{
    InitActorFields__FP5ACTOR(pbentley);
//{
    pbentley->n1040 = 0;
    pbentley->state = -1;
    pbentley->n16B0 = -1;
    pbentley->n16BC = -1;
    pbentley->n1800 = -1;
    pbentley->g103C = 45.0f;
    pbentley->sHeight = 125.0f;
//}
    InitGait__FP4GAITii(pbentley->gaitWalk, pbentley, 0x73);
    InitGait__FP4GAITii(pbentley->gaitRun, pbentley, 0x73);
    pbentley->gJump118 = -70.0f;
    pbentley->g1098 = -100.0f;
    pbentley->g109C = 100.0f;
    pbentley->g10A0 = 50.0f;
    pbentley->g10A4 = -10.0f;
    {
        struct S10A8 *ps = &pbentley->s10A8;
        ps->g0 = 250.0f;
        ps->g8 = 1.0f;
        ps->n4 = 0;
        ps->gC = 4500.0f;
    }
    pbentley->n1000 = 2;
    pbentley->idAbil1 = 7;
    pbentley->idAbil2 = 9;
    pbentley->idAbil3 = 11;
    pbentley->idAbil4 = 13;
    pbentley->idAbil5 = 4;
    pbentley->idAbil0 = 5;
    pbentley->n1870 = 5;
    D_002DD5BC = pbentley;
}
