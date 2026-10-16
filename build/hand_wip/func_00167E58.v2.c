/* far: RGBA->16bit conversion loop; target has extra value copies (t9/t7) and base+offset operand order */
typedef struct { unsigned char r, pad0[3], g, pad1[3], b, pad2[3], a, pad3[3]; } CQW;
struct X { int pad[2]; int iA; int iB; int iEnd; char *ib14; char *ib18; int pad2; char *ib20; char *ib24; };
struct S { char pad[0x3010]; int pbBase; char pad2[0x3070 - 0x3014]; struct X x; };
static __inline__ unsigned short Rgba16(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return ((g >> 3) << 5) | (r >> 3) | ((b >> 3) << 10) | ((a >> 7) << 15);
}
void func_00167E58(struct S *p)
{
    struct X *px = &p->x;
    int pbBase = p->pbBase;
    CQW *pqwEnd = (CQW *)p + px->iEnd;
    CQW *pqwB = (CQW *)p + px->iB;
    CQW *pqwA = (CQW *)p + px->iA;
    unsigned char *pbAlpha = (unsigned char *)(px->ib24 + pbBase);
    unsigned short *ps1 = (unsigned short *)(px->ib14 + pbBase);
    unsigned short *ps2 = (unsigned short *)(px->ib18 + pbBase);
    unsigned char *pb2 = (unsigned char *)(px->ib20 + pbBase);
    unsigned short c1, c2;
    for (; pqwB < pqwEnd; pqwB++, pqwA++) {
        unsigned short *pd1, *pd2;
        pd1 = ps1++;
        pd2 = ps2++;
        *pd1 = c1 = Rgba16(pqwA->r, pqwA->g, pqwA->b, pqwA->a);
        *pd2 = c2 = Rgba16(pqwB->r, pqwB->g, pqwB->b, pqwA->a);
        *pbAlpha++ = pqwB->a;
        if (px->ib20)
            *pb2++ = pqwA->a;
    }
}
