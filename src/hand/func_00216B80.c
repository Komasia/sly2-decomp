struct S { char pad[0x1C]; float *ag; };
int PglyffFromCh__8CFontBrxc(struct S *p, unsigned char ch);
float func_00216B80(struct S *p, unsigned char ch)
{
    int i = PglyffFromCh__8CFontBrxc(p, ch);
    return i ? p->ag[i - 1] : 0.0f;
}
