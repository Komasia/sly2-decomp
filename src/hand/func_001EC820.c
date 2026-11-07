
struct E { int oid; char pad[0x28]; };
extern int D_003DCFE8;
extern struct E *D_003DCFEC;
// name: SafeHouse port (PshdFindShader)
struct E *PshdFindShader__F3OID(int oid)
{
    int i;
    if (oid == -1) return 0;
    for (i = 0; i < D_003DCFE8; i++) {
        if (D_003DCFEC[i].oid == oid) return &D_003DCFEC[i];
    }
    return 0;
}
