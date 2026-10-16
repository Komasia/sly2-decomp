int FFloatsNear(float a, float b, float eps) __asm__("func_0011D4D0");
void FitLinearFunction(float x0, float y0, float x1, float y1, float *pdu, float *pru)
{
    if (FFloatsNear(x0, x1, 0.0001f))
    {
        *pru = 0.0f;
        *pdu = y0;
        return;
    }

    float a = (y1 - y0) / (x1 - x0);
    *pru = a;
    *pdu = y0 - a * x0;
}
