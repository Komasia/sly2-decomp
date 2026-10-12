struct N { int k; int id; int pad[4]; struct N *next; };
struct S { char pad[0x50]; struct N *first; };
struct N *func_001711F0(struct S *p, int id) { int unused[4]; struct N *n; for (n = p->first; n; n = n->next) if (n->k == 9 && n->id == id) break; return n; }
