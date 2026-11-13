struct CRef;
extern "C" void Decref(CRef *) asm("Decref__4CRef");
struct CRef { int m_tagk; int m_tag; CRef(const CRef &) __asm__("__4CRefRC4CRef"); ~CRef() { Decref(this); } };
extern "C" {
extern int D_003E0FC0, D_003E0FD8, D_003E0FDC, D_003E0FE0;
extern int D_003DD050;
extern int D_002C2D8C;
extern char D_003D4A60[];
}
CRef Eval(int a, void *b) __asm__("NProgress");
static inline int GetTag(int id) { return Eval(id, D_003D4A60).m_tag; }
// name: SafeHouse port (InitOptionText)
extern "C" void InitOptionText__FP7MENUENT(int *s)
{
    int t;
    switch (*s) {
    case 63:
        break;
    case 76:
    case 77:
    case 78:
        switch (GetTag(D_003E0FC0)) {
        case 1:
            *s = 0x4C;
            break;
        case 2:
            *s = 0x4D;
            break;
        case 0:
        default:
            *s = 0x4E;
            break;
        }
        break;
    case 79:
    case 80:
        *s = D_003DD050 ? 0x4F : 0x50;
        break;
    case 72:
    case 73:
        switch (D_002C2D8C) {
        case 1:
            t = GetTag(D_003E0FD8);
            break;
        case 2:
            t = 0;
            break;
        case 3:
            t = 1;
            break;
        default:
            t = 0;
            break;
        }
        if (t) *s = 0x49; else *s = 0x48;
        break;
    case 81:
    case 82:
        if (GetTag(D_003E0FDC)) *s = 0x52; else *s = 0x51;
        break;
    case 83:
    case 84:
        if (GetTag(D_003E0FE0)) *s = 0x54; else *s = 0x53;
        break;
    case 104:
        break;
    }
}
