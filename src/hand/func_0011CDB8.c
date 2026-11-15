/* Clears three counters at +0xC..+0x14 (Sly 3 maps it to POOLSTATE::Reset). */
typedef struct X { char pad[0xC]; int nC; int n10; int n14; } X;

void func_0011CDB8(X *px)
{
    px->n14 = 0;
    px->n10 = 0;
    px->nC = 0;
}
