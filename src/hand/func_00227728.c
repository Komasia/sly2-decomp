struct C { unsigned char a[4]; };
struct S { int k; struct C c; int z; };
void func_00227788(struct S *p);
void RgbaDialogSpeaker__Fi(struct C *pc, int a);
// name: SafeHouse port (SetDialogSubtitle)
void SetDialogSubtitle__FP9DIALOGSUBii(struct S *p, int k, int b)
{
    struct C c;
    func_00227788(p);
    p->k = k;
    RgbaDialogSpeaker__Fi(&c, b);
    p->c = c;
}
