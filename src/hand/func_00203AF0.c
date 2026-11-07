/* (Claude agent) matched: mesh->p7C loaded into a $2 pointer after qmtc2, vmadd fed the VF3 scalar directly, slot = c*16 + (int)dst computed before the u.q store. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct E { float a; float b; float c; float d; };
struct Q0 { char pad[0x40]; char a40[1]; };
struct Q { struct Q0 *p0; char pad[0x1C - 4]; int c; char pad2[0x78 - 0x20]; char a78[4]; void *p7C; char pad3[0x90 - 0x80]; char a90[4]; char *p94; };
struct M { char pad[0x1C]; int n1C; char pad2[0x78 - 0x20]; int n78; };
struct S {
    char pad0[0x28]; unsigned long fl28; char pad1[0x60 - 0x30]; void *p60; char pad2[0xE0 - 0x64]; int nE0; char *pE4;
    char pad3[0x210 - 0xE8]; float f210; int n214; char *p218; char *p21C; char pad4[0x240 - 0x220]; qword q240;
    char pad5[0x258 - 0x250]; struct Q *pq;
};
extern float D_002A85F0;
extern qword g_normalZ;
extern qword D_002A2DD0;
void RemoveAloSoes__FP3ALO(struct S *p);
void AddAloSoes__FP3ALO(struct S *p);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct S *p, int n);
void RebuildSoe__FP3SOEP2XFiT0(struct M *m, void *p, int k, struct Q *q);
void EnsureSoeMesh__FP3SOE(struct Q *q);
void TransformGeom__FP7MATRIX4P4GEOMT1(void *a, void *b, void *c);

// name: SafeHouse port (MakeStepCustomEntry)
void MakeStepCustomEntry__FP3ALOP3SOE(struct S *p, struct M *m)
{
    int n, fl, i, c;
    float mn;
    U u;
    qword r;
    if ((int)(p->fl28 >> 60) & 1)
        RemoveAloSoes__FP3ALO(p);
    n = p->nE0;
    p->nE0 = n + 1;
    fl = 0;
    p->pq = (struct Q *)(p->pE4 + n * 0xB0);
    if (!FIsBasicDerivedFrom__FP5BASIC3CID(p, 0x34))
        fl = m->n1C == m->n78;
    RebuildSoe__FP3SOEP2XFiT0(m, p->p60, !fl ? 2 : 3, p->pq);
    EnsureSoeMesh__FP3SOE(p->pq);
    mn = D_002A85F0;
    for (i = 0; i < p->pq->c; i++) {
        float e = ((struct E *)p->pq->p7C)[i].c;
        mn = (e > mn) ? mn : e;
    }
    p->f210 = mn;
    c = p->pq->c;
    p->pq->c = c + 2;
    {register struct Q *mesh __asm__("$4")=p->pq;
     register qword point __asm__("$3")=p->q240;
     ((qword *)mesh->p7C)[c]=point;}
    {register int word __asm__("$2");
     register struct Q *mesh __asm__("$3");
     register qword *dst __asm__("$2");
     __asm__("lw %0,%2\n\tlw %1,%3":"=&r"(word),"=r"(mesh):"m"(p->n214),"m"(p->pq));
     {register qword value __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(value):"r"(word));
     dst=(qword *)mesh->p7C;
     __asm__ __volatile__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(p->q240),"j"(g_normalZ),"j"(value));
     {qword *slot=(qword *)(c*16+(int)dst);
     u.q=value;
     slot[1]=r;}}}
    if (fl)
        ((qword *)p->pq->p7C)[c + 2] = D_002A2DD0;
    TransformGeom__FP7MATRIX4P4GEOMT1(p->pq->p0->a40, p->pq->a78, p->pq->a90);
    p->p218 = p->pq->p94 + c * 16;
    p->p21C = p->pq->p94 + (c * 16 + 0x10);
    if ((int)(p->fl28 >> 60) & 1)
        AddAloSoes__FP3ALO(p);
}
