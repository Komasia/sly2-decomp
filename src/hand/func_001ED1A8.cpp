struct RGBA { unsigned char r, g, b, a;
  RGBA() {}
  RGBA(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_) { r = r_; g = g_; b = b_; a = a_; }
};
struct BF { unsigned short r : 5; unsigned short g : 5; unsigned short b : 5; unsigned short a : 1; };
union U { unsigned short w; BF bf; };
extern "C" { extern int D_003E12C8; void func_001ED278(RGBA *prgba); void func_001ED1A8(U *pu); }
static inline U Pack(RGBA c) { U u; u.bf.r = c.r >> 3; u.bf.g = c.g >> 3; u.bf.b = c.b >> 3; u.bf.a = c.a >> 7; return u; }
void func_001ED1A8(U *pu)
{
    if (!D_003E12C8) return;
    RGBA c(pu->bf.r << 3, pu->bf.g << 3, pu->bf.b << 3, pu->bf.a ? 0xFF : 0);
    func_001ED278(&c);
    *pu = Pack(c);
}
