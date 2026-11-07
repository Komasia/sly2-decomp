typedef int TI __attribute__((mode(TI)));
typedef struct CRef { int m_tagk; int m_tag; } CRef;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void InitTag__4CRef(CRef *pref, int tagk);
void func_00129248(CRef *pref, TI vec);
TI ConvertPos__FP2LOT0G9VU_VECTOR(int a, int b, TI v);
CRef *func_00125000(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    func_00129248(&ref, ConvertPos__FP2LOT0G9VU_VECTOR(aref[0].m_tag, aref[1].m_tag, *(TI *)aref[2].m_tag));
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
