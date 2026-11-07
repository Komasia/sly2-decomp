struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct S { char pad[0x1D8]; void *powner; };
extern struct DL D_003E1A4C;
void OnLoRemove__FP2LO(struct S *p);
void DissolveMerged__FP2LO(void *p);
void RemoveDlEntry__FP2DLPv(struct DL *pdl, void *pv);
int FFindDlEntry__FP2DLPv(struct DL *pdl, void *pv);
void RemovePolyFromRegion__FP7NAVPOLY(void *p);
// name: SafeHouse port (RemoveNavPoly)
void RemoveNavPoly__FP2LO(struct S *p)
{
    struct DL *pdl;
    OnLoRemove__FP2LO(p);
    if (p->powner) DissolveMerged__FP2LO(p->powner);
    RemovePolyFromRegion__FP7NAVPOLY(p);
    pdl = &D_003E1A4C;
    if (FFindDlEntry__FP2DLPv(pdl, p)) RemoveDlEntry__FP2DLPv(pdl, p);
}
