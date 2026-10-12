void func_001F7D90(void *, float);
void func_001F7D10(void *, float);
void func_001F7BF8(void *p, float f)
{
    if (f <= 0.0f) {
        func_001F7D90(p, 0.0f);
        func_001F7D10(p, 0.0f);
    } else {
        func_001F7D90(p, -1.0f / f);
    }
}
