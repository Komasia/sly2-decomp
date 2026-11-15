// BuildBlipAqwGifs (Sly 1 blip.c name, by module order): a blip GIF packet template into aqw: the alpha blend mode
// n (1 normal, 2 clamped add) in ALPHA_1 (0x42), TEST_1 (0x47), then the blip primitive registers (0x424242412E).
#include "gifs.h"
extern "C" void func_00138F08(int n, QW *aqw)
{
    GIFS gifs;
    gifs.AllocStatic(4, aqw);
    gifs.AddPrimPack(0, 1, 0xe);
    gifs.PackAD(0x47, 0x7180b);
    gifs.PackAD(0x42, ((long)n << 2) | 0x40);
    gifs.AddPrimBulk(0x54, 0, 10, 0x424242412eUL, 0);
    gifs.EndDmaCnt();
}
