/* func_00162050: the state mask of the task states an object's option 0x1050 lists (up to 6). */
typedef struct CRef { int m_tagk; int m_tag; } CRef;
void func_002013D8(CRef *pref, void *plo, int eopid, int cMax, int *pc, int *an);
int func_00161FF0(int cnState, int *anState);
void Decref(CRef *pref) asm("Decref__4CRef");
int func_00162050(void *plo)
{
    int anState[8];
    CRef ref;
    int cnState;
    int grfState;
    func_002013D8(&ref, plo, 0x1050, 6, &cnState, anState);
    grfState = func_00161FF0(cnState, anState);
    Decref(&ref);
    return grfState;
}
