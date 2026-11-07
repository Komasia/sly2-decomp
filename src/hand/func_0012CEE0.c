typedef struct LO { int tagk; int pad[6]; struct LO *pother; } LO;
typedef struct SW { int pad[0x24]; LO *pfirst; } SW;
typedef struct T { int pad[2]; SW *psw; } T;
// name: SafeHouse port (CTRL::FFirst)
int FFirst__4CTRL(T *p)
{
    LO *q = p->psw->pfirst;
    if (q == (LO *)p)
        return 1;
    if (q && q->tagk == 5 && q->pother == (LO *)p)
        return 1;
    return 0;
}
