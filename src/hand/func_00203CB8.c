/* class: ALO (the splice method 0x102858: an object and an int): the object's mesh entry of that oid (0x1F6030: its
 * +0xE4 entries) made its step mesh (SetStepMesh), if there is one. */
typedef struct ALO ALO;
void *func_001F6030(ALO *palo, int oid);
void SetStepMesh__FP3ALOPvi(ALO *palo, void *pmesh, int f);

void func_00203CB8(ALO *palo, int oid, int f)
{
    void *pmesh = func_001F6030(palo, oid);

    if (pmesh != 0) {
        SetStepMesh__FP3ALOPvi(palo, pmesh, f);
    }
}
