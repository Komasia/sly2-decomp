struct G { char pad[0x40]; };
struct S { char pad[0x14]; struct G *ag; };
int PglyffFromCh__8CFontBrxc(struct S *p, unsigned char ch);
struct G *func_00216B40(struct S *p, unsigned char ch)
{
    int i = PglyffFromCh__8CFontBrxc(p, ch);
    return i ? &p->ag[i] : 0;
}
