float GLimitAbs(float g, float gLimit)
{
    if (g > gLimit) {
        g = gLimit;
    } else if (g < -gLimit) {
        g = -gLimit;
    }
    return g;
}
