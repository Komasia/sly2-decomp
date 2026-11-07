struct CLOCK { float t; };
extern struct CLOCK g_clock;
extern float D_002A70E0;
struct S { char pad[0x168]; float f168; int x16C; char pad1[0x1C4 - 0x170]; int x1C4; char pad2[0x220 - 0x1C8]; int x220; int x224; float f228; float f22C; };
void UpdateSo__FP2SOf(struct S *p);
int StBirdSees__FP2LO(struct S *p);
int FBirdFacing__FP2LO(struct S *p);
void func_001F7BF8(struct S *p, float f);
void SetBirdState__FP2LOi(struct S *p, int st);
void MoveBirdAlongPath__FP2LO(struct S *p);
// name: SafeHouse port (UpdateBird)
void UpdateBird__FP2LO(struct S *p)
{
    int st;
    UpdateSo__FP2SOf(p);
    st = p->x220;
    switch (st) {
    case 0:
        st = StBirdSees__FP2LO(p);
        if (st != 3 && p->f228 <= g_clock.t) {
            if (p->x16C) st = 1;
        }
        break;
    case 1:
        st = StBirdSees__FP2LO(p);
        if (st != 3 && p->f228 <= g_clock.t) st = 0;
        break;
    case 2:
        st = StBirdSees__FP2LO(p);
        if (st != 3 && FBirdFacing__FP2LO(p)) st = 1;
        break;
    case 3:
        if (!p->x1C4 && FBirdFacing__FP2LO(p)) st = 4;
        break;
    case 4:
        if (p->f22C <= g_clock.t) {
            func_001F7BF8(p, p->f168);
            p->f22C = D_002A70E0;
        }
        break;
    }
    SetBirdState__FP2LOi(p, st);
    MoveBirdAlongPath__FP2LO(p);
}
