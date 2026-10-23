// Matched by Claude agent (2026-10-23). Both searches are real loops that re-read pasega->paseg / pasega->t (only the
// loads before the loop's first exit test get hoisted, which gives the target's paseg/cea copies). The `== 0` keeps
// fast-math from folding !(a <= b) into a < b.
struct EA { float t; int pad[3]; };
struct ASEG { char pad[0xa0]; int cea; EA *aea; };
struct ASEGA { char pad[0x14]; ASEG *paseg; char pad2[4]; float t; char pad3[0x40 - 0x20]; float svt; char pad4[0x50 - 0x44]; int ieaCur; };
void UpdateAsegaIeaCur(ASEGA *pasega)
{
    ASEG *paseg = pasega->paseg;
    int cea = paseg->cea;
    int iea;
    if (cea == 0)
        return;
    if (pasega->svt >= 0.0f) {
        for (iea = 0; iea < pasega->paseg->cea; iea++)
            if (pasega->t <= pasega->paseg->aea[iea].t)
                break;
        pasega->ieaCur = iea;
    } else {
        iea = cea;
        do
            iea--;
        while (iea >= 0 && (pasega->paseg->aea[iea].t <= pasega->t) == 0);
        pasega->ieaCur = iea + 1;
    }
}
