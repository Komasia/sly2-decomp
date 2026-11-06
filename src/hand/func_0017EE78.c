struct S { char pad[0x18]; void *p18; };
int FAtEnd__11JOBPATHSTEP(struct S *p);
int NArrived__7JOBGOTO(void *p);
// name: SafeHouse port (JOBPATHSTEP::FDone)
int FDone__11JOBPATHSTEP(struct S *p) { if (!FAtEnd__11JOBPATHSTEP(p)) return 0; return NArrived__7JOBGOTO(p->p18); }
