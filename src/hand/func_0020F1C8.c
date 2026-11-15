typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { float x, y, z; } V3;
typedef union { qword q; V3 v; } UV;
extern char g_lmZeroOne[];
/* the world's lighting fields (see sw.h): the change count, the light colour (HSV), scale and midtone, and what
 * they make */
struct SW { char pad[0x3D5C]; int cLightChange; char pad2[0x3E10 - 0x3D60]; V3 hsvLight; int pad3; float gLightScale; float gMidtone; V3 rgbLight; float uMidtone; int fBrighten; };
void RgbFromHsv__FP6VECTORT0(V3 *pin, UV *pout);
void func_001ED2D8(UV *pv);
float GLimitLm(void *plm, float g) asm("GLimitLm__FP2LMf");
/* func_0020F1C8 (0x20F1C8): recomputes the world's lighting: the light colour from HSV (saturation and value out of
 * 255) scaled by gLightScale / 255 (0x1ED2D8 on it), the midtone out of 255 (raised by 0.3 and clamped to [0, 1]
 * with fBrighten), and the change counted. */
void func_0020F1C8(struct SW *psw)
{
    float r255 = 1.0f / 255.0f;
    V3 hsv;
    UV rgb;
    U u;
    qword r;
    hsv.x = psw->hsvLight.x;
    hsv.y = psw->hsvLight.y * r255;
    hsv.z = psw->hsvLight.z * r255;
    RgbFromHsv__FP6VECTORT0(&hsv, &rgb);
    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(psw->gLightScale * r255));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(rgb.q), "j"(u.q));
    rgb.q = r;
    func_001ED2D8(&rgb);
    psw->rgbLight = rgb.v;
    psw->uMidtone = psw->gMidtone * r255;
    if (psw->fBrighten)
        psw->uMidtone = GLimitLm(g_lmZeroOne, psw->uMidtone + 0.3f);
    psw->cLightChange++;
}
