float func_0011D898(float gDividend, float gDivisor);

float func_0011CF60(float rad)
{
    if (rad < -3.14159265359f || 3.14159265359f < rad) {
        float modpos = func_0011D898(rad + 3.14159265359f, 2 * 3.14159265359f);
        rad = modpos - 3.14159265359f;
    }
    return rad;
}
