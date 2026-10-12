struct S { char pad[8]; void *x8; char pad2[0x7C]; float x88; };
void func_00215CA8(struct S *p, int a);
int func_00215D40(struct S *p);
float func_00216B80(void *p, int ch);
float func_00215ED8(struct S *p)
{
    float sum = 0.0f;
    int ch;
    func_00215CA8(p, 0);
    while ((ch = func_00215D40(p)) != 0)
        sum += func_00216B80(p->x8, ch) * p->x88;
    return sum;
}
