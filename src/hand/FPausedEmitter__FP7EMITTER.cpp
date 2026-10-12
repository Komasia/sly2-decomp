struct CLOCK { float t; float dt; };
extern CLOCK D_002DDED0;
struct EMITTER { char pad[0xF0]; int k; int c; char pad2[0x148 - 0xF8]; float tUnpause; };
int FPausedEmitter(EMITTER *pemitter)
{
    if (D_002DDED0.t < pemitter->tUnpause)
        return 1;
    switch (pemitter->k) {
    case 0:
    case 1:
        if (pemitter->c == 0)
            return 1;
    }
    return 0;
}
