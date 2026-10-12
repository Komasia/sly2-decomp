#include "bis.h"

CBinaryInputStream::CBinaryInputStream() : m_grfbis(0)
{
    m_pbRaw = NULL;
    m_pb = NULL;
    m_cbRaw = 0;
    m_cb = 0;
    m_grfDecomp = 0;
    m_cbPending = 0;
    m_cbConsumed = 0;
    m_unk20 = 0;
    m_pbDecomp = NULL;
    m_unk2C = 0;
    m_unk28 = 0;
}

void CBinaryInputStream::Close()
{
    m_pbRaw = NULL;
    m_pb = NULL;
    m_cbRaw = 0;
    m_cb = 0;
    m_grfDecomp = 0;
    m_cbPending = 0;
}

void CBinaryInputStream::Refill()
{
    if (m_cb != 0)
        return;

    if (m_grfbis & 2)
    {
        Decompress();
    }
    else
    {
        Fill();
        m_cb = m_cbRaw;
        m_pb = m_pbRaw;
        m_pbRaw += m_cbRaw;
        m_cbRaw = 0;
    }
    m_cbConsumed += m_cb;
}

int CBinaryInputStream::CbRead(int cb, void *pv)
{
    int cbLeft = cb;
    byte *pb = (byte *)pv;

    if (m_cb < 0)
        return 0;

    while (cbLeft > 0)
    {
        Refill();
        if (m_cb == 0)
        {
            m_cb = -1;
            break;
        }

        int cbCopy = (cbLeft < m_cb) ? cbLeft : m_cb;

        if (pb)
        {
            CopyAb(pb, m_pb, cbCopy);
            pb += cbCopy;
        }

        m_pb += cbCopy;
        m_cb -= cbCopy;
        cbLeft -= cbCopy;
    }

    return cb - cbLeft;
}

void CBinaryInputStream::Read(int cb, void *pv)
{
    CbRead(cb, pv);
}

void CBinaryInputStream::Align(int n)
{
    int pbAligned = ((int)m_pb + (n - 1)) & -n;
    m_cb -= (pbAligned - (int)m_pb);
    m_pb = (byte *)pbAligned;
}

uchar CBinaryInputStream::U8Read()
{
    if (m_cb >= 1)
    {
        uchar b = *m_pb;
        m_pb++;
        m_cb--;
        return b;
    }

    uchar b;
    Read(sizeof(uchar), &b);
    return b;
}

ushort CBinaryInputStream::U16Read()
{
    if (m_cb >= 2)
    {
        ushort u = m_pb[0];
        ushort v = m_pb[1];
        m_pb += 2;
        m_cb -= 2;
        return (v << 8) | u;
    }

    ushort v;
    Read(sizeof(ushort), &v);
    return v;
}

uint CBinaryInputStream::U32Read()
{
    if (m_cb >= 4)
    {
        uint v = m_pb[0] + (m_pb[1] << 8) + (m_pb[2] << 16) + (m_pb[3] << 24);
        m_pb += 4;
        m_cb -= 4;
        return v;
    }

    uint v;
    Read(sizeof(uint), &v);
    return v;
}

char CBinaryInputStream::S8Read()
{
    if (m_cb >= 1)
    {
        char b = *m_pb;
        m_pb += 1;
        m_cb -= 1;
        return b;
    }

    char b;
    Read(sizeof(char), &b);
    return b;
}

short CBinaryInputStream::S16Read()
{
    if (m_cb >= 2)
    {
        short v = m_pb[1] << 8;
        v |= m_pb[0];
        m_pb += 2;
        m_cb -= 2;
        return v;
    }

    short v;
    Read(sizeof(short), &v);
    return v;
}

int CBinaryInputStream::S32Read()
{
    if (m_cb >= 4)
    {
        int v = m_pb[0] + (m_pb[1] << 8) + (m_pb[2] << 16) + (((char *)m_pb)[3] << 24);
        m_pb += 4;
        m_cb -= 4;
        return v;
    }

    int v;
    Read(sizeof(int), &v);
    return v;
}

