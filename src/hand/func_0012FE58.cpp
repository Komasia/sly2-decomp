/* GetAsegChannelTarget: the object an ASEG channel drives (its oid, looked up nearest to palo, else to the ASEG
 * itself) and that object's transform record isub (null when the object is missing). SafeHouse port (asega.h). */
struct ASEGCHN { int oid : 20; int isub : 10; int pad : 2; };   // field: SafeHouse port (aseg.h)
struct O {
    char pad[0xC];
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
    virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
    virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50();
    virtual int Get(int isub);   // vt slot 51: the object's isub-th transform record
};
extern char g_sw[];
extern "C" {
O *PloFindSwNearest(void *pg, int grfFind, int oid, void *ploNear) asm("PloFindSwNearest__FP2LO3OIDii");
void GetAsegChannelTarget(void *paseg, void *palo, ASEGCHN *pchn, O **ppalo, int *ppxf) asm("GetAsegChannelTarget__FP4ASEGP3ALOP7ASEGCHNPP3ALOPP2XF");
}
// name: SafeHouse port (GetAsegChannelTarget)
void GetAsegChannelTarget(void *paseg, void *palo, ASEGCHN *pchn, O **ppalo, int *ppxf)
{
    if (palo)
        *ppalo = PloFindSwNearest(g_sw, 1, pchn->oid, palo);
    else
        *ppalo = PloFindSwNearest(g_sw, 4, pchn->oid, paseg);
    if (!*ppalo)
        *ppxf = 0;
    else
        *ppxf = (*ppalo)->Get(pchn->isub);
}
