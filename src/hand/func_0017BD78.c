struct T { char pad[0x30]; int n30; };
struct S { char pad[0x10]; void *p10; int pad2; struct T *p18; char pad3[0x14]; int n30; char pad4[0xC]; int n40; };
void Update__5AIJOB(struct S *p);
int func_00209098(void *p);
void Choose__5JOBB2(struct S *p);
int func_001EF0A8(struct S *p);
void SetB2State__5JOBB2i(struct S *p, int n);
int func_00175810(struct T *p);
// name: SafeHouse port (JOBB2::Update)
void Update__5JOBB2(struct S *p) {
    int f, s;
    Update__5AIJOB(p);
    f = func_00209098(p->p10);
    Choose__5JOBB2(p);
    while (!func_001EF0A8(p)) {
        s = p->n30;
        switch (s) {
        case 0:
            if (f) SetB2State__5JOBB2i(p, 2);
            else if (p->n40) SetB2State__5JOBB2i(p, 1);
            break;
        case 1:
            if (f) SetB2State__5JOBB2i(p, 2);
            else if (!p->n40) SetB2State__5JOBB2i(p, 0);
            else if (p->n40 != p->p18->n30) { SetB2State__5JOBB2i(p, -1); SetB2State__5JOBB2i(p, 1); }
            else if (func_00175810(p->p18)) SetB2State__5JOBB2i(p, 0);
            break;
        case 2:
            if (!f) SetB2State__5JOBB2i(p, 0);
            break;
        }
        if (s != p->n30) continue;
        break;
    }
}
