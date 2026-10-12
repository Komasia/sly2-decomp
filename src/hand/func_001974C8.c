typedef struct N { int v; struct N *next; } N;
typedef struct O { char pad[0x64]; N *p; } O;
int func_001974C8(O *o)
{
    N *p = o->p;
    while (p) {
        if (p->v)
            return p->v;
        p = p->next;
    }
    return 0;
}
