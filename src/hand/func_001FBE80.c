struct A { char pad[0x40]; int h; char pad2[4]; float g; };
void func_00232568(int h, int a, int b, int c);
void func_00232350(int h);
void func_001FBE80(struct A *p)
{
    if (p->g > 0.0f)
        func_00232568(p->h, -4, (int)(p->g * 240.0f), 2);
    else
        func_00232350(p->h);
}
