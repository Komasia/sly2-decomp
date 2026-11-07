typedef struct VT { short d; short pad; void (*fn)(void *); } VT;
typedef struct O { int pad[6]; VT *vt; } O;
typedef struct T { int pad[4]; O *p; int pad2[2]; O *q; } T;
// name: SafeHouse port (CTRLSOURCE::Start)
void Start__10CTRLSOURCE(T *t)
{
    O *p = t->p;
    t->q = p;
    if (p)
        p->vt[1].fn((char *)p + p->vt[1].d);
}
