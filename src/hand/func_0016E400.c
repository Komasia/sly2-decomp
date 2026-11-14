/* class: a render pass's finish (the render-pass table 0x2BDD88 of {setup, finish} pairs, VIFS argument; setup
 * 0x16E3C8): the common finish 0x16E228, then the 2 GIF quadwords at 0x2DF720 sent (0x16E318). */
typedef struct VIFS VIFS;   /* vifs.h (a DMAS packet builder) */
typedef struct QW { int an[4]; } QW;
void func_0016E228(VIFS *pvifs);
void func_0016E318(VIFS *pvifs, int cqw, QW *aqw);
extern QW D_002DF720[];

void func_0016E400(VIFS *pvifs)
{
    func_0016E228(pvifs);
    func_0016E318(pvifs, 2, D_002DF720);
}
