/* func_001FF830 (called by UnloadWorld): the frame reference dropped (0x256EE0 with 0), then the Splice state reset
 * (0x12AE28). */
void func_00256EE0(void *ppframe, void *pframe);
void func_0012AE28(void);

void func_001FF830(void *ppframe)
{
    func_00256EE0(ppframe, 0);
    func_0012AE28();
}
