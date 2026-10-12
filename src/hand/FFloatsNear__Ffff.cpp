int FFloatsNear(float g1, float g2, float gEpsilon)
{
    g2 = g1 - g2;
    g1 = g1 > 0.0f ? g1 : -g1;
    g2 = g2 > 0.0f ? g2 : -g2;
    float x = 1.0f;
    x = g1 > x ? g1 : x;
    return (g2 / x) < gEpsilon;
}
