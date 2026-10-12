/* 9 diffs: register allocation only (target pqw in $v1, ours $a1) */
#include "gifs.h"
void GIFS::AddPrimPack(int prim, int creg, ulong regs)
{
    EndPrim(0);
    ulong tag = ((ulong)creg << 60) | (1L << 46);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->aul[0] = ((ulong)prim << 47) | tag;
    pqw->aul[1] = regs;
    m_creg = creg;
    m_pqwPrim = pqw;
    m_cregAll = 0;
}
