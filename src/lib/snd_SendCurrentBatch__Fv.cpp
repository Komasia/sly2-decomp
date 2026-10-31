// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
extern "C" {
extern int gCommandFillBuffer, D_002C46B8;
extern int *gSndCommandBuffePtr[2];
extern int gCommandBuffeBytesAvail[2];
extern void *gReturnValuesPtr[2];
extern char D_00443800[];
extern char D_002AA1C8[];
void func_00231F38(void *, int, int *);
void func_0021EC18(const char *, ...);
void func_00234CA0(int);
int func_00237488(void *);
int func_00237288(void *, int, int, void *, int, void *, int, void *, void *);
}

void snd_SendCurrentBatch()
{
    func_00231F38(gReturnValuesPtr[gCommandFillBuffer], *gSndCommandBuffePtr[gCommandFillBuffer], gSndCommandBuffePtr[gCommandFillBuffer]);
    while (func_00237488(D_00443800)) {
        if (!D_002C46B8)
            func_0021EC18(D_002AA1C8);
        func_00234CA0(0);
    }
    func_00237288(D_00443800, 0x4D, 1, gSndCommandBuffePtr[gCommandFillBuffer], 0x1000 - gCommandBuffeBytesAvail[gCommandFillBuffer],
                  gReturnValuesPtr[gCommandFillBuffer], *gSndCommandBuffePtr[gCommandFillBuffer] * 4 + 8, 0, 0);
    int c = gCommandFillBuffer != 1;
    gCommandFillBuffer = c;
    *gSndCommandBuffePtr[c] = 0;
    gCommandBuffeBytesAvail[c] = 0xFFC;
}
