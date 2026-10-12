struct O { char pad[0x520]; int x520; };
struct S { struct O *p; int pad[6]; int x1c; char pad2[0xC0-0x20]; int c0; int c4; };
int func_0019C870(struct S *s, int *pn) {
    int v;
    switch (s->x1c) {
    case 0xB: case 0xC: case 0xD: v = s->p->x520; break;
    case 0x11: v = s->c4; break;
    default: v = s->c0; break;
    }
    *pn = 0;
    return v;
}
