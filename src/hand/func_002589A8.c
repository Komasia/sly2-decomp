/* class: EMITTER (SafeHouse emitter.cpp: the option setter 0x2589A8 "the particle kind: 0 / 1 make their blocks";
 * its descriptor 0x2B13E0): kind 0 OffKind0, kind 1 OffKind1 (with 1), any other nothing. */
typedef struct EMITTER EMITTER;
void OffKind0(EMITTER *pemitter, int f);
void OffKind1(EMITTER *pemitter, int f);

void func_002589A8(EMITTER *pemitter, int kind)
{
    switch (kind) {
    case 0:
        OffKind0(pemitter, 1);
        break;
    case 1:
        OffKind1(pemitter, 1);
        break;
    }
}
