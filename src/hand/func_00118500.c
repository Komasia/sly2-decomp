/* Sets three fields of a small record (+0x34, +0x38 and +0x0); called by 0x1CAEC8. */
typedef struct X { int n0; char pad[0x30]; int n34; int n38; } X;

void func_00118500(X *px, int n34, int n38, int n0)
{
    px->n34 = n34;
    px->n38 = n38;
    px->n0 = n0;
}
