struct F { int a[0x1C]; };
void *func_00205458(void *p, int n);
void *s1_memset(void *p, int c, int n);
void React__8JOBREACTP5AIMSG(void *p, struct F *pf);
// name: SafeHouse port (TellGuardCommands)
void TellGuardCommands__FP2LOi(void *p, int n) { struct F f; void *o = func_00205458(p, 0x9C); if (o) { s1_memset(&f, 0, sizeof(f)); f.a[4] = n; f.a[0] = 5; React__8JOBREACTP5AIMSG(o, &f); } }
