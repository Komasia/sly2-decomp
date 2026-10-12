extern unsigned char D_002C40C8[];
double func_002452C0(double, double);
double func_0011D740(double);
unsigned char func_0021E0D8(double g, int a, int b)
{
    if (a < b || a - 15 < b) {
        int i;
        g = func_0011D740(g * func_002452C0(10.0, (double)-b));
        i = (int)(g - func_0011D740(g * 0.1) * 10.0);
        return D_002C40C8[i];
    } return 0;
}
