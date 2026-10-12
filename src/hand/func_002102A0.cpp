struct XB { char pad[0xC];
  virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
  virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
  virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
  virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
};
struct X : XB { char pad10[0x10]; X *next; };
struct B { X *first; int a, b; };
struct S { char pad[0x3038]; B ab[199]; };
extern "C" void func_001C4A60(S *p, int k);
extern "C" void func_002102A0(S *p)
{
    int i;
    func_001C4A60(p, 0);
    for (i = 0; i < 199; i++) {
        X *x = ((struct B *)((char *)p + 0x3038))[i].first;
        for (; x; x = x->next)
            x->v24();
    }
}
