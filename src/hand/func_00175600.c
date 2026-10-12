struct S { char pad[0x18]; void *p18; char pad2[0x18]; int n34; char pad3[8]; int n40; };
void func_001EEF98(struct S *p);
int func_001EF0A8(struct S *p);
int func_00174FB8(void *p);
void func_00175488(struct S *p, int n);
void func_00175600(struct S *p) {
    int s;
    func_001EEF98(p);
    do {
        if (func_001EF0A8(p)) return;
        s = p->n34;
        switch (s) {
        case 0:
            if (p->n40) func_00175488(p, 1);
            else if (func_00174FB8(p->p18)) func_00175488(p, -1);
            break;
        case 1:
            if (func_00174FB8(p->p18)) func_00175488(p, -1);
            break;
        }
    } while (s != p->n34);
}
