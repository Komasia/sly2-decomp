/* class: ALO (SafeHouse loaders.cpp, orig 0x001F7B98: the object's child of class 0x12 with oid 391 (0x187), made
 * when it has none). */
struct LO;
struct SW;
extern struct SW g_sw;
struct LO *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int grf, int oid, struct LO *ploContext);
struct LO *PloNew__F3CIDP2SW3OIDi(int cid, struct LO *ploParent, int oid, int n);

void func_001F7B98(struct LO *palo)
{
    if (PloFindSwNearest__FP2LO3OIDii(&g_sw, 2, 0x187, palo) == 0) {
        PloNew__F3CIDP2SW3OIDi(0x12, palo, 0x187, -1);
    }
}
