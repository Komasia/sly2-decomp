struct S { char pad[0x110]; int x; };
void InitXfm__FP3XFM(struct S *p);
void func_00227350(struct S *p)
{
    InitXfm__FP3XFM(p);
    p->x = -1;
}
