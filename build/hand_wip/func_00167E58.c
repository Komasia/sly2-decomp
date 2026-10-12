/* far: RGBA->16bit conversion loop; target has extra value copies (t9/t7) and base+offset operand order */
typedef struct { unsigned char r, pad0[3], g, pad1[3], b, pad2[3], a, pad3[3]; } CQW;
struct X { int pad[2]; int iA; int iB; int iEnd; int ib14; int ib18; int pad2; int ib20; int ib24; };
struct S { char pad[0x3010]; char *pbBase; char pad2[0x3070 - 0x3014]; struct X x; };
static __inline__ unsigned short Rgba16(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return ((g >> 3) << 5) | (r >> 3) | ((b >> 3) << 10) | ((a >> 7) << 15);
}
void func_00167E58(struct S *p)
{
    struct X *px = &p->x;
    char *pbBase = p->pbBase;
    CQW *pqwEnd = (CQW *)p + px->iEnd;
    CQW *pqwB = (CQW *)p + px->iB;
    unsigned char *pbAlpha = (unsigned char *)(pbBase + px->ib24);
    CQW *pqwA = (CQW *)p + px->iA;
    unsigned short *ps1 = (unsigned short *)(pbBase + px->ib14);
    unsigned short *ps2 = (unsigned short *)(pbBase + px->ib18);
    unsigned char *pb2 = (unsigned char *)(pbBase + px->ib20);
    for (; pqwB < pqwEnd; pqwB++, pqwA++) {
        *ps1++ = Rgba16(pqwA->r, pqwA->g, pqwA->b, pqwA->a);
        *ps2++ = Rgba16(pqwB->r, pqwB->g, pqwB->b, pqwA->a);
        *pbAlpha++ = pqwB->a;
        if (px->ib20)
            *pb2++ = pqwA->a;
    }
}
