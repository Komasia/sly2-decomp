typedef int qword __attribute__((mode(TI)));
qword PosOfLo__FP2LO(void *p);
qword DwAloTorque__FP3ALOG9VU_VECTOR(void *p, qword q);
qword func_001FAA48(void *p, qword a, qword b)
{
    qword r, c, d;
    d = PosOfLo__FP2LO(p);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(d));
    c=b;
    __asm__("vopmula.xyz $ACC, %1, %0\n\tvopmsub.xyz %0, %0, %1" : "+j"(c) : "j"(r));
    return DwAloTorque__FP3ALOG9VU_VECTOR(p, c);
}

typedef char angular_input_layout[(sizeof(qword)==16 && __alignof__(qword)==16 && sizeof(void*)==4)?1:-1];
