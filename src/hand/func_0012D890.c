typedef struct VT { short d; short pad; void (*fn)(void *); } VT;
typedef struct O { int pad[6]; VT *vt; } O;
typedef struct T { int pad[7]; O *q; } T;
void func_0012D890(T *t)
{
    O *p = t->q;
    if (p) {
        p->vt[2].fn((char *)p + p->vt[2].d);
        t->q = 0;
    }
}
