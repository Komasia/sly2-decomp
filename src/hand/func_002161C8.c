struct S { char pad[8]; void *x8; char padc[0x7C]; float f88; };
void func_00215CA8(struct S *p, int i);
int func_00215D40(struct S *p);
float func_00216B80(void *p, int ch);
float func_002161C8(struct S *p)
{
    float fMax = 0.0f;
    float fCur = fMax;
    int ch;
    func_00215CA8(p, 0);
    while ((ch = func_00215D40(p)) != 0) {
        if (ch == 10) {
            fMax = (fMax > fCur) ? fMax : fCur;
            fCur = 0.0f;
        } else {
            fCur += func_00216B80(p->x8, ch) * p->f88;
        }
    }
    fMax = (fMax > fCur) ? fMax : fCur;
    return fMax;
}
