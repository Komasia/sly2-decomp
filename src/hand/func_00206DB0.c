/* func_00206DB0 (0x206DB0): entering guard mode 34 / 37: each special guard class (D_002C3D10) that has objects in
 * the world (including inactive ones: search grf 0x605) becomes an excluded target class (0x208920). */
extern int D_002C3D10[];   /* the special guard classes */
extern char g_sw[];
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *psw, int grffso, int cid, int a, int cploMax, int aplo);
void func_00208920(void *pguard, int cid);   /* adds an excluded target class */
void func_00206DB0(void *pguard)
{
    unsigned int icid;
    for (icid = 0; icid < 5; icid++) {
        int cid = D_002C3D10[icid];
        if (CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(g_sw, 0x605, cid, 0, 0, 0))
            func_00208920(pguard, cid);
    }
}
