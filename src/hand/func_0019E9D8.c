struct S { int pad[3]; int c; float g; };
void EvalCrvS(int, int, float, int) asm("EvalCrvS__FP3CRVfP6VECTORT2");
void func_0019E9D8(struct S *s, int x) { EvalCrvS(s->c, x, s->g, 0); }
