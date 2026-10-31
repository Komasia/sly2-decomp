// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef struct CB { void (*fn)(int, long); int pad; long arg; } CB;
extern int gCommBusy;
extern void (*gCdCallback)(int);
extern int gSSRead, gSSReadDone, gLoadingFromFS, gCommandFillBuffer, gCaching, gLoadBusy;
extern int *gSndCommandBuffePtr[2];
extern CB *gSndCommandReturnDefPtr[2];
extern int *gReturnValuesPtr[2];
extern void (*gLoadCB)(int, long);
extern long gLoadUserData;
extern CB gLoadReturnDef;
extern int gSyncBuffer[];
extern unsigned int gLoadReturnValue;
int snd_GotReturns__Fv(void);
void func_00234CA0(int);
void snd_SendCurrentBatch__Fv(void);
int snd_StreamSafeCdSync(int);

int snd_FlushSoundCommands(void)
{
    int i;
    if (gCommBusy && snd_GotReturns__Fv()) {
        if (gLoadingFromFS) {
            if (gLoadCB)
                gLoadCB(gSyncBuffer[1], gLoadUserData);
            gLoadCB = 0;
            gLoadingFromFS = 0;
        } else {
            int other = gCommandFillBuffer != 1;
            for (i = 0; i < *gSndCommandBuffePtr[other]; i++) {
                if (gSndCommandReturnDefPtr[other][i].fn)
                    gSndCommandReturnDefPtr[other][i].fn(gReturnValuesPtr[other][i + 1], gSndCommandReturnDefPtr[other][i].arg);
            }
        }
    }
    if (gLoadBusy) {
        func_00234CA0(0);
        if (gLoadReturnValue != 0xFFFFFFFF) {
            void (*fn)(int, long) = gLoadReturnDef.fn;
            if (fn) {
                long arg = gLoadReturnDef.arg;
                gLoadReturnDef.fn = 0;
                gLoadReturnDef.arg = 0;
                fn(gLoadReturnValue, arg);
            }
            gLoadReturnValue = 0;
            gLoadBusy = 0;
        }
    }
    if (!gCommBusy) {
        if (*gSndCommandBuffePtr[gCommandFillBuffer] && !gCaching)
            snd_SendCurrentBatch__Fv();
    }
    if (gSSRead) {
        snd_StreamSafeCdSync(1);
        if (gSSReadDone) {
            gSSRead = 0;
            gSSReadDone = 0;
            if (gCdCallback)
                gCdCallback(1);
        }
    }
    if (gCommBusy || gLoadBusy)
        return 1;
    return 0;
}
