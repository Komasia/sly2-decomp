typedef int qword __attribute__((mode(TI)));
struct V {qword q;};
struct M4 { qword r[4];  };
extern "C" qword VecRotateTiltPan(qword,qword) asm("VecRotateTiltPan__FG9VU_VECTORT0");
extern "C" M4 DmatSkew(void *,void *,V) asm("DmatSkew__FP7MATRIX4P7VECTOR4PvG9VU_VECTOR");
extern "C" M4 func_0022CB90(void *a,void *b,qword c,qword d) return m {
    V v;v.q=VecRotateTiltPan(c,d);
    m=DmatSkew(a,b,v);
}
