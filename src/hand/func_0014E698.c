void SetVectorCylind__Ffff(void *a, void *b, float x, float y, float z);
// name: SafeHouse port (CalcCmAdjust)
void CalcCmAdjust__FP2CMP6CPDEFI(void *a, char *b)
{
    SetVectorCylind__Ffff(a, b, *(float *)(b + 0x30) + 3.14159265f, *(float *)(b + 0x34), 0.0f);
}
