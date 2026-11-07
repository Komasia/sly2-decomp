extern struct { float t; float dt; } g_clock;
extern float D_002C3D40[3];
struct S { char pad[0xFBC]; int k; float t; };
void SetGuardMode__FP5GUARDi(struct S *p, int n);
// name: SafeHouse port (UpdateGuardTimedMode)
void UpdateGuardTimedMode__FP5GUARD(struct S *p)
{
    switch (p->k) {
    case 8:
    case 13:
        if (g_clock.t - p->t > D_002C3D40[0])
            SetGuardMode__FP5GUARDi(p, -1);
        break;
    case 34:
    case 37:
        if (g_clock.t - p->t > D_002C3D40[1])
            SetGuardMode__FP5GUARDi(p, -1);
        break;
    case 21:
        if (g_clock.t - p->t > D_002C3D40[2])
            SetGuardMode__FP5GUARDi(p, -1);
        break;
    }
}
