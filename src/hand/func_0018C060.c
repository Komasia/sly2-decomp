struct S { char pad[0x2C0]; char x2c0[0x200]; char x4c0[0x60]; void *x520; char p1[0x8CC]; char xdf0[0x930]; void *a1720[0x6A]; int n; };
void *IsoeInteractMesh__FP5ACTORPi(void *p, int *pn);
void *IsoeDamageMesh__FP5ACTORPi(void *p, int *pn);
void *IsoeJumpMesh__FP5ACTORPi(void *p, int *pn);
void SetStepMesh__FP3ALOPvi(struct S *p, void *pv, int n);
// name: SafeHouse port (UpdateActorStepMesh)
void UpdateActorStepMesh__FP5ACTOR(struct S *p)
{
    int n = 0;
    void *pv;
    switch (p->n) {
    case 7: pv = IsoeInteractMesh__FP5ACTORPi(p->x4c0, &n); break;
    case 4: pv = IsoeDamageMesh__FP5ACTORPi(p->xdf0, &n); break;
    case 2: pv = IsoeJumpMesh__FP5ACTORPi(p->x2c0, &n); break;
    case 21: case 22: pv = p->x520; break;
    default: pv = p->a1720[p->n]; break;
    }
    if (!pv) pv = p->a1720[0];
    SetStepMesh__FP3ALOPvi(p, pv, n);
}
