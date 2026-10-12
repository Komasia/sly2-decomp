typedef struct S { char pad[0x98]; short k; short x9A; } S;
void func_002303A0(void *, S *, int);

void func_00230630(void *p, S *s)
{
    switch (s->k) {
    case 7:
    case 9:
        if (s->x9A == 2)
            func_002303A0(p, s, 10);
        else if (s->x9A == 1)
            func_002303A0(p, s, 6);
        break;
    case 11:
        if (s->x9A == 2)
            func_002303A0(p, s, 0xC);
        break;
    case 18:
        if (s->x9A == 2)
            func_002303A0(p, s, 0x13);
        break;
    case 1:
        func_002303A0(p, s, 3);
        break;
    }
}
