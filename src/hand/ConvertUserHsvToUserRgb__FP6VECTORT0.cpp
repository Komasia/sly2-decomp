struct VECTOR { float x, y, z; } __attribute__((aligned(16)));
extern "C" void RgbFromHsv(VECTOR *pvecHsv, VECTOR *pvecRgb) asm("RgbFromHsv__FP6VECTORT0");

void ConvertUserHsvToUserRgb(VECTOR *pvecHsv, VECTOR *pvecRgb)
{
    VECTOR vecHsv = *pvecHsv;
    vecHsv.y *= 1.0f / 255.0f;
    vecHsv.z *= 1.0f / 255.0f;
    RgbFromHsv(&vecHsv, pvecRgb);
    pvecRgb->x *= 255.0f;
    pvecRgb->y *= 255.0f;
    pvecRgb->z *= 255.0f;
}
