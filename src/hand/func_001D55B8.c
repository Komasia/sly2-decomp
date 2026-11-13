typedef struct CRef { int tagk; int tag; } CRef;
extern int D_002C2D8C;
extern void *D_003E0FD8;
extern char D_003D4A60[];
void NProgress(CRef *pref, void *a, char *b);
void Decref(CRef *pref) asm("Decref__4CRef");
// name: SafeHouse port (FVibrationEnabled)
int FVibrationEnabled__Fv(void) {
    switch (D_002C2D8C) {
    case 2:
        return 1;
    case 0:
    case 3:
        return 0;
    case 1:
    default: {
        CRef ref;
        int n;
        NProgress(&ref, D_003E0FD8, D_003D4A60);
        n = ref.tag;
        Decref(&ref);
        return n ^ 1;
    }
    }
}
