struct S { char pad[0x3D78]; int n; };
struct G;
extern struct G g_joy;
void RemoveGrfusr__Fi(int n);
void ClearJoyBtns__FP6JOYPS2Ui(struct G *pg, int n);
void func_0020F160(struct S *p);
void func_0020F1A8(struct S *p);
// name: SafeHouse port (ResumeGame)
void ResumeGame__FP9GAMEPAUSEi(struct S *p, int grf)
{
    if (--p->n == 0) {
        RemoveGrfusr__Fi(2);
        ClearJoyBtns__FP6JOYPS2Ui(&g_joy, 8);
    }
    if (grf & 1) func_0020F160(p);
    if (grf & 2) func_0020F1A8(p);
}
