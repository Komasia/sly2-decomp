struct S { char pad[0x18]; void *p18; char pad2[0x18]; int n34; char pad3[8]; int n40; };
void Update__5AIJOB(struct S *p);
int func_001EF0A8(struct S *p);
int func_00174FB8(void *p);
void SetActState__6JOBACTi(struct S *p, int n);
// name: SafeHouse port (JOBACT::Update)
void Update__6JOBACT(struct S *p) {
    int s;
    Update__5AIJOB(p);
    do {
        if (func_001EF0A8(p)) return;
        s = p->n34;
        switch (s) {
        case 0:
            if (p->n40) SetActState__6JOBACTi(p, 1);
            else if (func_00174FB8(p->p18)) SetActState__6JOBACTi(p, -1);
            break;
        case 1:
            if (func_00174FB8(p->p18)) SetActState__6JOBACTi(p, -1);
            break;
        }
    } while (s != p->n34);
}
