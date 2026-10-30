struct MSG { int cb; int nKind; };
typedef struct { int c; short *a; } SA;
void *PvAllocSlot__FP8ALLOCREQ(struct MSG *pmsg);
void func_001AE5A0(void *, void *, int);
SA *func_001D8CC8(SA *p1, SA *p2)
{
    struct MSG msg;
    SA *r;
    int c;
    msg.cb = 8;
    msg.nKind = 0x10;
    r = (SA *)PvAllocSlot__FP8ALLOCREQ(&msg);
    c = p1->c + p2->c;
    r->c = c;
    msg.cb = c * 2;
    msg.nKind = 0x10;
    r->a = (short *)PvAllocSlot__FP8ALLOCREQ(&msg);
    func_001AE5A0(r->a, p1->a, p1->c * 2);
    func_001AE5A0(r->a + p1->c, p2->a, p2->c * 2);
    return r;
}
