struct RGBA { unsigned char r, g, b, a; };
struct BF { unsigned short r : 5; unsigned short g : 5; unsigned short b : 5; unsigned short a : 1; };
union U { unsigned short w; struct BF bf; };
extern int D_003E12C8;
void func_001ED278(struct RGBA *prgba);
void func_001ED1A8(union U *pu)
{
    struct RGBA c;
    if (!D_003E12C8) return;
    { unsigned short w = pu->w; int a = 0; c.r = pu->bf.r << 3; c.g = (w >> 2) & 0xF8; c.b = (w >> 7) & 0xF8; if (w & 0x8000) a = 0xFF; c.a = a;
 }
    func_001ED278(&c);
    {
        struct RGBA c2 = c;
        pu->w = (c2.r >> 3) | ((c2.g << 2) & 0x3E0) | ((c2.b >> 3) << 10) | ((c2.a >> 7) << 15);
    }
}
