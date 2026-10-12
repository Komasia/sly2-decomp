/* only diff: original assembler padded a backward branch (to a jr) with a nop at 0x14443C; asfix.py does not pad when a jump is in between. Code otherwise identical. */
struct Q { char pad[0xC]; int c; int n; };
int func_00144418(char *p, struct Q *q)
{
    if (-q->n < *(int *)(p + 0xDFC)) return 0;
    switch (q->c) {
    case 0:
    case 1:
    case 0x80000:
    case 0x100000:
        return 0;
    }
    return 1;
}
