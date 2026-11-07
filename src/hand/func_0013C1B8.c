struct S { char pad[0x184]; int st; int f188; int f18c; };
void func_00133590(struct S *, int, int);
void SetBootyState__FP2LOi(struct S *, int);
// name: SafeHouse port (OnBootyMessage)
void OnBootyMessage__FP2LOii(struct S *p, int msg, int a) {
    func_00133590(p, msg, a);
    switch (msg) {
    case 4:
        if (p->st == 5) SetBootyState__FP2LOi(p, 0);
        break;
    case 8:
        if (a == p->f18c) {
            switch (p->st) {
            case 2: SetBootyState__FP2LOi(p, 4); break;
            case 3: SetBootyState__FP2LOi(p, 1); break;
            }
        }
        break;
    }
}
