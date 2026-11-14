/* The splice GC's heap heads saved (SafeHouse splicemap.cpp: "0x128148: the GC's heap heads saved"; a world pass):
 * each of the six heads copied to its saved slot. */
extern int D_002DD280, D_002DD288;
extern int D_002DD290, D_002DD298;
extern int D_002DD2A0, D_002DD2A8;
extern int D_002DD2B0, D_002DD2B8;
extern int D_002DD2C0, D_002DD2C8;
extern int D_002DD2D0, D_002DD2D8;

void func_00128148(void)
{
    D_002DD288 = D_002DD280;
    D_002DD2A8 = D_002DD2A0;
    D_002DD298 = D_002DD290;
    D_002DD2B8 = D_002DD2B0;
    D_002DD2C8 = D_002DD2C0;
    D_002DD2D8 = D_002DD2D0;
}
