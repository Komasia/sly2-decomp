/* Bentley's step collision mesh by state: the interaction's, the damage's or the jump's, else the default
 * (+0x268). */
struct BENTLEY { char pad[0x268]; int isoeDefault; char pad1[0x2c0 - 0x26c]; int jump; char pad2[0x4c0 - 0x2c4]; int interact; char pad3[0xdf0 - 0x4c4]; int damage; char pad4[0x13d0 - 0xdf4]; int state; };
int IsoeInteractMesh__FP5ACTORPi(void *, int *);
int IsoeJumpMesh__FP5ACTORPi(void *, int *);
int IsoeDamageMesh__FP5ACTORPi(void *, int *);
void SetStepMesh__FP3ALOPvi(struct BENTLEY *, int, int);
void func_00135D80(struct BENTLEY *pbentley) {
    int n = 0;
    int isoe;
    switch (pbentley->state) {
    case 3: isoe = IsoeInteractMesh__FP5ACTORPi(&pbentley->interact, &n); break;
    case 4: isoe = IsoeDamageMesh__FP5ACTORPi(&pbentley->damage, &n); break;
    case 2: isoe = IsoeJumpMesh__FP5ACTORPi(&pbentley->jump, &n); break;
    default: isoe = 0; break;
    }
    if (!isoe) isoe = pbentley->isoeDefault;
    SetStepMesh__FP3ALOPvi(pbentley, isoe, n);
}
