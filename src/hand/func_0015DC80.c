/* func_0015DC80: init a screen fade (cid 0x74): always active (func_001A6CA8 kind 1) with update flags 0xA added. LO +0x40
 * holds the update flags inline (bit 0 set) while the object is not in the update table, else it points at its
 * update entry, whose first word holds them (SafeHouse lo.h grfUpd / iupd). */
struct LO { char pad[0x40]; unsigned int grfUpd; };
void InitLo__FP2LO(void *plo);
void func_001A6CA8(void *plo, int st);   /* SafeHouse: the activation kind (option 14) */
void func_0015DC80(struct LO *plo)
{
    unsigned int grfUpd;
    InitLo__FP2LO(plo);
    func_001A6CA8(plo, 1);
    grfUpd = plo->grfUpd;
    if ((grfUpd ^ 1) & 1) *(int *)grfUpd |= 0xA;
    else plo->grfUpd = grfUpd | 0xA;
}
