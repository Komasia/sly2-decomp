struct EA { float t; int pad[3]; };
struct ASEG { char pad[0xa0]; int cea; EA *aea; };
struct ASEGA { char pad[0x14]; ASEG *paseg; char pad2[4]; float t; char pad3[0x40 - 0x20]; float svt; char pad4[0x50 - 0x44]; int ieaCur; };
void UpdateAsegaIeaCur(ASEGA *pasega)
{
    ASEG *paseg = pasega->paseg;
    int cea = paseg->cea;
    int iea;
    if (cea == 0) return;
    if (pasega->svt >= 0.0f) {
        for (iea = 0; iea < cea; iea++) {
            if (pasega->t <= pasega->paseg->aea[iea].t) break;
        }
        pasega->ieaCur = iea;
    } else {
        iea = cea;
    L2:
        iea--;
        if (iea >= 0) {
            if (pasega->paseg->aea[iea].t <= pasega->t)
                goto D2;
            goto L2;
        }
    D2:
        pasega->ieaCur = iea + 1;
    }
}
