/* GC mark: tagk 0x1F/0x22 push to lists, 0x20 marks the CRef itself. Diff: target keeps pref/pobj in a1 and copies pgc to a2;
   ours copies pref->a2, pgc->a1 (reg alloc only, ~49 lines due to shift) */
typedef struct OBJ { int a; unsigned n : 31; unsigned fMark : 1; } OBJ;
typedef struct CRef { int m_tagk; OBJ *pobj; } CRef;
typedef struct GC { int pad[3]; int cA; OBJ **apA; int cB; OBJ **apB; } GC;
extern unsigned int D_002DD598;
void func_001285D8(GC *pgc, OBJ *pobj)
{
    switch (((CRef *)pobj)->m_tagk) {
    case 0x1F:
        pobj = ((CRef *)pobj)->pobj;
        if (pobj->fMark != D_002DD598) {
            pobj->fMark = D_002DD598;
            pgc->apA[pgc->cA++] = pobj;
        }
        break;
    case 0x22:
        pobj = ((CRef *)pobj)->pobj;
        if (pobj->fMark != D_002DD598) {
            pobj->fMark = D_002DD598;
            pgc->apB[pgc->cB++] = pobj;
        }
        break;
    case 0x20:
        pobj->fMark = D_002DD598;
        break;
    }
}
