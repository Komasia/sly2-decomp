typedef struct {
    char pad[0x10];
    int x10;
    int pad14;
    int x18;
    float x1C;
    int x20;
    float x24;
} OBJ;
void func_001DA578(OBJ *, int);
void func_001DA5C8(OBJ *, int);
void func_001DA4B8(OBJ *p, int n, float g)
{
    if (n == -1) {
        func_001DA578(p, -1);
        return;
    }
    switch (p->x10) {
    case 1:
        func_001DA5C8(p, -1);
    case 0:
    case 3:
        p->x18 = n;
        p->x1C = g;
        func_001DA5C8(p, 1);
        break;
    case 2:
        if (p->x18 == n) {
            p->x1C = g;
            break;
        }
    case 4:
        p->x20 = n;
        p->x24 = g;
        break;
    }
}
