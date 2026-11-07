struct T { char pad[0x30]; int fl; };
struct S {
    char pad[0x150]; struct T *pt; char p0[0x16C]; char x2c0[0x208]; int x4c8;
    char p1[0x13FC]; int st; int p2; int x18d0; int p3; int x18d8; char p4[8]; int x18e4; int x18e8; int x18ec;
};
int GrfPadctlTakePressed__FP6PADCTL(struct T *p, int n, float g);
void SetJumpKind__FP4JUMPiiP2LO(void *p, int a, int b, int c);
void SetJtJts__FP2JT3JTS4JTBS(struct S *p, int a, int b);
void SetSlyMode__FP3SLYi(struct S *p, int n);
int NSlyNextTriangle__FP3SLY(struct S *p);
int NSlyNextSwing__FP3SLY(struct S *p);
// name: SafeHouse port (UpdateSlyButtons)
void UpdateSlyButtons__FP3SLY(struct S *p)
{
    int f;
    switch (p->x18d8) {
    case 12 ... 21:
        if (!(p->pt->fl & 0x80)) p->x18ec = 0;
        break;
    }
    f = 0;
    switch (p->st) {
    case 3: case 21: case 22:
        if (GrfPadctlTakePressed__FP6PADCTL(p->pt, 0x80, 0.0f))
            SetJumpKind__FP4JUMPiiP2LO(p->x2c0, 0, 0, 0);
        break;
    case 7:
        if (p->x4c8 < 5) f = p->x4c8 >= 3;
        break;
    case 5:
        switch (p->x18d0) {
        case 6: case 7:
            if (!(p->pt->fl & 0x80)) {
                if (p->x18e8) SetJtJts__FP2JT3JTS4JTBS(p, 5, 8);
                else SetJtJts__FP2JT3JTS4JTBS(p, 5, 4);
            }
            break;
        case 8: case 9:
            return;
        default:
            f = 1;
            break;
        }
        break;
    case 0: case 1: case 10: case 12:
        f = 1;
        break;
    }
    if (!f) return;
    switch (p->x18d8) {
    case 12 ... 23:
        if (!p->x18e4) return;
    case -1:
        if (GrfPadctlTakePressed__FP6PADCTL(p->pt, 0x10, 0.35f)) {
            SetSlyMode__FP3SLYi(p, -1);
            SetSlyMode__FP3SLYi(p, NSlyNextTriangle__FP3SLY(p));
        } else if (GrfPadctlTakePressed__FP6PADCTL(p->pt, 0x80, 0.35f)) {
            SetSlyMode__FP3SLYi(p, -1);
            SetSlyMode__FP3SLYi(p, NSlyNextSwing__FP3SLY(p));
        }
        break;
    }
}
