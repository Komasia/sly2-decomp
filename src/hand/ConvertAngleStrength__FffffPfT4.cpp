float cosf(float) __asm__("func_00244E10");
void FitLinearFunction(float x0, float y0, float x1, float y1, float *pdu, float *pru);
void ConvertAngleStrength(float deg0, float g0, float deg1, float g1, float *pdu, float *pru)
{
    const float kDegToHalfRad = 0.008726647f;
    const float kStrengthScale = 1.0f / 255.0f;

    float strength0 = cosf(deg0 * kDegToHalfRad);
    strength0 += strength0 * strength0 * strength0;

    float strength1 = cosf(deg1 * kDegToHalfRad);
    strength1 += strength1 * strength1 * strength1;

    FitLinearFunction(strength0, g0 * kStrengthScale, strength1, g1 * kStrengthScale, pdu, pru);
}
