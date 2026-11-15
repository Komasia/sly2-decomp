// The attach controller's (kind 6, made by 0x12DDB0) Fetch: the record's value becomes that of the other record's
// world matrix times the offset matrix, in the record's parent space; no velocity, state 3 (fixed + velocity).
// Layout: SafeHouse port (lo.h XF: matWorld +0x40, state +0x9A, pxfRef +0xA0, aseg +0xC0).
typedef int qword __attribute__((mode(TI)));
struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16)));
struct XFW { char pad[0x40]; MATRIX4 matWorld; };
struct Y { char pad[0x9A]; short state; char pad2[0xA0 - 0x9C]; XFW *pxfRef; char pad3[0xC0 - 0xA4]; qword pos0; qword vel0; };
struct XX { char pad[8]; Y *pxf; char pad2[0x1C - 0xC]; XFW *pxfOther; MATRIX4 mat; };
extern qword D_002A2DD0;   // the zero vector
extern "C" {
MATRIX4 InverseAffineMatrix4(const MATRIX4 &mat) asm("InverseAffineMatrix4__FP7MATRIX4");
MATRIX4 MulMatrix4(const MATRIX4 &a, const MATRIX4 &b) asm("MulMatrix4__FP7MATRIX4T0Pv");
qword VecXfValue(Y *pxf, MATRIX4 mat) asm("VecXfValue__FP2XFP7MATRIX4");
void func_0012DEF0(XX *pctrl);
}
void func_0012DEF0(XX *pctrl)
{
    MATRIX4 mat;
    if (pctrl->pxf->pxfRef)
        mat = MulMatrix4(MulMatrix4(InverseAffineMatrix4(pctrl->pxf->pxfRef->matWorld), pctrl->pxfOther->matWorld), pctrl->mat);
    else
        mat = MulMatrix4(pctrl->pxfOther->matWorld, pctrl->mat);
    Y *pxf = pctrl->pxf;
    pxf->pos0 = VecXfValue(pxf, mat);
    pctrl->pxf->vel0 = D_002A2DD0;
    pctrl->pxf->state = 3;
}
