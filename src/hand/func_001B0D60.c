/* class: CID_60, the birds (vt slot 26, a pool row taken again; SafeHouse bird.cpp ResetBirdSlot26): after the base
 * 0x1CB518, placed again. */
struct LO;
void func_001CB518(struct LO *plo, struct LO *pproxy);   /* the base slot 26 */
void PlaceBird__FP2LO(struct LO *plo);

void func_001B0D60(struct LO *plo, struct LO *pproxy)
{
    func_001CB518(plo, pproxy);
    PlaceBird__FP2LO(plo);
}
