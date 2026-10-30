struct S { char pad[0x148]; unsigned long grf; };
void InitSo__FP2SO(struct S *);
void InitBarrier__FP7BARRIER(struct S *p) { InitSo__FP2SO(p); p->grf |= 0x8000L << 19; }
