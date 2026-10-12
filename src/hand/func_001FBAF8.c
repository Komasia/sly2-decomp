struct VTE { short d; short pad; void (*pfn)(void *); };
struct S { int a[3]; struct VTE *vt; char pad[0x30]; int x40; char pad2[0xE]; short x52; };
void func_001FBAF8(int x, long l) { struct S *p = (struct S *)(int)l; p->x40 = x; p->x52 = 0; p->vt[2].pfn((char *)p + p->vt[2].d); }
