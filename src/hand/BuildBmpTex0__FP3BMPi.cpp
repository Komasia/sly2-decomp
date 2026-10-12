typedef unsigned long ulong;
struct TEX0 {
    ulong TBP0 : 14; ulong TBW : 6; ulong PSM : 6; ulong TW : 4; ulong TH : 4; ulong TCC : 1;
    ulong TFX : 2; ulong CBP : 14; ulong CPSM : 4; ulong CSM : 1; ulong CSA : 5; ulong CLD : 3;
};
struct BMP { int pad[2]; unsigned short cx; unsigned short cy; unsigned char psm; unsigned char cbw; char pad2[0x20 - 0xE]; TEX0 tex0; };
extern "C" int func_001703C0(int n);
void BuildBmpTex0(BMP *pbmp, int tbp)
{
    pbmp->tex0.TBP0 = tbp;
    pbmp->tex0.TBW = pbmp->cbw;
    pbmp->tex0.PSM = pbmp->psm;
    pbmp->tex0.TW = func_001703C0(pbmp->cx);
    pbmp->tex0.TH = func_001703C0(pbmp->cy);
    pbmp->tex0.TCC = 1;
}
