/* Real roots of a x^2 + b x + c = 0 into ax (ascending): returns their count (0, 1 for a double root, or 2). */
static inline float sqrtf_(float x) { float r; __asm__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
#define sqrtf sqrtf_
float fabsf(float x);

int CSolveQuadratic__FfffPf(float a, float b, float c, float *ax)
{
    float alpha;
    float beta;

    c *= 4.0f;
    alpha = b * b - a * c;
    if (alpha < 0.0f)
        return 0;
    a = a + a;
    alpha = sqrtf(alpha) / a;
    beta = b / a;
    if (fabsf(alpha) < 0.0001f) {
        *ax = -beta;
        return 1;
    }
    ax[0] = -beta + alpha;
    ax[1] = -beta - alpha;
    if (ax[1] < ax[0]) {
        ax[0] = -beta - alpha;
        ax[1] = -beta + alpha;
    }
    return 2;
}
