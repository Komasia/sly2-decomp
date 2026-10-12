typedef struct LM { float gMin; float gMax; } LM;
float func_0011CF60(float rad);
float GLimitAbs__Fff(float g, float gLimit);

float func_0011D978(LM *plm, float rad)
{
    float radMid = (plm->gMax + plm->gMin) * 0.5f;
    float radHalf = (plm->gMax - plm->gMin) * 0.5f;
    return func_0011CF60(radMid + GLimitAbs__Fff(func_0011CF60(rad - radMid), radHalf));
}
