struct X { char pad[0xC];
  virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); };
extern "C" X *func_0015E938(void *pv, int k, int id);
extern "C" int FIsBasicDerivedFrom(void *p, int cid) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
extern "C" void FadeAloIn(X *p, float f) asm("FadeAloIn__FP3ALOf");
extern "C" void FadeAloOut(X *p, float f) asm("FadeAloOut__FP3ALOf");
// name: SafeHouse port (AddRemoveByOid)
extern "C" X *AddRemoveByOid__FPv3OIDif(void *pv, int fOn, int id, float g)
{
    X *p = func_0015E938(pv, 4, id);
    if (p) {
        if (g != 0.0f && FIsBasicDerivedFrom(p, 0x30)) {
            if (fOn)
                FadeAloIn(p, g);
            else
                FadeAloOut(p, g);
        } else {
            if (fOn)
                p->v8();
            else
                p->v9();
        }
    }
    return p;
}
