typedef unsigned long ulong;
typedef int qword __attribute__((mode(TI)));
struct VEC3 { float x, y, z; VEC3() {} };
struct CLR { unsigned int n; CLR() {} };
struct CLR3 { CLR a[3]; };
struct DMAS { int a[12]; };
struct O { char pad[0x3EA0]; ulong tex0; };
extern "C" {
struct SRC { float ag[3]; char aclr[3][16]; };
extern struct SRC D_003E12F4;
extern int D_002C3680[];
extern int D_002DE598;
void func_0011DFA0(void *, VEC3 *);
int func_00170548(void *, int);
void func_00166920(DMAS *);
void func_00157330(DMAS *, int, void *);
void func_001574B8(DMAS *);
void func_00170650(int, int, int, int, int, int, DMAS *);
void func_00157500(DMAS *, int, void *);
void func_00166BD8(DMAS *, int, int, int);
void func_00166E90(DMAS *, int, int);
void func_00166968(DMAS *);
void func_001576B0(DMAS *);
void func_00157348(DMAS *, int, int *);
void func_0016F8B8(int, int);
void func_001EA9F0(O *p, void *pbs);
}
static inline void ClearClr(CLR *pc)
{
    pc->n = 0;
}
static inline void SetClr(CLR *pc, float g, float gA, unsigned int rgb)
{
    float h = gA * 128.0f;
    pc->n = rgb | ((int)(g * h) << 24);
}
void func_001EA9F0(O *p, void *pbs)
{
    if (!pbs && !(p->tex0 & (0x3FFFL << 37)))
        return;
    {
    float ag[3];
    CLR argb[3];
    VEC3 v;
    int i;
    {
        char *pclr = D_003E12F4.aclr[0];
        float *pg = D_003E12F4.ag;
        for (i = 0; i < 3; i++) {
            func_0011DFA0(pclr, &v);
            pclr += 0x10;
            ag[i] = *pg++ * 0.003921569f;
            argb[i].n = (int)v.x | ((int)v.y << 8) | ((int)v.z << 16);
        }
    }
    CLR aclr[256];
    {
        int n = 0;
        CLR *pc = aclr;
        int k;
        for (k = 0; k < 0x100; k += 0x20) {
            int j;
            for (j = 0; j < 4; j++) {
                int m;
                for (m = 0; m < 8; m++) {
                    int a = (n & 0x7F) - 1;
                    float g;
                    if (!(a > -1))
                        a = 0;
                    g = a * 0.007936508f;
                    g = (g > 0.0f) ? g : 0.0f;
                    switch (n & 0x81) {
                    case 0x81:
                        SetClr(pc++, g, ag[2], argb[2].n);
                        break;
                    case 0x80:
                        SetClr(pc++, g, ag[0], argb[0].n);
                        break;
                    case 1:
                        SetClr(pc++, g, ag[1], argb[1].n);
                        break;
                    case 0:
                        ClearClr(pc++);
                        break;
                    }
                    n++;
                }
                n += D_002C3680[j];
            }
        }
    }
    DMAS dmas;
    qword aqw[0x80];
    int x;
    if (pbs)
        p->tex0 = ((ulong)func_00170548(pbs, 4) << 37) | 0x2000000001B00000L;
    func_00166920(&dmas);
    func_00157330(&dmas, 0x80, aqw);
    func_001574B8(&dmas);
    func_00170650((int)((p->tex0 >> 37) & 0x3FFF), 1, 0, 0x10, 0x10, 0x40, &dmas);
    func_00157500(&dmas, 0x40, aclr);
    func_00166BD8(&dmas, 0, 1, 14);
    func_00166E90(&dmas, 0x3F, 0);
    func_00166E90(&dmas, 0x61, 0);
    func_00166968(&dmas);
    func_001576B0(&dmas);
    func_00157348(&dmas, 0, &x);
    func_0016F8B8(D_002DE598, x);
    }
}
