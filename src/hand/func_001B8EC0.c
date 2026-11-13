typedef struct T { char pad[0x1C]; float x1C; char pad2[0x80 - 0x20]; int x80; } T;
typedef struct P {
    char pad0[0x150];
    T *x150;
    char pad154[0x1030 - 0x154];
    void *x1030;
    char pad1034[0x1840 - 0x1034];
    int x1840;
    float x1844;
    char pad1848[0x1900 - 0x1848];
    void *x1900;
    int pad1904;
    int x1908;
    char pad190C[0x1AC0 - 0x190C];
    int x1AC0;
} P;
extern float g_clock;
extern float D_002C0A30;
extern float D_002C0A34;
int FAsegaRetracted(void *p) asm("FAsegaRetracted__FP5ASEGA");
void func_001B6078(P *p, int s);
void SetMurrayBerserk__FP6MURRAYi(P *p, int s);
int FK2Done(void *p) asm("FK2Done__FP6K2PLAY");
void UpdateK2__FP6K2PLAY(void *p);

// name: SafeHouse port (UpdateMurrayBerserkTransitions)
void UpdateMurrayBerserkTransitions__FP6MURRAY(P *p)
{
    int s;
    for (;;) {
        s = p->x1840;
        switch (s) {
        case 0:
            if (!p->x1030 || FAsegaRetracted(p->x1030)) SetMurrayBerserk__FP6MURRAYi(p, 1);
            break;
        case 1:
            if (!p->x1030 || FAsegaRetracted(p->x1030)) {
                func_001B6078(p, 0);
            } else if (p->x1908) {
                SetMurrayBerserk__FP6MURRAYi(p, 2);
            } else if (!p->x1AC0 && g_clock - p->x1844 > D_002C0A30) {
                SetMurrayBerserk__FP6MURRAYi(p, 3);
            }
            break;
        case 2:
            if (!p->x1900 || FK2Done(p->x1900)) {
                if (p->x1AC0) SetMurrayBerserk__FP6MURRAYi(p, 0);
                else func_001B6078(p, 0);
            } else {
                UpdateK2__FP6K2PLAY(p->x1900);
            }
            break;
        case 3:
            if (!p->x1030 || FAsegaRetracted(p->x1030)) {
                func_001B6078(p, 0);
            } else if (g_clock - p->x1844 > D_002C0A34 && p->x150->x80 == 1 && 0.0f < p->x150->x1C) {
                func_001B6078(p, 0);
            }
            break;
        }
        if (p->x1840 == s || p->x1840 == -1) break;
    }
}
