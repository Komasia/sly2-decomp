typedef struct LO { int pad[4]; struct LO *pnext; } LO;
typedef struct SW { int pad[0x24]; LO *pfirst; } SW;
typedef struct T { int pad[2]; SW *psw; } T;
int func_0012D058(T *p)
{
    LO *q = p->psw->pfirst;
    while (q) {
        if (q == (LO *)p)
            return 1;
        q = q->pnext;
    }
    return 0;
}
