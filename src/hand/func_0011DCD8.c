typedef struct RGBA { unsigned char r, g, b, a; } RGBA;

void func_0011DCD8(RGBA *prgba, float *pg)
{
    pg[0] = prgba->r * (1.0f / 255.0f);
    pg[1] = prgba->g * (1.0f / 255.0f);
    pg[2] = prgba->b * (1.0f / 255.0f);
}
