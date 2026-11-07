typedef struct S { char pad[0x98]; short k; short x9A; } S;
void SetXfMode__FP3ALOP2XFi(void *, S *, int);

// name: SafeHouse port (ReleaseXfMode)
void ReleaseXfMode__FP3ALOP2XF(void *p, S *s)
{
    switch (s->k) {
    case 7:
    case 9:
        if (s->x9A == 2)
            SetXfMode__FP3ALOP2XFi(p, s, 10);
        else if (s->x9A == 1)
            SetXfMode__FP3ALOP2XFi(p, s, 6);
        break;
    case 11:
        if (s->x9A == 2)
            SetXfMode__FP3ALOP2XFi(p, s, 0xC);
        break;
    case 18:
        if (s->x9A == 2)
            SetXfMode__FP3ALOP2XFi(p, s, 0x13);
        break;
    case 1:
        SetXfMode__FP3ALOP2XFi(p, s, 3);
        break;
    }
}
