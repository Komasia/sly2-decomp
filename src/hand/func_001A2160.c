struct Q { unsigned int x0; char pad[0x30]; int x34; };
struct S { int x0; int x4; };
void func_001A2160(struct S *p, struct Q *q)
{
    switch (p->x4) {
    case 5: case 8: case 9: case 10: case 11: case 12: q->x34 = 0; break; case 4: break;
    }
    q->x0 |= 1;
}
