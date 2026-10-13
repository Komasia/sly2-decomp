extern float D_002DDF0C;
extern void *D_002DD314;
extern int D_003D3A3C;
int func_00234A40(int);

static inline float *Receiver(float *p)
{
    register float *source __asm__("$4") = p;
    register float *copy __asm__("$5");
    __asm__("daddu %0,%1,$zero" : "=r"(copy) : "r"(source));
    return copy;
}

void func_001C9058(float *input)
{
    float now = D_002DDF0C;
    float *p = Receiver(input);
    int sema = D_003D3A3C;
    *p = now;
    D_002DD314 = p;
    func_00234A40(sema);
}
