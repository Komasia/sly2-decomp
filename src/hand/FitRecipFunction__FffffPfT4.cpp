int FFloatsNear(float a, float b, float eps) __asm__("func_0011D4D0");
void FitRecipFunction(float x0, float y0, float x1, float y1, float *pdu, float *pru)
{
    float gEpsilon = 0.0001f;
    if (FFloatsNear(x0, x1, gEpsilon) || __builtin_fabsf(x0) < gEpsilon || __builtin_fabsf(x1) < gEpsilon)
    {
        *pru = 0.0f;
        *pdu = y0;
        return;
    }

    float deltaX = x0 - x1;
    float deltaY = y1 - y0;

    float r = ((x0 * x1) * deltaY) / deltaX;
    float d = y0 - (r / x0);

    *pru = r;
    *pdu = d;
}
