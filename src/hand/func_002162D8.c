struct S { char pad[0x64]; float f64; float f68; };
void *func_002333B4(void *p, int c, int n);
void func_002162D8(struct S *p, float *m, float *v)
{
    func_002333B4(m, 0, 0x40);
    m[0] = v[0] * 0.8f;
    m[1] = v[1] * 0.454545454545f;
    m[4] = v[2] * 0.8f;
    m[5] = v[3] * 0.454545454545f;
    m[8] = v[4] * 0.8f + p->f64 + 786432.0f;
    m[9] = v[5] * 0.454545454545f + p->f68 + 786432.0f;
    m[10] = 1.0f;
    m[15] = 1.0f;
}
