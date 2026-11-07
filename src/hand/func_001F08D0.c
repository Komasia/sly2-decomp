struct O { char pad[0x40]; float g; };
struct P { char pad[0x30]; struct O *po; };
void SetAsegaTime__FP5ASEGAiff(struct O *, int, float, float);
void RetractAsega__FP5ASEGA(struct O *);
void EndSmaTransition__FP3SMA(struct P *);
// name: SafeHouse port (FinishSmaTransition)
void FinishSmaTransition__FP3SMA(struct P *p)
{
    struct O *po = p->po;
    if (po) {
        p->po = 0;
        if (po->g < 0.0f) SetAsegaTime__FP5ASEGAiff(po, 0, 0.0f, po->g);
        else SetAsegaTime__FP5ASEGAiff(po, 2, 0.0f, po->g);
        RetractAsega__FP5ASEGA(po);
        EndSmaTransition__FP3SMA(p);
    }
}
