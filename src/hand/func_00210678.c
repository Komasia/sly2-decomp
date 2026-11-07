void *func_0015E938(void *pv, int k, int id);
void *func_001EC918(int id);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int cid);
void SetAloEyesClosed__FP3ALOf(void *p, float f);
void SetEyesClosed__FP4EYESf(void *p, float f);
// name: SafeHouse port (SetEyesClosedOf)
void SetEyesClosedOf__FP2LOiif(void *pv, int id1, int id2, float f)
{
    void *p1 = 0;
    void *p2 = 0;
    if (id1 != -1) {
        void *q = func_0015E938(pv, 4, id1);
        if (q && FIsBasicDerivedFrom__FP5BASIC3CID(q, 0x30))
            p1 = q;
    }
    if (id2 != -1) {
        p2 = func_001EC918(id2);
        if (p2 && !FIsBasicDerivedFrom__FP5BASIC3CID(p2, 0x8E))
            p2 = 0;
    }
    if (p1)
        SetAloEyesClosed__FP3ALOf(p1, f);
    if (p2)
        SetEyesClosed__FP4EYESf(p2, f);
}
