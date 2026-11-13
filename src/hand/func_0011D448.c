int NRandom(void) asm("NRandom__Fv");
float GRandInRange__Fff(float gMin, float gMax)
{
    if (gMin == gMax)
        return gMin;
    return gMin + (gMax - gMin) * (float)(NRandom() % 0x16A1B) * 1.078760305972537e-05f;
}
