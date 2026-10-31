/* UBias (Sly 1 wr.c): Schlick's bias curve of u with bias v. */
float UBias(float u, float v)
{
    return u / ((1.0f / v - 2.0f) * (1.0f - u) + 1.0f);
}