float CBinaryInputStream::F32Read()
{
    if (m_cb >= 4)
    {
        uint u = m_pb[0] + (m_pb[1] << 8) + (m_pb[2] << 16) + (m_pb[3] << 24);
        m_pb += 4;
        m_cb -= 4;
        return *(float *)&u;
    }
    float f;
    Read(sizeof(float), &f);
    return f;
}

void CBinaryInputStream::Skip(int cb)
{
    Read(cb, NULL);
}

void CBinaryInputStream::SetDecompress(int n, byte *pb)
{
    m_grfbis |= 2;
    m_unk20 = n;
    m_pbDecomp = pb;
}

/* LZSS: 8K window, flag byte per 8 tokens (bit set = literal), references are
 * 13-bit offset + 3-bit length (copies length + 3 bytes). */
void CBinaryInputStream::Decompress()
{
    int cbOut = 0;
    byte *pbOut = m_pbDecomp;
    int cbIn = m_cbRaw;
    byte *pbIn = m_pbRaw;
    int grf = m_grfDecomp;

    if (m_cbPending > 0)
    {
        memcpy(pbOut, pbOut + 0x2000, m_cbPending);
        cbOut = m_cbPending;
    }

    int grfMark = 0xFF00;   /* loop-hoisted constant in the original */
    while (cbOut < 0x2000)
    {
        grf >>= 1;
        if (!(grf & 0x100))
        {
            if (--cbIn < 0)
            {
                Fill();
                if (m_cbRaw <= 0)
                    break;
                pbIn = m_pbRaw;
                cbIn = m_cbRaw - 1;
            }
            grf = *pbIn++ + grfMark;
        }

        if (--cbIn < 0)
        {
            Fill();
            if (m_cbRaw <= 0)
                break;
            pbIn = m_pbRaw;
            cbIn = m_cbRaw - 1;
        }
        int b = *pbIn++;

        if (grf & 1)
        {
            pbOut[cbOut++] = b;
        }
        else
        {
            if (--cbIn < 0)
            {
                Fill();
                pbIn = m_pbRaw;
                cbIn = m_cbRaw - 1;
            }
            int v = b + (*pbIn++ << 8);
            int cb = (v >> 13) + 2;
            int ib = v & 0x1FFF;
            for (; cb >= 0; cb--)
            {
                pbOut[cbOut++] = pbOut[ib++ & 0x1FFF];
            }
        }
    }

    m_pb = pbOut;
    if (cbOut >= 0x2000)
    {
        m_cb = 0x2000;
        m_cbPending = cbOut - 0x2000;
    }
    else
    {
        m_cb = cbOut;
        m_cbPending = 0;
    }
    m_pbRaw = pbIn;
    m_cbRaw = cbIn;
    m_grfDecomp = grf;
}

void CBinaryInputStream::ReadVector(VECTOR *pvec)
{
    Read(sizeof(float) * 3, pvec);
}

void CBinaryInputStream::ReadMatrix(MATRIX3 *pmat)
{
    ReadVector((VECTOR *)pmat->mat[0]);
    ReadVector((VECTOR *)pmat->mat[1]);
    ReadVector((VECTOR *)pmat->mat[2]);
}

void CBinaryInputStream::ReadMatrix4(MATRIX4 *pmat)
{
    ReadMatrix((MATRIX3 *)pmat);
    ReadVector((VECTOR *)pmat->mat[3]);
    pmat->mat[0][3] = 0.0f;
    pmat->mat[1][3] = 0.0f;
    pmat->mat[2][3] = 0.0f;
    pmat->mat[3][3] = 1.0f;
}

void CBinaryInputStream::ReadVector4(VECTOR4 *pvec)
{
    Read(sizeof(VECTOR4), pvec);
}

void CBinaryInputStream::ReadCb12(void *pv)
{
    Read(12, pv);
}

void CBinaryInputStream::ReadCb8(void *pv)
{
    Read(8, pv);
}
