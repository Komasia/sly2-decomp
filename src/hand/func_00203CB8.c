/* func_00203CB8 (0x203CB8), class STEP (the splice method 0x102858): the object's mesh entry with that tag (0x1F6030: its
 * +0xE4 entries) made its step mesh (SetStepMesh), if there is one. */
typedef struct ALO ALO;
void *func_001F6030(ALO *palo, int oid);
void SetStepMesh__FP3ALOPvi(ALO *palo, void *pmesh, int fSnap);

void func_00203CB8(ALO *palo, int oid, int fSnap)
{
    void *pmesh = func_001F6030(palo, oid);

    if (pmesh != 0) {
        SetStepMesh__FP3ALOPvi(palo, pmesh, fSnap);
    }
}
