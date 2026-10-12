#ifndef GIFS_H
#define GIFS_H
#include "dmas.h"

/* GIF packet builder */
class GIFS : public DMAS
{
public:
    /* 0x1c */ QW *m_pqwPrim;
    /* 0x20 */ uint m_creg;
    /* 0x24 */ uint m_cregAll;

    GIFS();
    void AddPrimEnd();
    virtual void EndPrim(int fEOP);
    void CheckReg(int fExpectPack, int regExpect);
    void AddPrimBulk(int prim, int c, int creg, ulong regs, QW **paqwBulk);
    void AddPrimPack(int prim, int creg, ulong regs);
    void AddGifTag(int prim, int c, int creg, ulong regs, uint fEOP);
    void PackRGBA(uint rgba);
    void PackUV(int u, int v);
    void PackSTQ(float s, float t, float q);
    void PackXYZ(int x, int y, int z);
    void PackXYZF(int x, int y, int z, int fog);
    void PackAD(long a, long d);
    void AddPrimList(int creg, ulong regs);
    void ListRGBAQ(uint rgba, float q);
    void ListUV(int u, int v);
    void ListXYZ(int x, int y, int z);
    void ListXYZF(int x, int y, int z, int fog);
    void AddImage(int cqw);
};
#endif
