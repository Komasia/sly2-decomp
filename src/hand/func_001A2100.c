extern float D_002BFB20, D_002BFB24;
struct Q { char pad[0x94]; float x94; float x98; };
struct S { int x0; int x4; };
void func_001A2100(struct S *p, struct Q *q)
{
    switch (p->x4) {
    case 4: case 12:
        q->x94 = D_002BFB20;
        q->x98 = 0;
        break;
    case 0: case 6: case 7:
        break;
    default:
        q->x94 = D_002BFB20;
        q->x98 = D_002BFB24;
        break;
    }
}
