/* func_001637E8: whether the task applies its state changes: not disabled, not in change mode 2 / 3, and the world
 * not in its func_0020E040 state (the job's twin: func_00162670). */
struct TASK { char pad[0x50]; int fDisabled; char pad2[0xF4 - 0x54]; int nMode; };
extern char g_sw[];
int func_0020E040(void *psw);
int func_001637E8(struct TASK *ptask)
{
    if (ptask->fDisabled == 0 && ptask->nMode != 2 && ptask->nMode != 3)
        return func_0020E040(g_sw) == 0;
    return 0;
}
