struct S { char pad[0x34]; int n34; };
struct G { int a; };
extern struct G g_sw;
void *PloFindSwNearest__FP2LO3OIDii(struct G *pg, int kind, int oid, int owner);
// name: SafeHouse port (JOBSCRIPT::PloNear)
void *PloNear__9JOBSCRIPT3OID(struct S *p, int oid) { int o = p->n34; int k = o ? 4 : 5; return PloFindSwNearest__FP2LO3OIDii(&g_sw, k, oid, o); }
