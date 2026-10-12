float fmodf(float x, float y);

float func_0011D898(float gDividend, float gDivisor)
{
    float result = fmodf(gDividend, gDivisor);
    if (result < 0.0f) {
        result += gDivisor;
    }
    return result;
}
