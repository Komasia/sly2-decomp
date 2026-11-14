/* class: the second emitter class (SafeHouse emitter.cpp maps 0x259440 to 0x2589A8, 0x259330 / 0x2593B8 to
 * OffKind0 / OffKind1; its descriptor 0x2B1FA0): the particle kind - 0 / 1 make their blocks. */
typedef struct EMITTER EMITTER;
void func_00259330(EMITTER *pemitter, int f);   /* OffKind0's twin */
void func_002593B8(EMITTER *pemitter, int f);   /* OffKind1's twin */

void func_00259440(EMITTER *pemitter, int kind)
{
    switch (kind) {
    case 0:
        func_00259330(pemitter, 1);
        break;
    case 1:
        func_002593B8(pemitter, 1);
        break;
    }
}
