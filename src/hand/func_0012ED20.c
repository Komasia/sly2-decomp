typedef struct REC { int id; float a, b, c, d; } REC;
typedef struct H { void *p; } H;
typedef struct T { char pad[0xE4]; int c; REC *arec; H *ap; } T;
void func_001A6178(T *t);
void *func_001FBB90(int id);
void SetSource__4CSndPv(void *p, T *t);
void SetFalloff__4CSndff(void *p, float a, float b);
void SetVolume__4CSndf(void *p, float c);
void SetPitch__4CSndiif(void *p, float d);
void func_00258040(H *pp, void *p);
void func_0012ED20(T *t)
{
    int i;
    func_001A6178(t);
    for (i = 0; i < t->c; i++) {
        REC *prec = &t->arec[i];
        void *p = func_001FBB90(prec->id);
        SetSource__4CSndPv(p, t);
        SetFalloff__4CSndff(p, prec->a, prec->b);
        SetVolume__4CSndf(p, prec->c);
        SetPitch__4CSndiif(p, prec->d);
        func_00258040((H *)(i * 4 + (int)t->ap), p);
    }
}
