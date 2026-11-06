typedef struct T { char pad[0xE4]; int c; int pad2; void **ap; } T;
void func_001A6150(T *p);
void Stop__4CSndf(void *pv, float g);
void func_00258040(void **pp, int n);
void func_0012EDE8(T *p)
{
    int i;
    func_001A6150(p);
    for (i = 0; i < p->c; i++) {
        void **pp = (void **)((i << 2) + (int)p->ap);
        if (pp && *pp) {
            Stop__4CSndf(*pp, 0.0f);
            func_00258040(pp, 0);
        }
    }
}
