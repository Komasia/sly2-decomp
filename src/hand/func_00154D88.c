/* The suck's progress (SafeHouse task.cpp: 0x154D88 on 0x2DE578, the suck history): the value raised by g. */
float GSuck__FPv(void *psuck);
void SetSuck__FPvf(void *psuck, float g);

void func_00154D88(void *psuck, float g)
{
    SetSuck__FPvf(psuck, GSuck__FPv(psuck) + g);
}
