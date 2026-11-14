/* func_001C9098 (called by LoadSwFromBrx): the loader's helper thread handshake - its semaphore D_003D3A40 signalled,
 * D_003D3A44 waited for, then D_002DD314 cleared. */
extern int D_003D3A40;
extern int D_003D3A44;
extern int D_002DD314;
int SignalSema(int sid);
int WaitSema(int sid);

void func_001C9098(void)
{
    SignalSema(D_003D3A40);
    WaitSema(D_003D3A44);
    D_002DD314 = 0;
}
