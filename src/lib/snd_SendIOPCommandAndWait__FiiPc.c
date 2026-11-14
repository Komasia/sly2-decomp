// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// name: Sly 1 989snd.c (same mangled helper; called with (command, size, data) by the waited wrappers)
extern int gCommBusy, gCommandFillBuffer, gCaching, D_002C46B8;
extern int *gSndCommandBuffePtr[2];
extern unsigned char D_00443880[];
extern unsigned char D_0044388C[];
extern int gSyncBuffer[];
extern char D_00443800[];
extern char D_002AA5A0[], D_002AA1C8[];
void printf(const char *, ...);
void *s1_memcpy(void *, void *, int) asm("memcpy");
void snd_FlushSoundCommands(void);
void FlushCache(int);
void func_00231F38(void *, int);
int sceSifCheckStatRpc(void *);
int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
int snd_GotReturns__Fv(void);
void snd_SendCurrentBatch__Fv(void);

int snd_SendIOPCommandAndWait__FiiPc(int cmd, int size, unsigned char *buf)
{
    int i;
    int ret;
    if (cmd != 0x68) {
        for (i = 0; i < size; i++)
            D_00443880[i] = buf[i];
    } else {
        if ((unsigned int)(*(int *)(buf + 8) + 0xC) > 0x200) {
            printf(D_002AA5A0);
            while (1)
                ;
        }
        for (i = 0; i < 0xC; i++)
            D_00443880[i] = buf[i];
        s1_memcpy(D_0044388C, *(void **)(buf + 0xC), *(int *)(buf + 8));
    }
    while (gCommBusy) {
        snd_FlushSoundCommands();
        FlushCache(0);
    }
    func_00231F38(gSyncBuffer, 1);
    while (sceSifCheckStatRpc(D_00443800)) {
        if (!D_002C46B8)
            printf(D_002AA1C8);
        snd_FlushSoundCommands();
        FlushCache(0);
    }
    if (size)
        sceSifCallRpc(D_00443800, cmd, 1, D_00443880, size, gSyncBuffer, 0xC, 0, 0);
    else
        sceSifCallRpc(D_00443800, cmd, 1, 0, 0, gSyncBuffer, 0xC, 0, 0);
    while (!snd_GotReturns__Fv())
        ;
    ret = gSyncBuffer[1];
    if (*gSndCommandBuffePtr[gCommandFillBuffer] && !gCaching)
        snd_SendCurrentBatch__Fv();
    return ret;
}
