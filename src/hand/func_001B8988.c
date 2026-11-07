typedef struct T { char pad[0x1C]; float x1C; } T;
typedef struct P {
    char pad0[0x150];
    T *x150;
    char pad154[0x1030 - 0x154];
    void *x1030;
    char pad1034[0x1810 - 0x1034];
    int x1810;
    char pad1814[0x181C - 0x1814];
    int x181C;
} P;
int func_00131968(void *p);
void func_001B6078(P *p, int s);
int func_001B84E0(P *p);
int GrfPadctlTakePressed__FP6PADCTL(T *t, int k, float f);
void SetMurrayPunch__FP6MURRAYi(P *p, int k);
int FMurrayGrab__FP6MURRAY(P *p);
void EndMurrayPunch__FP6MURRAY(P *p);

// name: SafeHouse port (UpdateMurrayPunchTransitions)
void UpdateMurrayPunchTransitions__FP6MURRAY(P *p)
{
    int s;
    for (;;) {
        s = p->x1810;
        if (!p->x1030 || func_00131968(p->x1030)) {
            func_001B6078(p, 0);
        } else {
            switch (p->x1810) {
            case 0:
            case 1:
                if (func_001B84E0(p) && GrfPadctlTakePressed__FP6PADCTL(p->x150, 0x80, 0.25f)) {
                    SetMurrayPunch__FP6MURRAYi(p, p->x1810 == 0);
                } else if (!func_001B84E0(p) || !FMurrayGrab__FP6MURRAY(p)) {
                    if (p->x181C && 0.0f < p->x150->x1C) EndMurrayPunch__FP6MURRAY(p);
                }
                break;
            case 2:
            case 3:
                if (func_001B84E0(p) && GrfPadctlTakePressed__FP6PADCTL(p->x150, 0x10, 0.25f)) {
                    SetMurrayPunch__FP6MURRAYi(p, (p->x1810 == 2) ? 3 : 2);
                } else if (!func_001B84E0(p) || !FMurrayGrab__FP6MURRAY(p)) {
                    if (p->x181C && 0.0f < p->x150->x1C) EndMurrayPunch__FP6MURRAY(p);
                }
                break;
            }
        }
        if (p->x1810 == s || p->x1810 == -1) break;
    }
}
