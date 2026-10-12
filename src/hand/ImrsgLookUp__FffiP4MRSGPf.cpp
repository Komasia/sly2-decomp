struct MRSG { float t; float dt; };
int ImrsgLookUp(float t, float tMax, int cmrsg, MRSG *amrsg, float *pdt)
{
    int i;
    float dt;
    for (i = 0; ; amrsg++, i++) {
        if (i >= cmrsg) goto done;
        if (amrsg->dt == 0.0f) continue;
        dt = t - amrsg->t;
        if (dt < 0.0f) dt += tMax;
        if (dt < amrsg->dt + 0.0001f) break;
    }
    if (pdt) *pdt = dt;
done:
    return i;
}
