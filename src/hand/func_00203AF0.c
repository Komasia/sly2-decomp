/* MakeStepCustomEntry (0x203AF0): appends the STEP's custom entry (psoeCustom) rebuilt from psoeSrc in the root
 * record's space with 2 extra points (3 when all of psoeSrc's points are pinned and the object is not an actor):
 * the base vecBase and sProbeDrop below it (and the origin); sFloorTarget is its lowest pinned point and
 * pposProbe0 / pposProbe1 the probes' world points. A live object's entries are removed and re-added around it.
 * (Claude agent) matched: mesh->geomLocal.apos loaded into a $2 pointer after qmtc2, vmadd fed the VF3 scalar directly, slot = c*16 + (int)dst computed before the u.q store. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct POINT { float x; float y; float z; float w; };
struct XFW { char pad[0x40]; char matWorld[1]; };
/* a geometry: the point count and the points (qwords) */
struct GEOMQ { int cpos; void *apos; char pad8[0x10]; };
struct GEOMW { int cpos; char *apos; char pad8[0x10]; };
/* SOE: one entry of an ALO's mesh list (0xB0 bytes) */
struct SOE {
    /* 0x00 */ struct XFW *pxf;
    /* 0x04 */ char pad4[0x18];
    /* 0x1c */ int cposPinned;       /* the first cposPinned points are pinned */
    /* 0x20 */ char pad20[0x58];
    /* 0x78 */ struct GEOMQ geomLocal;
    /* 0x90 */ struct GEOMW geomWorld;
};
/* the STEP fields used here */
struct STEP {
    char pad0[0x28]; unsigned long grfLo; char pad1[0x60 - 0x30]; void *pxfRoot; char pad2[0xE0 - 0x64]; int csoe; char *asoe;
    char pad3[0x210 - 0xE8]; float sFloorTarget; float sProbeDrop; char *pposProbe0; char *pposProbe1; char pad4[0x240 - 0x220]; qword vecBase;
    char pad5[0x258 - 0x250]; struct SOE *psoeCustom;
};
extern float D_002A85F0;
extern qword g_normalZ;
extern qword D_002A2DD0;
void RemoveAloSoes__FP3ALO(struct STEP *pstep);
void AddAloSoes__FP3ALO(struct STEP *pstep);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct STEP *pstep, int cid);
void RebuildSoe__FP3SOEP2XFiT0(struct SOE *psoeSrc, void *pxf, int cposExtra, struct SOE *psoe);
void EnsureSoeMesh__FP3SOE(struct SOE *psoe);
void TransformGeom__FP7MATRIX4P4GEOMT1(void *pmat, void *pgeomSrc, void *pgeomDst);

// name: SafeHouse port (MakeStepCustomEntry)
void MakeStepCustomEntry__FP3ALOP3SOE(struct STEP *pstep, struct SOE *psoeSrc)
{
    int isoe, fAllPinned, i, c;
    float zMin;
    U u;
    qword r;
    if ((int)(pstep->grfLo >> 60) & 1)
        RemoveAloSoes__FP3ALO(pstep);
    isoe = pstep->csoe;
    pstep->csoe = isoe + 1;
    fAllPinned = 0;
    pstep->psoeCustom = (struct SOE *)(pstep->asoe + isoe * 0xB0);
    if (!FIsBasicDerivedFrom__FP5BASIC3CID(pstep, 0x34))
        fAllPinned = psoeSrc->cposPinned == psoeSrc->geomLocal.cpos;
    RebuildSoe__FP3SOEP2XFiT0(psoeSrc, pstep->pxfRoot, !fAllPinned ? 2 : 3, pstep->psoeCustom);
    EnsureSoeMesh__FP3SOE(pstep->psoeCustom);
    zMin = D_002A85F0;
    for (i = 0; i < pstep->psoeCustom->cposPinned; i++) {
        float z = ((struct POINT *)pstep->psoeCustom->geomLocal.apos)[i].z;
        zMin = (z > zMin) ? zMin : z;
    }
    pstep->sFloorTarget = zMin;
    c = pstep->psoeCustom->cposPinned;
    pstep->psoeCustom->cposPinned = c + 2;
    {register struct SOE *mesh __asm__("$4")=pstep->psoeCustom;
     register qword point __asm__("$3")=pstep->vecBase;
     ((qword *)mesh->geomLocal.apos)[c]=point;}
    {register int word __asm__("$2");
     register struct SOE *mesh __asm__("$3");
     register qword *dst __asm__("$2");
     __asm__("lw %0,%2\n\tlw %1,%3":"=&r"(word),"=r"(mesh):"m"(pstep->sProbeDrop),"m"(pstep->psoeCustom));
     {register qword value __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(value):"r"(word));
     dst=(qword *)mesh->geomLocal.apos;
     __asm__ __volatile__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(pstep->vecBase),"j"(g_normalZ),"j"(value));
     {qword *slot=(qword *)(c*16+(int)dst);
     u.q=value;
     slot[1]=r;}}}
    if (fAllPinned)
        ((qword *)pstep->psoeCustom->geomLocal.apos)[c + 2] = D_002A2DD0;
    TransformGeom__FP7MATRIX4P4GEOMT1(pstep->psoeCustom->pxf->matWorld, &pstep->psoeCustom->geomLocal, &pstep->psoeCustom->geomWorld);
    pstep->pposProbe0 = pstep->psoeCustom->geomWorld.apos + c * 16;
    pstep->pposProbe1 = pstep->psoeCustom->geomWorld.apos + (c * 16 + 0x10);
    if ((int)(pstep->grfLo >> 60) & 1)
        AddAloSoes__FP3ALO(pstep);
}
