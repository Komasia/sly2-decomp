typedef int qword __attribute__((mode(TI)));
struct P { int pad[7]; float g1C; };
int func_0014F898(struct P *p, qword v, float g, float *pu)
{
    qword l, one;
    float l2, r, r2, d2;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(v));
    r = g * p->g1C;
    __asm__("qmfc2.ni %0, %1" : "=r"(l2) : "j"(l));
    r2 = r * r;
    if (r2 < l2)
        return 0;
    d2 = r - p->g1C * 400.0f;
    d2 = d2 * d2;
    if (d2 < l2)
        *pu = (r2 - l2) / (r2 - d2);
    else
        *pu = 1.0f;
    return 1;
}
