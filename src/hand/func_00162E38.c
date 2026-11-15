/* func_00162E38 (SafeHouse: EndJob): a job ends: it becomes the world's ended job (SW +0x3B18) and, unless the world
 * is busy (func_0020E040) or a transition is pending (+0x3C84), the current world reloads at point 0x189. */
struct SW { char pad[0x3B18]; void *pjobEnded; char pad2[0x3C84 - 0x3B1C]; int fTransition; };
extern struct SW g_sw;
int func_0020E040(struct SW *psw);
int func_00210B70(void);   /* the current world */
void RequestTransition__FP2SWPUc3OIDT2iT2(struct SW *psw, int pchzWorld, int oid, int a, int b, int c);
void func_00162E38(void *pjob)
{
    struct SW *psw = &g_sw;
    psw->pjobEnded = pjob;
    if (!func_0020E040(psw) && !psw->fTransition)
        RequestTransition__FP2SWPUc3OIDT2iT2(psw, func_00210B70(), 0x189, -1, 0, -1);
}
