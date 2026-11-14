/* libsif (no direct callers): the first record's +0x10 copied to the second's +0x8. */
typedef struct SIFA { char pad0[0x10]; int n10; } SIFA;
typedef struct SIFB { char pad0[0x8]; int n8; } SIFB;

void func_0023AAB8(SIFA *pa, SIFB *pb)
{
    pb->n8 = pa->n10;
}
