// GIFS::AddPrimPack (Sly 1 gifs.c): close the open primitive and start a PACKED GIF tag (NLOOP filled in at its end)
// for prim with creg registers (regs: their 4-bit descriptors).
#include "gifs.h"

void GIFS::AddPrimPack(int prim, int creg, ulong regs)
{
    EndPrim(0);
    ulong tag = ((ulong)creg << 60) | (1L << 46);
    register QW *pqw __asm__("$3") = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->aul[0] = ((ulong)prim << 47) | tag;
    pqw->aul[1] = regs;
    m_creg = creg;
    m_pqwPrim = pqw;
    m_cregAll = 0;
}
