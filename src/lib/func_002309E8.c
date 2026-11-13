// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
void *s1_memset(void *, int, int); void PredictXfChain__FP2XFT0PvP7MATRIX4f(void *, void *, float, float *, float *);
void func_002309E8(void *a, void *b, float *m, float *n, float f)
{
    if (m) {
        s1_memset(m, 0, 0x40);
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }
    if (n) s1_memset(n, 0, 0x40);
    PredictXfChain__FP2XFT0PvP7MATRIX4f(a, b, f, m, n);
}
