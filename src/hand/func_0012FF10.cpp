/* PchnFindAseg: the ASEG's position channel that drives palo's record of the given kind (XF +0x94, 1: translation) (fCheck: only
 * channels flagged at bit 30), or null. Layout: SafeHouse port (aseg.h ASEGCHN). */
struct ASEGCHNK { int oid : 20; int isub : 10; unsigned int fDisabled : 1; unsigned int fScalar : 1; };   // field: SafeHouse port (aseg.h ASEGCHN)
struct XF { char pad[0x94]; void *kind /* an XF kind */; };   // +0x94 (SafeHouse lo.h: kind)
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
    virtual XF *Get(int isub);   // vt slot 51: the object's isub-th transform record
};
struct E { ASEGCHNK k; int ptrk; };   // ASEGCHN
struct T { char pad[0x5C]; int cchn; E *achn; };   // ASEG; field: SafeHouse port
struct O2 : O { };
extern "C" E *PchnFindAseg(T *paseg, O *palo, void *kind /* an XF kind */, int fCheck) asm("PchnFindAseg__FP4ASEGP3ALOPvi");
// name: SafeHouse port (PchnFindAseg)
E *PchnFindAseg(T *paseg, O *palo, void *kind /* an XF kind */, int fCheck)
{
    int i;
    for (i = 0; i < paseg->cchn; i++) {
        E *pchn = &paseg->achn[i];
        if (fCheck && !pchn->k.fDisabled)
            continue;
        if (pchn->k.oid != ((int *)palo)[6] /* LO +0x18: oid */)
            continue;
        if (pchn->k.fScalar)
            continue;
        if (palo->Get(pchn->k.isub)->kind == kind)
            return pchn;
    }
    return 0;
}
