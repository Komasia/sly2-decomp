struct RGBA { unsigned char r, g, b, a; };
void func_00166BD8(void *pgs, int a, int b, int c);
void func_00166E90(void *pgs, int a, int b);
void func_00166C70(void *pgs, int rgba);
void func_00166E08(void *pgs, int x, int y, int z, int w);
void func_001CD5F0(struct RGBA *pc, void *pgs, float x0, float y0, float x1, float y1)
{
    func_00166BD8(pgs, pc->a <= 0xFE ? 0x46 : 6, 5, 0x441EE);
    pc->a = (pc->a + 1) >> 1;
    func_00166E90(pgs, 0x47, 0x31001);
    func_00166E90(pgs, 0x42, 0x44);
    func_00166C70(pgs, *(int *)pc);
    func_00166E08(pgs, (int)((x0 * 0.8f + 1792.0f) * 16.0f), (int)((y0 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    func_00166E08(pgs, (int)((x1 * 0.8f + 1792.0f) * 16.0f), (int)((y1 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
}
