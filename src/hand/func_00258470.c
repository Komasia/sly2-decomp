/* class: FONTBRX, a font (callers: DrawDancePrompts__FP7FONTBRX, DrawGadgetIcons__FP7FONTBRX, DrawMarkerLabel): a
 * setter of its +0x14. */
struct FONTBRX {
    /* 0x00 */ char pad0[0x14];
    /* 0x14 */ int n14;
    /* 0x18 */ int n18;
};

void func_00258470(struct FONTBRX *pfont, int n)
{
    pfont->n14 = n;
}
