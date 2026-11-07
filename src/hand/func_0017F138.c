struct VTE { short d; short pad; void (*pfn)(void *); };
struct S { char pad[0xC]; struct VTE *vt; };
void func_001F36A8(struct S *p);
// name: SafeHouse port (PostLoadHackSoBase)
void PostLoadHackSoBase__FP2LO(struct S *p) { struct VTE *e; func_001F36A8(p); e = &p->vt[0x53]; e->pfn((char *)p + e->d); }
